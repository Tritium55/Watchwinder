#ifndef time_handler_
#define time_handler_

#include <RTClib.h>

typedef struct time{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}Time;

class Time_Handler{
    private:
        RTC_DS3231 rtc;
    public:
        Time_Handler();
        int Init();
        Time getTime();
        void setTime(Time curr);
};

#endif //time_handler_