#include <Servo.h>

#define servoPin 8

Servo servo;


void setup(){
  servo.attach(servoPin);
}

void loop(){
  servo.write(0);       //set angle to 0
  
  delay(3000);
  
  servo.write(90);      //set angle to 90

  delay(3000);

  servo.write(180);     //set angle to 180

  delay(3000);

  servo.write(20);      //set angle to 20

  delay(3000);
  
}
