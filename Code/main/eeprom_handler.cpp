#include "./eeprom_handler.h"
#include "./const_settings.h"
#include "./factory_settings.h"

#include <Arduino.h>
#include <EEPROM.h>

// set to true for eeprom debug mode
static bool debug_mode = false;
#include <assert.h>
#define __ASSERT_USE_STDERR

#define struct eeprom_data eeprom_data;

eeprom_handler::eeprom_handler(){ 
    // check if settings have ever been written onto the eeprom (if not, write them for the first time)
    bool eeprom_settings_saved = EEPROM.get(sizeof(eeprom_data), bool);
    if(eeprom_settings_saved)
        return;
    
    // set factory settings if necessary
    this->reset();    // this loads the factory settings into onto the EEPROM on first startup
   

    // debug stuff
    if(debug_mode){
        if(!Serial)
            Serial.begin(BAUD_RATE);
        
        assert(EEPROM.length() > sizeof(eeprom_data));
    }
}

// TODO: make return value a pointer
eeprom_data eeprom_handler::read(){
    return EEPROM.get(0, eeprom_data);
}

void eeprom_handler::write(eeprom_data &data) {
    EEPROM.put(0, data);
}

void eeprom_handler::reset(){
    eeprom_data temp;
    temp.rotation_amount = NUMBER_OF_ROTATIONS;
    temp.rotation_time.hours = TIME_FOR_ROTATION_HOURS;
    temp.rotation_time.minutes = TIME_FOR_ROTATION_MINUTES;
    temp.rotation_time.seconds = TIME_FOR_ROTATION_SECONDS;
    EEPROM.put(0, temp);
    // set flag, that the eeprom has been written to
    EEPROM.put(sizeof(eeprom_data), true);
}

// handle diagnostic informations given by assertion and abort program execution:
static void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
    // transmit diagnostic informations through serial link. 
    Serial.println(__func);
    Serial.println(__file);
    Serial.println(__lineno, DEC);
    Serial.println(__sexp);
    Serial.flush();
    // abort program execution.
    abort();
}
