#include "./time_handler.h"

#include <Arduino.h>

Time_Handler::Time_Handler(){
}

int Time_Handler::Init(){
    if(!rtc.begin()){
        Serial.println("RTC (Real Time Clock) init failed");
        Serial.flush();
        abort();
    }
    return 0;
}

Time Time_Handler::getTime(){
    Time result;
    DateTime now = rtc.now();

    result.hour = now.hour();
    result.minute = now.minute();
    result.second = now.second();
    return result;
}

//TODO
void Time_Handler::setTime(Time curr){
    rtc.adjust(DateTime(F(__DATE__), curr.hour, curr.minute, curr.second));
}

bool Time_Handler::lostPower(){
    return rtc.lostPower();
}