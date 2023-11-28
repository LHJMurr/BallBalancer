#include <Arduino.h>
#include "MotorManager.h"
#include "StepperMotor.h"

MotorManager::MotorManager() {
  /* Creates an empty motor manager object and established default values. */
  m_numMotors = 0;
  m_motors = nullptr;
  m_targetAngles = nullptr;
  m_currentAngles = nullptr;
  m_secondsPerTick = nullptr;
  m_lastTicks = nullptr;
}

MotorManager::~MotorManager() {
  delete[] m_currentAngles;
  delete[] m_targetAngles;
  delete[] m_secondsPerTick;
  delete[] m_lastTicks;
}

void MotorManager::initialize(int numMotors, StepperMotor* motors) {
  /* Initializes motor manager object with the number of motors and an array of the motors to coordinate. numMotors must be a positive integer and motors must be an array of stepper motor objects.*/
  m_numMotors = numMotors;
  m_motors = motors;
  // Initialize angle tracking array
  m_currentAngles = new float[m_numMotors];
  m_targetAngles = new float[m_numMotors];
  m_secondsPerTick = new float[m_numMotors];
  m_lastTicks = new float[m_numMotors];
  for (int i = 0; i < m_numMotors; i++) {
    m_currentAngles[i] = MotorManager::START_ANGLE;
    m_targetAngles[i] = MotorManager::START_ANGLE;
    m_secondsPerTick[i] = 0;
    m_lastTicks[i] = 0;
  }
  return;
}

void MotorManager::setTarget(float* targetAngles, float maxOmega) {
  /* m_targetAngles is a dynamically allocated array that is updated with this function. In this function, we create new parameters for the current motor command. */
  float* deltas = nullptr;
  deltas = new float[m_numMotors];
  float maxDelta = 0;
  for (int i = 0; i < m_numMotors; i++) {
    m_targetAngles[i] = targetAngles[i];
    deltas[i] = abs(m_currentAngles[i] - m_targetAngles[i]);
    if (deltas[i] > maxDelta) {
      maxDelta = deltas[i];
    }
  }
  for (int i = 0; i < m_numMotors; i++) { // Need two loops because we need to know maxDelta
    float current = 1.8 / m_motors[i].getMicrostep();
    m_secondsPerTick[i] = current * (1 / ((deltas[i] / maxDelta) *  maxOmega));
  }
  Serial.print("\n");
  delete[] deltas;
}

bool MotorManager::moveMotors() {
  /* Runs every tick and moves a motor if it is scheduled to move. Returns true if the target is met, else returns false. */
  if (m_targetAngles == nullptr) {
    Serial.println("TARGET IS NOT INITIALIZED");
    return false; // No target
  }
  bool endFlag = true;
  for (int i = 0; i < m_numMotors; i++) {
    float currentTarget = m_targetAngles[i];
    StepperMotor currentMotor = m_motors[i];
    float deltaAngle = 1.8 / currentMotor.getMicrostep(); // angle change per step
    if (abs(m_currentAngles[i] - currentTarget) < deltaAngle) { // if within step distance (as close as possible)
      continue;
    }
    endFlag = false; // needs at least one more adjustment
    float currentTime = millis() * 0.001;
    if (currentTime - m_lastTicks[i] > m_secondsPerTick[i]) { // Move motor
      m_lastTicks[i] = currentTime;
      bool dir = false;
      if (currentTarget > m_currentAngles[i]) {
        dir = true;
      }
    currentMotor.takeSteps(1, dir);
    m_currentAngles[i] = m_currentAngles[i] + (deltaAngle*directionCoefficient(dir));
    }
  }
  return endFlag;
}

void MotorManager::printAngles() const {
  for (int i = 0; i < m_numMotors; i++) {
    Serial.print(m_currentAngles[i]);
    Serial.print(" ");
  }
  Serial.print("\n");
  return;
}

void MotorManager::setUniformMicrostep(int microstep) {
  for (int i = 0; i < m_numMotors; i++) {
    m_motors[i].setMicrostep(microstep);
  }
  return;
}

int MotorManager::directionCoefficient(bool dir) const {
  if (dir) {
    return 1;
  }
  return -1;
}