#include <Arduino.h>
#include "StepperMotorControl.h"

StepperMotor::StepperMotor(int stp, int dir, int ms1, int ms2, int ms3, int microstep) {
  /* Initializes the pins for the motor object. Stp is the step pin, dir is the direction pin, microstep is an argument telling which degree to step to, ms1/3 are the microstepping pins.
     microstep = 1- --> full step, 2 --> half step, 3 --> quarter step, 4 --> eigth step, 5+ --> sixteenth step. Default to fullstep.
     If not microstepping (or only using one of the pins) set the non-used ms integer values to something outside the range so it will not interfere with other components */
  // SAVE PIN NUMBERS
  m_step = stp;
  m_dir = dir;
  m_ms1 = ms1;
  m_ms2 = ms2;
  m_ms3 = ms3;
  // SET PIN MODES
  pinMode(m_step, OUTPUT);
  pinMode(m_dir, OUTPUT);
  pinMode(m_ms1, OUTPUT);
  pinMode(m_ms2, OUTPUT);
  pinMode(m_ms3, OUTPUT);
  // SET MICROSTEP MODEL
  this->setMicrostep(microstep);
  // INITIALIZE ANGLE
  m_angle = 0.0; // Assume angle of zero to start. High direction pin --> positive angle, Low direction pin --> negative angle.
}

void StepperMotor::setMicrostep(int microstep) {
  switch (microstep) {
    case StepperMotor::FULLSTEP:
      digitalWrite(m_ms1, LOW);
      digitalWrite(m_ms2, LOW);
      digitalWrite(m_ms3, LOW);
      m_microstep = StepperMotor::FULLSTEP;
      break;
    case StepperMotor::HALFSTEP:
      digitalWrite(m_ms1, HIGH);
      digitalWrite(m_ms2, LOW);
      digitalWrite(m_ms3, LOW);
      m_microstep = StepperMotor::HALFSTEP;
      break;
    case StepperMotor::QUARTERSTEP:
      digitalWrite(m_ms1, LOW);
      digitalWrite(m_ms2, HIGH);
      digitalWrite(m_ms3, LOW);
      m_microstep = StepperMotor::QUARTERSTEP;
      break;
    case StepperMotor::EIGTHSTEP:
      digitalWrite(m_ms1, HIGH);
      digitalWrite(m_ms2, HIGH);
      digitalWrite(m_ms3, LOW);
      m_microstep = StepperMotor::EIGTHSTEP;
      break;
    case StepperMotor::SIXTEENTHSTEP:
      digitalWrite(m_ms1, HIGH);
      digitalWrite(m_ms2, HIGH);
      digitalWrite(m_ms3, HIGH);
      m_microstep = StepperMotor::SIXTEENTHSTEP;
      break;
    default:
      digitalWrite(m_ms1, LOW);
      digitalWrite(m_ms2, LOW);
      digitalWrite(m_ms3, LOW);
      m_microstep = StepperMotor::FULLSTEP;
      break;      
  }
}

void StepperMotor::moveToAngle(float target) {
  /* Moves the stepper motor to the target angle, capped by a minimum of 0 and a maximum of 90. */

  // CALCULATE DIRECTION OF ROTATION
  bool dir;
  if (m_angle < target) {
    dir = true;
  }
  else {
    dir = false;  
  }
  // CALCULATE NUMBER OF STEPS
  float anglePerStep = 1.8 / m_microstep;
  float difference = abs(m_angle - target);
  int numSteps = round(difference / anglePerStep);
  // MOVE MOTOR
  this->takeSteps(numSteps, dir);
}

void StepperMotor::takeSteps(int numSteps, bool dir) {
  /* Moves the motor a set number of steps in a given direction and updates the angle in a for loop. Works on a per motor basis (ie. asynchronously) at a set speed of 600microseconds per step  */
  // SET DIRECTION
  int angleCoefficient;
  if (dir) {
    digitalWrite(m_dir, HIGH);
    angleCoefficient = 1; // Positive change in angle  
  }  
  else {
    digitalWrite(m_dir, LOW);  
    angleCoefficient = -1; // Negative change in angle
  }
  
  // LOOP THROUGH STEPS
  for (int i = 0; i < numSteps; i++) {
    digitalWrite(m_step, HIGH); 
    delayMicroseconds(600); 
    digitalWrite(m_step, LOW); 
    delayMicroseconds(600);
    // UPDATE ANGLE
    m_angle += (angleCoefficient) * (1.8 / m_microstep);
  }
}
