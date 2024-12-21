#ifndef motor_control_h
#define motor_control_h

#include <Servo.h>
#include <stdint.h>

// TODO: rename
class servo_motor{
    private:
        Servo servo;
        const uint8_t pin;
        const void spin_once(void);                     //spins the servo by the number of turns
        const void slow_write(uint8_t angle);           //sets the servo to an angle, but with reduced turn speed

    public:
        servo_motor(uint8_t _pin);
        const void init(void);                          //must be run in the setup function
        const void home(void);                          //sets servo position to 90 degrees
        const void spin(uint16_t turns);                //spins the servo by the number of turns
        
        // spins three motors simultaneously for winding
        const void spin_multiple(servo_motor &m1, servo_motor &m2, servo_motor &m3, uint16_t turns);
        
        const void disable(void);                       //detaches the servo for power efficiency
        const void enable(void);                        //reattaches the servo
};



#endif  //motor_control_h
