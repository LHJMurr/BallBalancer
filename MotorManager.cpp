#include <Arduino.h>
#include "MotorManager.h"
#include "StepperMotor.h"

MotorManager::MotorManager() {
  /* Creates an empty motor manager object and established default values. */
  m_numMotors = 0;
  m_motors = nullptr;
  m_targetAngles = nullptr;
  m_currentAngles = nullptr;
}

MotorManager::~MotorManager() {
  delete[] m_currentAngles;
}

void MotorManager::initialize(int numMotors, StepperMotor* motors) {
  /* Initializes motor manager object with the number of motors and an array of the motors to coordinate. numMotors must be a positive integer and motors must be an array of stepper motor objects.*/
  m_numMotors = numMotors;
  m_motors = motors;
  // Initialize angle tracking array
  m_currentAngles = new float[m_numMotors];
  for (int i = 0; i < m_numMotors; i++) {
    m_currentAngles[i] = MotorManager::START_ANGLE;
  }
  return;
}

void MotorManager::setTarget(float *targetAngles) {
  m_targetAngles = targetAngles;
}

bool MotorManager::moveMotors() {
  /* Runs every tick and moves a motor if it is scheduled to move. Returns true if the target is met, else returns false. */
  if (m_targetAngles == nullptr) {
    Serial.println("TARGET IS INVALID");
    return false; // No target
  }
  bool endFlag = true;
  for (int i = 0; i < m_numMotors; i++) {
    float currentTarget = m_targetAngles[i];
    StepperMotor currentMotor = m_motors[i];
    float deltaAngle = 1.8 / currentMotor.getMicrostep(); // angle change per step
    if (abs(m_currentAngles[i] - currentTarget) <= deltaAngle) { // if within step distance (as close as possible)
      continue;
    }
    endFlag = false; // needs at least one more adjustment
    bool dir = false;
    if (currentTarget > m_currentAngles[i]) {
      dir = true;
    }
    currentMotor.takeSteps(1, dir);
    m_currentAngles[i] = m_currentAngles[i] + (deltaAngle*directionCoefficient(dir));
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