#include "StepperMotor.h"
#include "MotorManager.h"

// Global Variables
MotorManager manager; // empty manager object. Initialize in setup.

// FOR TESTING
float highTarget[3] = {120.0, 150.0, 150.0};
float lowTarget[3] = {MotorManager::START_ANGLE, MotorManager::START_ANGLE, MotorManager::START_ANGLE};
bool up = true;

void setup() {
  const int numMotors = 3;
  StepperMotor motors[numMotors] = {
    StepperMotor(51, 53, 45, 47, 49, StepperMotor::FULLSTEP), // motor one
    StepperMotor(50, 52, 44, 46, 48, StepperMotor::FULLSTEP), // motor two
    StepperMotor(24, 22, 30, 28, 26, StepperMotor::FULLSTEP), // motor three
  };
  manager.initialize(numMotors, motors);

  Serial.begin(9600);
  delay(1000); 

  manager.setUniformMicrostep(StepperMotor::SIXTEENTHSTEP);
  manager.setTarget(highTarget, 20.0);
}

void loop() {
  if(manager.moveMotors()) {
    up = !up;
    if (up) {
      manager.setUniformMicrostep(StepperMotor::SIXTEENTHSTEP);
      manager.setTarget(highTarget, 40.0);
    }
    else {
      manager.setUniformMicrostep(StepperMotor::SIXTEENTHSTEP);
      manager.setTarget(lowTarget, 40.0);
    }
  }

  /*
  motor_one.setMicrostep(StepperMotor::SIXTEENTHSTEP);
  motor_one.moveToAngle(StepperMotor::START_ANGLE - 10.0);
  delay(500);
  motor_two.setMicrostep(StepperMotor::SIXTEENTHSTEP);
  motor_two.moveToAngle(StepperMotor::START_ANGLE - 10.0);
  delay(500);
  motor_three.setMicrostep(StepperMotor::SIXTEENTHSTEP);
  motor_three.moveToAngle(StepperMotor::START_ANGLE - 10.0);
  delay(500);
  motor_one.setMicrostep(StepperMotor::SIXTEENTHSTEP);
  motor_one.moveToAngle(StepperMotor::START_ANGLE);
  delay(500);
  motor_two.setMicrostep(StepperMotor::SIXTEENTHSTEP);
  motor_two.moveToAngle(StepperMotor::START_ANGLE);
  delay(500);
  motor_three.setMicrostep(StepperMotor::SIXTEENTHSTEP);
  motor_three.moveToAngle(StepperMotor::START_ANGLE);
  delay(500);
  */
}
