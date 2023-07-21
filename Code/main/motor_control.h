#ifndef motor_control_h
#define motor_control_h

#include <Servo.h>

class ServoMotor{
    private:
        Servo servo;
        const uint8_t pin;
        void SpinOnce(void);         //spins the servo by the number of turns
        void slowWrite(uint8_t angle);        //sets the servo to an angle, but with reduced turn speed

    public:
        ServoMotor(uint8_t _pin);
        void Init(void);        //must be used in the setup function
        void Home(void);             //sets servo position to 90 degrees
        void Spin(uint8_t turns);        //spins the servo by the number of turns
};



#endif  //motor_control_h
