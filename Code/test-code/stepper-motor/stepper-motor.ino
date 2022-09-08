#define dirPin 2
#define stepPin 3


void setup(){
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
}

void loop(){
  digitalWrite(dirPin, HIGH);

  for(int i=0; i<200; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

  delay(2000);

  digitalWrite(dirPin, LOW);

  for(int i=0; i<400; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(5000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }

  delay(5000);
  
}
