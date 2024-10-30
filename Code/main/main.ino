#include "./motor_control.h"
#include "./eeprom_handler.h"
#include "./display_handler.h"
#include "./time_handler.h"

//all user settings are imported from this file
#include "./const_settings.h"

// default library for watchdog, deepsleep and power saving management
// #include <ArduinoLowPower.h>     //comment out if using avr boards
#include <LowPower.h>          //use library if using avr boards

//create servo motors
ServoMotor m1(SERVO_PIN_1);
ServoMotor m2(SERVO_PIN_2);
ServoMotor m3(SERVO_PIN_3);

//manage EEPROM
EEPROM_Handler EEPROM;

//manage real time clock
Time_Handler clock;

//manage display
Display_Handler display = Display_Handler(DISPLAY_CS, DISPLAY_DC, DISPLAY_RESET);

void setup(){
    Serial.begin(9600);
    pinMode(CONFIRM_BUTTON, INPUT_PULLUP);
    pinMode(INCREASE_BUTTON, INPUT_PULLUP);
    pinMode(REALTIME_CLK_SQW, INPUT_PULLUP);
    m1.Init();
    m2.Init();
    m3.Init();
    clock.Init();
    display.Init();
    
    LowPower.attachInterruptWakeup(REALTIME_CLK_SQW, wakeup_with_turn, CHANGE);
    LowPower.attachInterruptWakeup(CONFIRM_BUTTON, wakeup, CHANGE);

    clock.setAlarm(EEPROM.Read().rotation_time);

    bool setClock = true;
    setTime(setClock);
}

void sleep(){
    // power off display (probably via digital pin and transistor/ mosfet)
    m1.disable();
    m2.disable();
    m3.disable();
    LowPower.deepSleep();
}

void wakeup_with_turn(){
    turn_motor_flag = true;
    wakeup();
}

void wakeup(){
    // power on display (probably via digital pin and transistor/ mosfet)
    m1.enable();
    m2.enable();
    m3.enable();
    last_action = millis();
}

// checks if confirm button is pushed and waits for release
bool confirmButtonPushed(){
    // negate digigalRead() because PULL_UP resistor is used instead of PULL_DOWN
    bool state = !digitalRead(CONFIRM_BUTTON);
    if(!state)
        return false;
    while(state){
        state = !digitalRead(CONFIRM_BUTTON);
    }
    return true;
}

// checks if increase button is pushed and waits for release
bool increaseButtonPushed(){
    // negate digigalRead() because PULL_UP resistor is used instead of PULL_DOWN
    bool state = !digitalRead(INCREASE_BUTTON);
    if(!state)
        return false;
    while(state){
        state = !digitalRead(INCREASE_BUTTON);
    }
    return true;
}

// if the parameter is set to true, the RTC time will be set.
// otherwise the time for when the rotations will occur will be set.
void setTime(bool setClock){
    TimeHighlighting highlight = hours;
    Time time = (setClock ? clock.getTime() : EEPROM.Read().rotation_time);
    while(true){
        DisplayTime dt;
        dt.time = time;
        dt.time_highlight = highlight;
        display.handle_time_setting(dt);

        if(confirmButtonPushed()){
            //? this comparison might not be legal
            if(highlight<seconds)
                highlight++;
            else{
                if(setClock)
                    clock.setTime(time);
                else{
                    EEPROM_DATA data = EEPROM.Read();
                    data.rotation_time = time;
                    EEPROM.Write(data);
                    clock.setAlarm(time);
                }
                return;
            }
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

// manages all aspects of the rotation setting interaction
void setRotations(){
    EEPROM_DATA data = EEPROM.Read();
    uint16_t rotations = data.rotation_amount;
    while(true){
        display.handle_rotation_setting(rotations);
        if(confirmButtonPushed()){
            data.rotation_amount = rotations;
            EEPROM.Write(data);
        }
        else if(increaseButtonPushed()){
            rotations += AMOUNT_PER_INCREASE_BUTTON_PUSHED;
            rotations %= (MAX_NUMBER_OF_ROTATIONS+1);
        }
    }
}


// declared volatile since its' value can change inside an interrupt
volatile unsigned long last_action = millis(); 
volatile bool turn_motor_flag = false;

MenuSelection menu_status = none;

void loop(){
    // updates the timestamp of the last user input
    if(!digitalRead(INCREASE_BUTTON) || !digitalRead(CONFIRM_BUTTON) || last_action>millis())
        last_action = millis();

    display.handle_menu(menu_status);
    switch(menu_status){
        // no button selected
        case none:
            if(increaseButtonPushed())
                menu_status = set_time;

            break;
        
        // set turn time menu button currently selected
        case set_time:
            if(increaseButtonPushed())
                menu_status = set_rotations;

            if(confirmButtonPushed()){
                menu_status = none;
                setTime(false);
            }
            break;

        // set rotations menu button currently selected
        case set_rotations:
            if(increaseButtonPushed())
                menu_status = reset_to_factory_settings;
            
            if(confirmButtonPushed()){
                menu_status = none;
                setRotations();
            }
            break;
        
        // reset button currently selected
        case reset_to_factory_settings:
            if(increaseButtonPushed())
                menu_status = none;
            
            if(confirmButtonPushed()){
                menu_status = none;
                EEPROM.Reset();
                clock.setAlarm(EEPROM.Read().rotation_time);
            }
            break;

        // just in case some bs happens
        default:
            menu_status = none;
            break;
    }

    // put arduino to sleep if more than five minutes have passed since last user input
    if(menu_status+300000 < millis())
        sleep();

    if(turn_motor_flag){
        uint16_t rotations = EEPROM.Read().rotation_amount;
        ServoMotor::SpinMultiple(m1, m2, m3, rotations);
        turn_motor_flag = false;
    }
}
