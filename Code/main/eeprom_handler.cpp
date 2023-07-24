#include "./eeprom_handler.h"
#include "./const_settings.h"
#include "./factory_settings.h"

#include <Arduino.h>
#include <EEPROM.h>

#define struct EEPROM_DATA EEPROM_DATA;

EEPROM_Handler::EEPROM_Handler(){
    // return if factory settings haven't been changed
    if(!EEPROM.get(sizeof(EEPROM_DATA), bool))
        return;
    
    // set factory settings if necessary
    Reset();    // this loads the factory settings into onto the EEPROM on first startup
}

EEPROM_DATA EEPROM_Handler::Read(){
    return EEPROM.get(0, EEPROM_DATA);
}

void EEPROM_Handler::Write(EEPROM_DATA &data) {
    EEPROM.put(0, data);
    // set flag for custom settings - prevents overwriting custom settings on startup
    EEPROM.put(sizeof(EEPROM_DATA), true);
}

void EEPROM_Handler::Reset(){
    EEPROM_DATA temp;
    temp.rotation_amount = NUMBER_OF_ROTATIONS;
    temp.rotation_time.hour = TIME_FOR_ROTATION_HOUR;
    temp.rotation_time.minute = TIME_FOR_ROTATION_MINUTE;
    temp.rotation_time.second = TIME_FOR_ROTATION_SECOND;
    EEPROM.put(0, temp);
    // unset custom settings flag
    EEPROM.put(sizeof(EEPROM_DATA), false);
}