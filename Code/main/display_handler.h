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

// selected highlighting in he 
enum MenuSelection{
    default,
    set_time,
    set_rotations
};

class Display_Handler{
    private:
        TFT tft;
        enum last_function_call{
            handle_menu,
            handle_time_setting,
            handle_rotation_setting
        };
        last_function_call call_flag;
    public:
        Display_Handler();
        int Init();
        void handle_time_setting(DisplayTime dt);    // this function is for setting the time at which the clock will 
        void handle_rotation_setting(uint8_t n_rotations);
        void handle_menu(MenuSelection sel);
}


#endif //display_handler_