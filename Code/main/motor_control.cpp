#include <Arduino.h>
#include "./motor_control.h"

#include "./settings.h"


ServoMotor::ServoMotor(int _pin) : pin(_pin){
}

void ServoMotor::ServoMotorInit(void){
    servo.attach(pin);
}


void ServoMotor::slowWrite(int angle){
    if(angle<ServoLowLimit) angle=ServoLowLimit;                    //set servo angle limits
    if(angle>ServoHighLimit) angle=ServoHighLimit;

    int curAngle = servo.read();                                    //reads current angle of servo

    if(angle>=curAngle){
        while(curAngle<angle){
            servo.write(curAngle);
            delay(ServoSpeed);
            curAngle++;
        }
    }
    else{
        while(curAngle>angle){
            servo.write(curAngle);
            delay(ServoSpeed);
            curAngle--;
        }
    }
}


void ServoMotor::ServoHome(void){
    slowWrite(90);
    delay(6000);
}

void ServoMotor::ServoSpinOnce(void){
    slowWrite(0);
    delay(3000);
    slowWrite(90);
    delay(3000);
    slowWrite(180);
    delay(3000);
    slowWrite(90);
    delay(3000);
}

void ServoMotor::ServoSpin(int turns){
    ServoHome();
    for(int i=0; i<turns; i++){
        ServoSpinOnce();
        delay(500);
    }
}
