#include "StepperMotorControl.h"

// Global Variables
StepperMotor motor_one(51, 53, 45, 47, 49, StepperMotor::FULLSTEP);
StepperMotor motor_two(50, 52, 44, 46, 48, StepperMotor::FULLSTEP);
StepperMotor motor_three(26, 28, 23, 22, 24, StepperMotor::FULLSTEP);

void setup() {
  Serial.begin(9600);
  delay(1000);  
}

void loop() {
  motor_one.setMicrostep(StepperMotor::SIXTEENTHSTEP);
  motor_one.moveToAngle(-10.0);
  delay(500);
  motor_two.setMicrostep(StepperMotor::SIXTEENTHSTEP);
  motor_two.moveToAngle(-10.0);
  delay(500);
  motor_three.setMicrostep(StepperMotor::SIXTEENTHSTEP);
  motor_three.moveToAngle(-10.0);
  delay(500);
  motor_one.setMicrostep(StepperMotor::SIXTEENTHSTEP);
  motor_one.moveToAngle(0);
  delay(500);
  motor_two.setMicrostep(StepperMotor::SIXTEENTHSTEP);
  motor_two.moveToAngle(0);
  delay(500);
  motor_three.setMicrostep(StepperMotor::SIXTEENTHSTEP);
  motor_three.moveToAngle(0);
  delay(500);
}
