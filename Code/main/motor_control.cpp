#include "./motor_control.h"
#include "./const_settings.h"

#include <Arduino.h>


servo_motor::servo_motor(uint8_t _pin) : pin( _pin){
}

const void servo_motor::init(void) {
    servo.attach(pin);
    this->home();
}

// TODO
//? BULLSHIT
const void servo_motor::slow_write(uint8_t angle){
    //set servo angle limits
    if(angle < SERVO_LOW_LIMIT)
        angle = SERVO_LOW_LIMIT;

    if(angle > SERVO_HIGH_LIMIT)
        angle = SERVO_HIGH_LIMIT;

    //reads current angle of servo
    int currAngle = servo.read();

    if(angle >= currAngle){
        while(currAngle < angle){
            servo.write(currAngle);
            delay(SERVO_SPEED);
            currAngle++;
        }
    }
    else{
        while(currAngle > angle){
            servo.write(currAngle);
            delay(SERVO_SPEED);
            currAngle--;
        }
    }
}


const void servo_motor::home(void){
    slow_write(90);
    delay(2000);
}

// TODO: VERY IMPORTANT TO OPTIMIZE (unless SpinMultiple works)
const void servo_motor::spin_once(void){
    slow_write(0);
    delay(3000);
    slow_write(90);
    delay(3000);
    slow_write(180);
    delay(3000);
    slow_write(90);
    delay(3000);
}

const void servo_motor::spin(uint16_t turns){
    this->home();
    for(int i=0; i<turns; i++){
        this->spin_once();
        delay(300);
    }
}

// TODO optimize all of this. this shit is slow af

// getter function
Servo servo_motor::get_servo(){
    return this->servo;
}

// helper function
const void spin_multiple_helper(const servo_motor &m1, const servo_motor &m2, const servo_motor &m3, int deg){
    m1.get_servo().write(deg);
    m2.get_servo().write(deg);
    m3.get_servo().write(deg);
    delay(SERVO_SPEED);
}

const void servo_motor::spin_multiple(servo_motor &m1, servo_motor &m2, servo_motor &m3, uint16_t turns){
    m1.home();
    m2.home();
    m3.home();

    for(int deg=90; deg>SERVO_LOW_LIMIT; deg--){
        spin_multiple_helper(m1, m2, m3, deg);
    }

    for(int turn=0; turn<turns; turn++){
        // spin to max
        for(int deg=SERVO_LOW_LIMIT; deg<SERVO_HIGH_LIMIT; deg++){
            spin_multiple_helper(m1, m2, m3, deg);
        }
        // spin to min
        for(int deg=SERVO_HIGH_LIMIT; deg>SERVO_LOW_LIMIT; deg--){
            spin_multiple_helper(m1, m2, m3, deg);
        }
    }

    m1.home();
    m2.home();
    m3.home();
}

const void servo_motor::disable(void){
    servo.detach();
    //TODO: disable with mosfet
}

const void servo_motor::enable(void){
    servo.attach(this->pin);
    //TODO: enable with mosfet
}
