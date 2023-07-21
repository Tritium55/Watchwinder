#ifndef display_handler_
#define display_handler_

#include "./const_settings.h"

#include <Adafruit_ST7735.h>

enum DisplayMode{
    default,
    set_time,
    set_rotations,
    off
};

class Display_Handler{
    private:
        Adafruit_ST7735 tft;
    public:
        Display_Handler();
        int Init();
        void handle(DisplayMode mode);

}


#endif //display_handler_