#include "./motor_control.h"
#include "./const_settings.h"

#include <Arduino.h>


ServoMotor::ServoMotor(uint8_t _pin) : pin( _pin){
}

void ServoMotor::Init(void) {
    servo.attach(pin);
    this->Home();
}

//? BULLSHIT
void ServoMotor::slowWrite(uint8_t angle){
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


void ServoMotor::Home(void){
    slowWrite(90);
    delay(2000);
}

// TODO: VERY IMPORTANT TO OPTIMIZE
void ServoMotor::SpinOnce(void){
    slowWrite(0);
    delay(3000);
    slowWrite(90);
    delay(3000);
    slowWrite(180);
    delay(3000);
    slowWrite(90);
    delay(3000);
}

void ServoMotor::Spin(uint16_t turns){
    this->Home();
    for(int i=0; i<turns; i++){
        this->SpinOnce();
        delay(300);
    }
}

// helper function
void spin_multiple_helper(const ServoMotor &m1, const ServoMotor &m2, const ServoMotor &m3, int deg){
    m1->servo.write(deg);
    m2->servo.write(deg);
    m3->servo.write(deg);
    delay(SERVO_SPEED);
}

static void ServoMotor::SpinMultiple(const ServoMotor &m1, const ServoMotor &m2, const ServoMotor &m3, uint16_t turns){
    m1->Home();
    m2->Home();
    m3->Home();

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

    m1->Home();
    m2->Home();
    m3->Home();
}

void ServoMotor::disable(void){
    servo.detach();
    //TODO: disable with transistor/ mosfet
}

void ServoMotor::enable(void){
    servo.attach(pin);
    //TODO: enable with transistor/ mosfet
}
