#ifndef motor_control_h
#define motor_control_h

#include <Servo.h>

class ServoMotor{
  private:
    Servo servo;
    int servoAngle;
    int pin;
  public:
    ServoMotor(int _pin);
    void ServoMotorInit(void);
    void ServoSpin(int turns);        //spins the servo by the number of turns
}



#endif  //motor_control_h
