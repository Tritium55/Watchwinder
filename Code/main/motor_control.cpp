#include <Arduino.h>
#include "./motor_control.h"

#include "./settings.h"


ServoMotor::ServoMotor(int _pin) : pin(_pin){
}

void ServoMotor::ServoMotorInit(void){
    servo.attach(pin);
}

void ServoMotor::ServoHome(void){
    servo.write(90);
    delay(6000);
}

void ServoMotor::ServoSpinOnce(void){
    servo.write(0);
    delay(3000);
    servo.write(90);
    delay(3000);
    servo.write(180);
    delay(3000);
    servo.write(90);
    delay(3000);
}

void ServoMotor::ServoSpin(int turns){
    ServoHome();
    for(int i=0; i<turns; i++){
        ServoSpinOnce();
        delay(500);
    }
}