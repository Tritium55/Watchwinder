#include <Adafruit_ST7735.h>        //hardware specific library
#include <SPI.h>                    //communication interface

Adafruit_ST7735 tft = Adafruit_ST7735(10, 9, 8);

void setup(){
    tft.initR(INITR_GREENTAB);
    
}

void loop(){
    tft.fillScreen(ST77XX_BLACK);
    delay(3000);
    tft.fillScreen(ST77XX_WHITE);
    delay(3000);
    tft.fillScreen(ST77XX_BLUE);
    delay(3000);
    tft.fillScreen(ST77XX_RED);
    delay(3000);
    tft.fillScreen(ST77XX_GREEN);
    delay(3000);
}