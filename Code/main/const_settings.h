#ifndef const_settings_h_
#define const_settings_h_


//define servo pins
#define SERVO_PIN_1 2
#define SERVO_PIN_2 3
#define SERVO_PIN_3 4

//define servo angle limits
#define SERVO_LOW_LIMIT 10
#define SERVO_HIGH_LIMIT 170

//define turn speed of servo
#define SERVO_SPEED 25               //the lower, the faster


//define DS3231 realtime clock pins
#define REALTIME_CLK_SDA A4
#define REALTIME_CLK_SCL A5


//define display pins
#define DISPLAY_CS 10
#define DISPLAY_DC 9
#define DISPLAY_RESET 8


//define button pins
#define CONFIRM_BUTTON 6
#define INCREASE_BUTTON 5

//define rotation settings
#define MAX_NUMBER_OF_ROTATIONS 1000
#define AMOUNT_PER_INCREASE_BUTTON_PUSHED 25

#endif  //const_settings_h_
