#include "./display_handler.h"

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <SPI.h>

#define std_font FreeSansBold9pt7b

display_handler::display_handler(uint8_t CS, uint8_t DC, uint8_t RESET){
    // TODO
    tft = TFT(CS, DC, RESET);
}

int display_handler::init(){
    // TODO
    tft.begin();
    tft.background(0, 0, 0);
    tft.setCursor(14,22);
    tft.setFont(FreeSansBold18pt7b);
    tft.stroke(CYAN);
    tft.println("Watch Winder");
    tft.setFont(std_font)
    tft.stroke(WHITE);
    tft.print("by Tritium");
    delay(4000);
}

void display_handler::set_time_menu(display_time dt){
    // anti flickering because ATMEGA328 is slow
    if(last_function_call != handle_time_setting){
        tft.background(0, 0, 0);
        last_function_call = handle_time_setting;
    }

    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", dt.time.hours, dt.time.minutes, dt.time.seconds);

    //? maybe needed
    tft.setTextSize(2);

    switch(dt.time_highlight){
        case hours:
            //? idk if this works (found this in the ILI9488 src code)
            tft.setTextColor(ST7735_WHITE, ST7735_CYAN);
            tft.text(&buffer[0], 50, 50);
            tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
            tft.text(&buffer[3], 50 + 2*6*2, 50);
            tft.text(&buffer[6], 50 + 4*6*2, 50);
            break;
        
        case minutes:
            //? idk if this works (found this in the ILI9488 src code)
            tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
            tft.text(&buffer[0], 50, 50);
            tft.setTextColor(ST7735_WHITE, ST7735_CYAN);
            tft.text(&buffer[3], 50 + 2*6*2, 50);
            tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
            tft.text(&buffer[6], 50 + 4*6*2, 50);
            break;
        
        case seconds:
            //? idk if this works (found this in the ILI9488 src code)
            tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
            tft.text(&buffer[0], 50, 50);
            tft.text(&buffer[3], 50 + 2*6*2, 50);
            tft.setTextColor(ST7735_WHITE, ST7735_CYAN);
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

void display_handler::set_rotations_menu(uint16_t n_rotations){
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

String menu_selection_to_string(menu_selection sel){
    String result;
    switch(sel){
        case set_time:
            result = "Set Time";
            break;

        case set_rotations:
            result = "Rotations";
            break;
        
        case reset_to_factory_settings:
            result = "Reset";
            break;
        
        default:
            result = NULL;
            break;
    }
    return result;
}

void display_handler::main_menu(menu_selection sel){
    // TODO
    bool was_menu = (bool) function_call_flag == handle_menu;

    // anti flickering (ATMEGA328 is slow)
    if(!was_menu){
        function_call_flag = handle_menu;
        tft.fillScreen(ST7735_BLACK);
    }

    // avoid unnecessary rendering
    if(was_menu && (menu_call_flag==sel))
        return;

    tft.setTextSize(2);
    tft.stroke(255, 255, 255);

    // display all options as buttons
    int buttonWidth = 100;
    int buttonHeight = 30;
    int buttonGap = 5;
    int numberOfButtons = 3;
    int startX = (tft.width() - numberOfButtons * buttonWidth + (numberOfButtons-1) * buttonGap)) / 2;
    int startY = tft.height() - buttonHeight - 10;

    //? might need to declare enum menu_selection as enum class menu_selection because of int comparability restrictions
    for(int i=0; i<numberOfButtons; i++){
        int buttonX = startX + (buttonWidth + buttonGap) * i;
        int buttonY = startY;

        tft.stroke(255, 255, 255);
        if(sel == i){
            tft.fillRoundRect(buttonX, buttonY, buttonWidth, buttonHeight, 5, TFT_YELLOW);
            tft.stroke(0, 0, 0); // Set text color to black for the highlighted option
        }
        else{
            tft.fillRoundRect(buttonX, buttonY, buttonWidth, buttonHeight, 5, TFT_BLUE);
        }

        //? Todo: might need to adjust cords for centered button text/labels
        tft.text(menu_selection_to_string(sel), buttonX + 10, buttonY + 8);
    }

}
