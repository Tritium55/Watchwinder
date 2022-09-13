#ifndef motor_control_h
#define motor_control_h

#include <Servo.h>

class ServoMotor{
    private:
        Servo servo;
        int pin;
        void ServoSpinOnce(void);         //spins the servo by the number of turns
        void slowWrite(int angle);        //sets the servo to an angle, but with reduced turn speed

    public:
        ServoMotor(int _pin);
        void ServoMotorInit(void);        //must be used in the setup function
        void ServoHome(void);             //sets servo position to 90 degrees 
        void ServoSpin(int turns);        //spins the servo by the number of turns
};



#endif  //motor_control_h
