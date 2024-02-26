#include "./eeprom_handler.h"
#include "./const_settings.h"
#include "./factory_settings.h"

#include <Arduino.h>
#include <EEPROM.h>

#define struct EEPROM_DATA EEPROM_DATA;

EEPROM_Handler::EEPROM_Handler(){
    // check if settings have ever been written onto the eeprom (if not, write them for the first time)
    bool eeprom_settings_saved = EEPROM.get(sizeof(EEPROM_DATA), bool);
    if(eeprom_settings_saved)
        return;
    
    // set factory settings if necessary
    this->Reset();    // this loads the factory settings into onto the EEPROM on first startup
}

// TODO: make return value a pointer
EEPROM_DATA EEPROM_Handler::Read(){
    return EEPROM.get(0, EEPROM_DATA);
}

void EEPROM_Handler::Write(EEPROM_DATA &data) {
    EEPROM.put(0, data);
}

void EEPROM_Handler::Reset(){
    EEPROM_DATA temp;
    temp.rotation_amount = NUMBER_OF_ROTATIONS;
    temp.rotation_time.hour = TIME_FOR_ROTATION_HOUR;
    temp.rotation_time.minute = TIME_FOR_ROTATION_MINUTE;
    temp.rotation_time.second = TIME_FOR_ROTATION_SECOND;
    EEPROM.put(0, temp);
    // set flag, that the eeprom has been written to
    EEPROM.put(sizeof(EEPROM_DATA), true);
}