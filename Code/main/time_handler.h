#ifndef time_handler_
#define time_handler_

#include <stdint.h>
#include <RTClib.h>

typedef struct time_{
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
}time;

class time_handler{
    private:
        RTC_DS3231 rtc;     // real time clock object
    public:
        time_handler();
        int init();
        time get_time();
        void set_time(time current_time_of_day);
        void set_alarm(time time_of_alarm);
        bool lost_power();
};

#endif //time_handler_
