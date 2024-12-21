#include "./time_handler.h"
#include "./const_settings.h"

#include <Arduino.h>

time_handler::time_handler(){
}

int time_handler::init(){
    if(!rtc.begin()){
        if(!Serial)
            Serial.begin(BAUD_RATE);
        Serial.println("RTC (Real time Clock) init failed");
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

time time_handler::get_time(){
    time result;
    DateTime now = rtc.now();

    result.hours = now.hour();
    result.minutes = now.minute();
    result.seconds = now.second();
    return result;
}

// TODO: fix this
void time_handler::set_time(time current_time_of_day){
    rtc.adjust(DateTime(2025, 1, 1, current_time_of_day.hours, current_time_of_day.minutes, current_time_of_day.seconds));
}

void time_handler::set_alarm(time time_of_alarm){
    rtc.clearAlarm(1);
    rtc.setAlarm1(DateTime(2024, 1, 1, time_of_alarm.hours, time_of_alarm.minutes, time_of_alarm.seconds), DS3231_A1_Hour);
}

// probably not needed for this project
bool time_handler::lost_power(){
    return rtc.lostPower();
}
