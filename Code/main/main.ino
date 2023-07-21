#include "./motor_control.h"
#include "./eeprom_handler.h"

//all user settings are imported from this file
#include "./settings.h"

//create servo motors
ServoMotor m1(SERVO_PIN_1);
ServoMotor m2(SERVO_PIN_2);
ServoMotor m3(SERVO_PIN_3);

//manage EEPROM
EEPROM_Handler EEPROM;

//manage real time clock
Time_Handler clock;


void setup(){
    Serial.begin(9600);
    m1.ServoMotorInit();
    m2.ServoMotorInit();
    m3.ServoMotorInit();
    clock.Init();

    // TODO set time
}

void loop(){
    m1.ServoHome();
    delay(5000);
    m1.ServoSpin(3);
    delay(1000);
}
