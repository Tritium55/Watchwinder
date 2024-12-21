// class for eeprom handling
#ifndef eeprom_handler_
#define eeprom_handler_

#include <stdint.h>
#include "time_handler.h"

typedef struct eeprom_data_{
    time rotation_time;         // time of day when the rotations occur
    uint16_t rotation_amount;   // the amount of rotations made per day
}eeprom_data;

class eeprom_handler{
    public:
        eeprom_handler();
        void write(eeprom_data &data);
        eeprom_data read();
        void reset();     // reset current settings to factory settings
};

#endif //eeprom_handler_
