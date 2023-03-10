#include <Servo.h>
#include <Wire.h>

// motor
Servo motor;
int motorControl(int value) {
  motor.write(map(value, -100, 100, 1000, 2000));
}


// pneumatics
int signalPin1 = 8;
int signalPin2 = 9;

//i2c constants
String answer = "on";
byte x = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  motor.attach(4);
  
  pinMode(signalPin1, OUTPUT);
  pinMode(signalPin2, OUTPUT);

  Wire.begin(9);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void receiveEvent() {
  x = Wire.read();
}

void requestEvent() {
  byte response[2]; 

  for( byte i = 0 ; i < 2 ; i++ ) {
    response[i] = (byte)answer.charAt(i);
  }
  Wire.write(response, sizeof(response));
}

void loop() {
  // put your main code here, to run repeatedly:
  if( x == 1 ) { // attractions
    motorControl(100);
  }
  else if( x == 3 ) { // state parks
    motorControl(100);
  }
  else if( x == 4 ) { // historical sites
    motorControl(100);
  }
  else if( x == 5 ) { // historical figures
    lightsOn();
    digitalWrite(signalPin1, HIGH);
    digitalWrite(signalPin2, HIGH);
    delay(5000);
    digitalWrite(signalPin1, LOW);
    digitalWrite(signalPin2, LOW);
  }
  else if ( x == 2 ) { // everything off
    
  }
}
