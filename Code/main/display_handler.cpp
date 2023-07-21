#include "./display_handler.h"
#include "./const_settings.h"
#include "./time_handler.h"

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <SPI.h>

#define FreeSansBold9pt7b std_font

Display_Handler::Display_Handler(){
    // TODO: enter pin def states from const_settings
    tft = Adafruit_ST7735();
}

int Display_Handler::Init(){
    // TODO
    tft.initR(INITR_GREENTAB);
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(14,22);
    tft.setFont(&FreeSansBold18pt7b);
    tft.setTextColor(ST77XX_CYAN);
    tft.println("Watch Winder");
    tft.setFont(&std_font)
    tft.setTextColor(ST77XX_WHITE);
    tft.print("by Tritium");
    delay(2000);
}

void Display_Handler::handle(DisplayMode mode){
    switch(mode){
        case off:
            //TODO
            break;

        case set_time:
            //TODO
            break;
        
        case set_rotations:
            //TODO
            break;

        default:
            //TODO
            break;
    }

    //? possibly add delay
}
