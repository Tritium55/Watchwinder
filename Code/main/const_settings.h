#ifndef const_settings_h_
#define const_settings_h_


// servo pins
#define SERVO_PIN_1 5
#define SERVO_PIN_2 6
#define SERVO_PIN_3 7

// servo angle limits
#define SERVO_LOW_LIMIT 10
#define SERVO_HIGH_LIMIT 170

// turn speed of servo
#define SERVO_SPEED 15               //the lower, the faster


// DS3231 realtime clock pins
#define REALTIME_CLK_SDA A4
#define REALTIME_CLK_SCL A5
#define REALTIME_CLK_SQW 2


// display pins
#define DISPLAY_CS 10
#define DISPLAY_DC 9
#define DISPLAY_RESET 8


// button pins
#define CONFIRM_BUTTON 3
#define INCREASE_BUTTON 4

// rotation settings
#define MAX_NUMBER_OF_ROTATIONS 1000
#define AMOUNT_PER_INCREASE_BUTTON_PUSHED 25

// baud rate
#define BAUD_RATE 9600
#endif  //const_settings_h_
