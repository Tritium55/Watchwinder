// class for eeprom handling
#ifndef eeprom_handler_
#define eeprom_handler_

#include "time_handler.h"

typedef struct EEPROM_DATA_{
    Time rotation_time;
    uint8_t rotation_amount;
}EEPROM_DATA;

class EEPROM_Handler{
    public:
        EEPROM_Handler();
        void Write(EEPROM_DATA &data);
        EEPROM_DATA Read();
        void Reset();     // reset current settings to factory settings
};

#endif //eeprom_handler_