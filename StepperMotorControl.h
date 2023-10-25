class StepperMotor {
  public:
    StepperMotor(int stp, int dir, int ms1, int ms2, int ms3, int microstep); // Full microstepping control
    void setMicrostep(int microstep);
    void moveToAngle(float target);

    // Microstepping Constants
    static const int FULLSTEP = 1;
    static const int HALFSTEP = 2;
    static const int QUARTERSTEP = 4;
    static const int EIGTHSTEP = 8;
    static const int SIXTEENTHSTEP = 16;

    // Angle Constants
    static const float START_ANGLE = 171.8;
    
  private:
    // Functions
    void takeSteps(int numSteps, bool dir);
    // Members
    int m_step;
    int m_dir;
    int m_ms1;
    int m_ms2;
    int m_ms3;
    int m_microstep;
    float m_angle = 0;
};
