#include "./display_handler.h"
#include "./const_settings.h"
#include "./time_handler.h"

#include <Arduino.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <SPI.h>

#define std_font &FreeSansBold9pt7b

Display_Handler::Display_Handler(){
    // TODO
    tft = TFT(DISPLAY_CS, DISPLAY_DC, DISPLAY_RESET);
}

int Display_Handler::Init(){
    // TODO
    tft.begin();
    tft.background(0, 0, 0);
    tft.setCursor(14,22);
    tft.setFont(&FreeSansBold18pt7b);
    tft.stroke(CYAN);
    tft.println("Watch Winder");
    tft.setFont(std_font)
    tft.stroke(WHITE);
    tft.print("by Tritium");
    delay(4000);
}

void Display_Handler::handle_time_setting(DisplayTime dt){
    // anti flickering because ATMEGA328 is slow
    if(last_function_call != handle_time_setting){
        tft.background(0, 0, 0);
        last_function_call = handle_time_setting;
    }

    char [20];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", dt.time.hours, dt.time.minutes, dt.time.seconds);

    //? maybe needed
    tft.setTextSize(2);

    switch(dt.time_highlight){
        case hours:
            //? idk if this works (found this in the ILI9488 src code)
            tft.setTextColor(WHITE, CYAN);
            tft.text(&buffer[0], 50, 50);
            tft.setTextColor(WHITE, BLACK);
            tft.text(&buffer[3], 50 + 2*6*2, 50);
            tft.text(&buffer[6], 50 + 4*6*2, 50);
            break;
        
        case minutes:
            //? idk if this works (found this in the ILI9488 src code)
            tft.setTextColor(WHITE, BLACK);
            tft.text(&buffer[0], 50, 50);
            tft.setTextColor(WHITE, CYAN);
            tft.text(&buffer[3], 50 + 2*6*2, 50);
            tft.setTextColor(WHITE, BLACK);
            tft.text(&buffer[6], 50 + 4*6*2, 50);
            break;
        
        case seconds:
            //? idk if this works (found this in the ILI9488 src code)
            tft.setTextColor(WHITE, BLACK);
            tft.text(&buffer[0], 50, 50);
            tft.text(&buffer[3], 50 + 2*6*2, 50);
            tft.setTextColor(WHITE, CYAN);
            tft.text(&buffer[6], 50 + 4*6*2, 50);
            break;

        default:
            if(!Serial)
                return;

            //? maybe try could be used here
            Serial.println("Error");
            return;
    }

}

void Display_Handler::handle_rotation_setting(uint16_t n_rotations){
    // anti flickering because ATMEGA328 is slow
    if(last_function_call != handle_rotation_setting){
        tft.background(0, 0, 0);
        last_function_call = handle_rotation_setting;
    }
    tft.setTextSize(2);
    tft.setTextColor(WHITE, BLACK);

    // TODO: coordinates will need to be changed
    tft.text(String(n_rotations), 50, 50);
}

void Display_Handler::handle_menu(MenuSelection sel){
    bool was_menu = function_call_flag == handle_menu;

    // anti flickering because ATMEGA328 is slow
    if(!was_menu){
        tft.background(0, 0, 0);
        function_call_flag = handle_menu;
    }

    // TODO

    // avoid unnecessary rendering
    if(was_menu && menu_call_flag==sel)
        return;

    switch(sel){
        case none:
            //TODO
            break;
        case set_time:
            //TODO
            break;
        
        case set_rotations:
            //TODO
            break;

        default:
            return;
            break;
    }

}
