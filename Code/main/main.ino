#include "./motor_control.h"
#include "./eeprom_handler.h"
#include "./display_handler.h"

//all user settings are imported from this file
#include "./const_settings.h"

//create servo motors
ServoMotor m1(SERVO_PIN_1);
ServoMotor m2(SERVO_PIN_2);
ServoMotor m3(SERVO_PIN_3);

//manage EEPROM
EEPROM_Handler EEPROM;

//manage real time clock
Time_Handler clock;

//manage display
Display_Handler display;

void setup(){
    Serial.begin(9600);
    m1.Init();
    m2.Init();
    m3.Init();
    clock.Init();
    display.Init();
    
    // TODO set time
}

void loop(){
    m1.Home();
    delay(5000);
    m1.Spin(3);
    delay(1000);
}
