#include "./motor_control.h"
#include "./eeprom_handler.h"
#include "./display_handler.h"
#include "./time_handler.h"

// all user settings
#include "./const_settings.h"

// default library for watchdog, deepsleep, and power saving
#ifdef __AVR__
    #include <LowPower.h>
#else
    #include <ArduinoLowPower.h>
#endif


// declared volatile since its' value can change inside an interrupt
volatile unsigned long last_action = millis(); 
volatile bool turn_motor_flag = false;

// what the screen the display currently displays
menu_selection menu_status = none;

//create servo motors handlers
servo_motor m1(SERVO_PIN_1);
servo_motor m2(SERVO_PIN_2);
servo_motor m3(SERVO_PIN_3);

eeprom_handler eeprom;

// RTC handler
time_handler clock;

// display handler
display_handler display = display_handler(DISPLAY_CS, DISPLAY_DC, DISPLAY_RESET);

void setup(){
    Serial.begin(9600);
    pinMode(CONFIRM_BUTTON, INPUT_PULLUP);
    pinMode(INCREASE_BUTTON, INPUT_PULLUP);
    pinMode(REALTIME_CLK_SQW, INPUT_PULLUP);
    m1.init();
    m2.init();
    m3.init();
    clock.init();
    display.init();
    
    LowPower.attachInterruptWakeup(REALTIME_CLK_SQW, wakeup_with_turn, CHANGE);
    LowPower.attachInterruptWakeup(CONFIRM_BUTTON, wakeup, CHANGE);

    clock.set_alarm(eeprom.read().rotation_time);

    bool setClock = true;
    set_time(setClock);
}

void sleep(){
    // power off display (probably via digital pin and transistor/ mosfet)
    m1.disable();
    m2.disable();
    m3.disable();
    LowPower.deepSleep();
}

// this function is used when a wakeup occurs not by user input, but by the RTC
// (its time for watch winding)
void wakeup_with_turn(){
    turn_motor_flag = true;
    wakeup();
}

// default wakeup function
void wakeup(){
    // TODO power on display (probably via digital pin and transistor/ mosfet)
    // TODO power on servo mosfets
    m1.enable();
    m2.enable();
    m3.enable();
    last_action = millis();
}

// checks if confirm button is pushed and waits for release
bool confirm_button_pushed(){
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
bool increase_button_pushed(){
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
void set_time(bool set_rtc){
    time_highlighting highlight = hours;
    time time = (set_rtc ? clock.get_time() : eeprom.read().rotation_time);
    while(true){
        display_time dt;
        dt.time = time;
        dt.time_highlight = highlight;
        display.set_time_menu(dt);

        // this checks if the confirm button has been pushed
        if(confirm_button_pushed()){
            //? this comparison might not be legal
            // TODO fix this shit
            if(highlight<seconds)
                highlight++;
            else{
                if(set_rtc)
                    clock.set_time(time);
                else{
                    eeprom_data data = eeprom.read();
                    data.rotation_time = time;
                    eeprom.write(data);
                    clock.set_alarm(time);
                }
                return;
            }
        }
        else if(increase_button_pushed()){
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
void set_rotations(){
    eeprom_data data = eeprom.read();
    uint16_t rotations = data.rotation_amount;
    while(true){
        display.set_rotations_menu(rotations);
        if(confirm_button_pushed()){
            data.rotation_amount = rotations;
            eeprom.write(data);
        }
        else if(increase_button_pushed()){
            rotations += AMOUNT_PER_INCREASE_BUTTON_PUSHED;
            rotations %= (MAX_NUMBER_OF_ROTATIONS+1);
        }
    }
}


void loop(){
    // updates the timestamp of the last user input
    if(!digitalRead(INCREASE_BUTTON) || !digitalRead(CONFIRM_BUTTON) || last_action>millis())
        last_action = millis();

    display.handle_menu(menu_status);
    switch(menu_status){
        // no button selected
        case none:
            if(increase_button_pushed())
                menu_status = time_select;

            break;
        
        // set turn time menu option currently selected
        case time_select:
            if(increase_button_pushed())
                menu_status = rotations_select;

            if(confirm_button_pushed()){
                menu_status = none;
                set_time(false);
            }
            break;

        // set rotations menu button currently selected
        case rotations_select:
            if(increase_button_pushed())
                menu_status = reset_to_factory_settings;
            
            if(confirm_button_pushed()){
                menu_status = none;
                set_rotations();
            }
            break;
        
        // reset button currently selected
        case reset_to_factory_settings:
            if(increase_button_pushed())
                menu_status = none;
            
            if(confirm_button_pushed()){
                menu_status = none;
                eeprom.reset();
                clock.set_alarm(eeprom.read().rotation_time);
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
        uint16_t rotations = eeprom.read().rotation_amount;
        servo_motor::spin_multiple(m1, m2, m3, rotations);
        turn_motor_flag = false;
    }
}
