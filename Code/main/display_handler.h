#ifndef display_handler_
#define display_handler_

#include "./const_settings.h"
#include "./time_handler.h"

#include <TFT.h>

// this is used as a parameter for selecting which time should be displayed as the one currently being changed by using the interface
enum time_highlighting{
    hours,
    minutes,
    seconds
};

typedef struct display_time_{
    time time;
    time_highlighting time_highlight;
}display_time;

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
// each state is assigned a value for loopability and rendering the buttons
enum menu_selection{
    none=-1,
    time_select=0,
    rotations_select=1,
    reset_to_factory_settings=2,
    dummy=-2   // for first render on startup
};

class display_handler{
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
        menu_selection menu_call_flag = dummy;
    public:
        display_handler(uint8_t CS, uint8_t DC, uint8_t RESET);     // constructor
        int init();
        void set_time_menu(display_time dt);    // this function is for setting the time (RTC and time of rotation)
        void set_rotations_menu(uint16_t n_rotations);
        void main_menu(menu_selection sel);
};


#endif //display_handler_
