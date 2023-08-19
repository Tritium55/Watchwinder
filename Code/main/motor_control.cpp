#include "./motor_control.h"
#include "./const_settings.h"

#include <Arduino.h>


ServoMotor::ServoMotor(uint8_t _pin) : pin( _pin){
}

void ServoMotor::Init(void) {
    servo.attach(pin);
    this->Home();
}

void ServoMotor::slowWrite(uint8_t angle){
    //set servo angle limits
    if(angle < SERVO_LOW_LIMIT)
        angle = SERVO_LOW_LIMIT;

    if(angle > SERVO_HIGH_LIMIT)
        angle = SERVO_HIGH_LIMIT;

    //reads current angle of servo
    int currAngle = servo.read();

    if(angle >= currAngle){
        while(currAngle < angle){
            servo.write(currAngle);
            delay(SERVO_SPEED);
            currAngle++;
        }
    }
    else{
        while(currAngle > angle){
            servo.write(currAngle);
            delay(SERVO_SPEED);
            curAngle--;
        }
    }
}


void ServoMotor::Home(void){
    slowWrite(90);
    delay(2000);
}

// TODO: VERY IMPORTANT TO OPTIMIZE
void ServoMotor::SpinOnce(void){
    slowWrite(0);
    delay(3000);
    slowWrite(90);
    delay(3000);
    slowWrite(180);
    delay(3000);
    slowWrite(90);
    delay(3000);
}

void ServoMotor::Spin(uint16_t turns){
    ServoHome();
    for(int i=0; i<turns; i++){
        ServoSpinOnce();
        delay(300);
    }
}

void ServoMotor::disable(void){
    servo.detach();
    //TODO: disable with transistor/ mosfet
}

void ServoMotor::enable(void){
    servo.attach(pin);
    //TODO: enable with transistor/ mosfet
}