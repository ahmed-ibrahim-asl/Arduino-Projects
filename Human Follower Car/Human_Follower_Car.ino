#include <Servo.h>

#define RIGHT_IR 6
#define LEFT_IR 7

#define ultraSonic_trig  10
#define ultraSonic_echo 11
#define max_distance    20

Servo myservo;
#define servoPin 8
int pos = 0;
unsigned long past = 0;

// MotorsPin: 2 3 4 5 


void setup() {
  pinMode(RIGHT_IR, INPUT);
  pinMode(LEFT_IR, INPUT);

  myservo.attach(servoPin);


  // Motor pins
  for(int i = 2; i<=5; i++)
    pinMode(2, OUTPUT);


  //debugger
  Serial.begin(9600);
  



  pinMode(ultraSonic_trig, OUTPUT);
  pinMode(ultraSonic_echo, INPUT);

}


inline float grapDistance(){
  delay(10);
  // Clear trigger pin
  digitalWrite(ultraSonic_trig, LOW);
  delayMicroseconds(2);

  // Set trigger pin high for 10 microseconds
  digitalWrite(ultraSonic_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraSonic_trig, LOW);



  return (pulseIn(ultraSonic_echo, HIGH)/2)*0.034;
}

void loop() {
  

  while(digitalRead(RIGHT_IR) == 1 && digitalRead(LEFT_IR) == 1){
   
    for(pos = 90; (pos <= 180 && (digitalRead(RIGHT_IR) == 1 && digitalRead(LEFT_IR) == 1)); pos += 1){
      
      myservo.write(pos);

      delay(15);
    } 
      if(digitalRead(RIGHT_IR) == 0 || digitalRead(LEFT_IR) == 0)
        break;

    for(pos = 180; (pos >= 0 && (digitalRead(RIGHT_IR) == 1 && digitalRead(LEFT_IR) == 1)); pos-= 1) {
      
      myservo.write(pos);
      delay(15);
    }
      if(digitalRead(RIGHT_IR) == 0 || digitalRead(LEFT_IR) == 0)
        break;
    
    for(pos = 0; (pos<=90 && (digitalRead(RIGHT_IR) == 1 && digitalRead(LEFT_IR) == 1)); pos += 1) {
      
      myservo.write(pos);
      delay(15);
    }

      if(digitalRead(RIGHT_IR) == 0 || digitalRead(LEFT_IR) == 0)
        break;
  }

  // we go left
  if((digitalRead(RIGHT_IR) == 1 && digitalRead(LEFT_IR) == 0) && (pos>=90 || pos<=180)){
    
   
    while((digitalRead(RIGHT_IR) == 1 && digitalRead(LEFT_IR) == 0)){
      pos = 90;
      myservo.write(pos);
      LEFT();
    }

    if(digitalRead(RIGHT_IR) == 1 && digitalRead(LEFT_IR) == 1)
      STOP();
  }
  

  // we go right 
  if((digitalRead(RIGHT_IR) == 0 && digitalRead(LEFT_IR) == 1) && (pos>=0 || pos<=90)){
    
   
    while((digitalRead(RIGHT_IR) == 0 && digitalRead(LEFT_IR) == 1)){      

      RIGHT();
      pos = 90;
      myservo.write(pos);

    }

    if(digitalRead(RIGHT_IR) == 1 && digitalRead(LEFT_IR) == 1){   
      STOP();
      pos = 90;
      myservo.write(pos);
    }
  }


  // forward()
  if((digitalRead(RIGHT_IR) == 0 && digitalRead(LEFT_IR) == 0) && pos == 90){
    
    while(grapDistance() <= 20)
      FORWARD();

    if(grapDistance() >= 20 && (digitalRead(RIGHT_IR) == 1 && digitalRead(LEFT_IR) == 1))
      STOP();
  }


  if(digitalRead(RIGHT_IR) == 1 && digitalRead(LEFT_IR) == 1)
    STOP();


    
}


void STOP(){
  digitalWrite(2, 0);
  digitalWrite(3, 0);

  digitalWrite(4, 0);
  digitalWrite(5, 0);
}

void LEFT(){
  digitalWrite(2, 1);
  digitalWrite(3, 0);

  digitalWrite(4, 1);
  digitalWrite(5, 0);
}


void RIGHT(){
  digitalWrite(2, 0);
  digitalWrite(3, 1);

  digitalWrite(4, 0);
  digitalWrite(5, 1);
}


void FORWARD(){
  digitalWrite(2, 1);
  digitalWrite(3, 0);

  digitalWrite(4, 0);
  digitalWrite(5, 1);
}

void BACKWARD(){
  digitalWrite(2, 0);
  digitalWrite(3, 1);

  digitalWrite(4, 1);
  digitalWrite(5, 0);
}