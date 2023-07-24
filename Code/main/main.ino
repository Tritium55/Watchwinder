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
    // TODO: check pull_down resistor option
    pinMode(CONFIRM_BUTTON, INPUT, PULL_DOWN);
    pinMode(INCREASE_BUTTON, INPUT, PULL_DOWN);
    m1.Init();
    m2.Init();
    m3.Init();
    clock.Init();
    display.Init();

    // TODO set time
}

// checks if confirm button is pushed and waits for release
bool confirmButtonPushed(){
    bool state = digitalRead(CONFIRM_BUTTON);
    if(!state)
        return false;
    while(state){
        state = digitalRead(CONFIRM_BUTTON);
    }
    return true;
}

// checks if increase button is pushed and waits for release
bool increaseButtonPushed(){
    bool state = digitalRead(INCREASE_BUTTON);
    if(!state)
        return false;
    while(state){
        state = digitalRead(INCREASE_BUTTON);
    }
    return true;
}

void setTime(){
    TimeHighlighting highlight = hours;
    Time time = clock.getTime();
    while(true){
        DisplayTime dt;
        dt.time = time;
        dt.time_highlight = highlight;
        display.handle_time_setting(dt);
        if(confirmButtonPushed()){
            if(highlight<seconds)
                highlight++;
            else
                return;
        }
        else if(increaseButtonPushed()){
            switch(highlight){
                case hours:
                    time.hours++;
                    time.hours %= 24;
                    break;
                
                case minutes:
                    time.minutes++;
                    time.minutes %= 60;
                    break;
                
                case seconds:
                    time.seconds++;
                    time.seconds %= 60;
                    break;
            }
        }
    }
}

void loop(){
    m1.Home();
    delay(5000);
    m1.Spin(3);
    delay(1000);
}
