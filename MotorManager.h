#ifndef MOTORMANAGER_H
#define MOTORMANAGER_H

/* This class is used to coordinate ainputted number of motors. It contains functions to input command angles and have the motors move synchronously. It is written to be scalable and have the potential
to be used with any number of motors, but for the ball balancer in particular there will be three. */

#include "StepperMotor.h"

class MotorManager {
  public:
    MotorManager();
    ~MotorManager();
    void initialize(int numMotors, StepperMotor* motors);
    void setTarget(float* targetAngles, float maxOmega); // maxOmega is the max angular velocity of any motor in degrees/second
    bool moveMotors();
    void printAngles() const;
    void setUniformMicrostep(int microstep);
    //Constants
    const static float START_ANGLE = 171.8;
  private:
    // Members
    int m_numMotors; // Number of motors to control.
    StepperMotor* m_motors; // Array of stepper motor objects. Create externally then pass as a parameter into initialize().
    float* m_targetAngles; // Array of angles for each motor to move towards
    float* m_currentAngles; // Array containing current angle information
    float* m_secondsPerTick; // Array containing the number of seconds per tick for each motor
    float* m_lastTicks; // Array containing the time when each motor last ticked.
    
    // Functions
    int directionCoefficient(bool dir) const;
};

#endif MOTORMANAGER_H