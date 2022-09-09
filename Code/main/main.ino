#include "./settings.h"
#include "./motor_control.h"

ServoMotor m1(ServoNr1);
ServoMotor m2(ServoNr2);
ServoMotor m3(ServoNr3);
ServoMotor m4(ServoNr4);

void setup(){
    m1.ServoMotorInit();
    m2.ServoMotorInit();
    m3.ServoMotorInit();
    m4.ServoMotorInit();
}

void loop(){
    m1.ServoHome();
    delay(5000);
    m2.ServoSpin(3);
    delay(1000);
}
