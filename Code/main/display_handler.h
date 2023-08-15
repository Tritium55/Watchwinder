#ifndef display_handler_
#define display_handler_

#include "./const_settings.h"
#include "./time_handler.h"

#include <TFT.h>

enum TimeHighlighting{
    hours,
    minutes,
    seconds
};

typedef struct display_time{
    Time time;
    TimeHighlighting time_highlight;
}DisplayTime;

/*
// struct for coordinates for print functions
typedef struct coord{
    uint8_t x;
    uint8_t y;
}Coord;
 */

/*
// struct for red green and blue values for print functions
typedef struct color{
    uint8_t r;
    uint8_t g;
    uint8_t b;
}Color;
 */

// select highlighting in menu handler
enum MenuSelection{
    none,
    set_time,
    set_rotations,
    reset_to_factory_settings,
    dummy   // for first render on startup
};

class Display_Handler{
    private:
        TFT tft;
        enum last_function_call{
            handle_menu,
            handle_time_setting,
            handle_rotation_setting,
            dummy   // for first render on startup
        };
        // dummy flags on startup so that the display doesn't blank
        last_function_call function_call_flag = dummy;
        MenuSelection menu_call_flag = dummy;
    public:
        Display_Handler();
        int Init();
        void handle_time_setting(DisplayTime dt);    // this function is for setting the time (RTC and time of rotation)
        void handle_rotation_setting(uint16_t n_rotations);
        void handle_menu(MenuSelection sel);
}


#endif //display_handler_