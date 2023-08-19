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
    //disables 32K pin on rtc
    rtc.disable32K();
    rtc.clearAlarm(1);
    rtc.clearAlarm(2);
    rtc.writeSqwPinMode(DS3231_OFF);
    rtc.disableAlarm(2);
    return 0;
}

Time Time_Handler::getTime(){
    Time result;
    DateTime now = rtc.now();

    result.hours = now.hour();
    result.minutes = now.minute();
    result.seconds = now.second();
    return result;
}

//TODO
void Time_Handler::setTime(Time curr){
    rtc.adjust(DateTime(F(__DATE__), curr.hours, curr.minutes, curr.seconds));
}

void Time_Handler::setAlarm(Time curr){
    rtc.clearAlarm(1);
    rtc.setAlarm1(DateTime(2023, 8, 19, curr.hours, curr.minutes, curr.seconds), DS3231_A1_Hour);
}

// probably not needed for this project
bool Time_Handler::lostPower(){
    return rtc.lostPower();
}