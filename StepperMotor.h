#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

/* This class contains the interface between the arduino and individual stepper motors. The class tracks the current angle (assuming no steps are skipped) as well as 
   containing step, direction, and microstep controls. */

class StepperMotor {
  public:
    StepperMotor(int stp, int dir, int ms1, int ms2, int ms3, int microstep); // Full microstepping control
    void setMicrostep(int microstep);
    void takeSteps(int numSteps, bool dir);
    int getMicrostep() const;

    // Microstepping Constants
    static const int FULLSTEP = 1;
    static const int HALFSTEP = 2;
    static const int QUARTERSTEP = 4;
    static const int EIGTHSTEP = 8;
    static const int SIXTEENTHSTEP = 16;
    
  private:
    // Functions
    // Members
    int m_step; // The pin connected to the drivers STEP input
    int m_dir;  // drivers DIRECTION input
    int m_ms1;  // drivers MS1 input (controls microstep logic)
    int m_ms2;
    int m_ms3;
    int m_microstep; // The current microstep state. Passed as an argument to setMicrostep. Defaults to fullstep.
};

#endif STEPPERMOTOR_H
