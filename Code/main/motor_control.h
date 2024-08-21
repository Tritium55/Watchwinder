#ifndef motor_control_h
#define motor_control_h

#include <Servo.h>

// TODO: rename
class ServoMotor{
    private:
        Servo servo;
        const uint8_t pin;
        void SpinOnce(void);                    //spins the servo by the number of turns
        void slowWrite(uint8_t angle);          //sets the servo to an angle, but with reduced turn speed

    public:
        ServoMotor(uint8_t _pin);
        void Init(void);                    //must be used in the setup function
        void Home(void);                    //sets servo position to 90 degrees
        void Spin(uint16_t turns);          //spins the servo by the number of turns
        static void SpinMultiple(const ServoMotor &m1, const ServoMotor &m2, const ServoMotor &m3, uint16_t turns);   // spins three motors simultaneously for winding
        void disable(void);                 //detaches the servo for power efficiency
        void enable(void);                  //reattaches the servo
};



#endif  //motor_control_h
