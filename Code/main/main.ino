#include "./motor_control.h"
#include "./eeprom_handler.h"
#include "./display_handler.h"
#include "./time_handler.h"

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
    pinMode(CONFIRM_BUTTON, INPUT_PULLUP);
    pinMode(INCREASE_BUTTON, INPUT_PULLUP);
    m1.Init();
    m2.Init();
    m3.Init();
    clock.Init();
    display.Init();

    bool setClock = true;
    setTime(setClock);
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
            if(highlight<seconds)
                highlight++;
            else{
                if(setClock)
                    clock.setTime(time);
                else{
                    EEPROM_DATA data = EEPROM.Read();
                    data.rotation_time = time;
                    EEPROM.Write(data);
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


MenuSelection menu_status = none;
void loop(){
    /*
    m1.Home();
    delay(5000);
    m1.Spin(3);
    delay(1000);
     */

    display.handle_menu(menu_status);
    switch(menu_status){
        case none:
            if(increaseButtonPushed())
                menu_status = set_time;

            break;
        
        case set_time:
            if(increaseButtonPushed())
                menu_status = set_rotations;

            if(confirmButtonPushed()){
                menu_status = none;
                setTime(false);
            }
            break;

        case set_rotations:
            if(increaseButtonPushed())
                menu_status = reset_to_factory_settings;
            
            if(confirmButtonPushed()){
                menu_status = none;
                setRotations();
            }
            break;
        
        case reset_to_factory_settings:
            if(increaseButtonPushed())
                menu_status = none;
            
            if(confirmButtonPushed()){
                menu_status = none;
                EEPROM.Reset();
            }
            break;
    }

}
