#include "./eeprom_handler.h"
#include "./settings.h"
#include "./factory_settings.h"

#include <Arduino.h>
#include <EEPROM.h>
#include "eeprom_handler.h"

#define struct EEPROM_DATA EEPROM_DATA;

EEPROM_Handler::EEPROM_Handler(){
    // return if factory settings haven't been changed
    if(!EEPROM.get(sizeof(EEPROM_DATA), bool))
        return;
    
    // set factory settings if necessary
    Reset();
}

EEPROM_DATA EEPROM_Handler::Read(){
    return EEPROM.get(0, EEPROM_DATA);
}

void EEPROM_Handler::Write(EEPROM_DATA &data) {
    EEPROM.put(0, data);
    EEPROM.put(sizeof(EEPROM_DATA), true); // set flag for custom settings
}

void EEPROM_Handler::Reset(){
    EEPROM_DATA temp;
    temp.rotation_amount = NUMBER_OF_ROTATIONS;
    temp.rotation_time.hour = TIME_FOR_ROTATION_HOUR;
    temp.rotation_time.minute = TIME_FOR_ROTATION_MINUTE;
    temp.rotation_time.second = TIME_FOR_ROTATION_SECOND;
    EEPROM.put(0, temp);
    EEPROM.put(sizeof(EEPROM_DATA), false);
}