#ifndef time_handler_
#define time_handler_

#include <RTClib.h>

typedef struct time{
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
}Time;

class Time_Handler{
    private:
        RTC_DS3231 rtc;
    public:
        Time_Handler();
        int Init();
        Time getTime();
        void setTime(Time curr);
        bool lostPower();
};

#endif //time_handler_