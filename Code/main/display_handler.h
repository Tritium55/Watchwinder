#ifndef display_handler_
#define display_handler_

#include "./const_settings.h"

#include <TFT.h>

enum TimeSelection{
    first,
    second,
    third
};

typedef struct display_time{
    Time time;
    TimeSelection time_sel;
}DisplayTime;

enum DisplayMode{
    default,
    set_time,
    set_rotations,
    off
};

class Display_Handler{
    private:
        TFT tft;
    public:
        Display_Handler();
        int Init();
        void handle_time_setting(DisplayTime dt);
        void handle(DisplayMode mode);

}


#endif //display_handler_