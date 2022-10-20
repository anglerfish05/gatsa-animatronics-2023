#include <FastLED.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <Wire.h>
#include <pcmRF.h>
#include <pcmConfig.h>
#include <TMRpcm.h>


// general constants
bool start = false;
bool end1 = false;
bool end2 = false;

// UltraSonic Sensor constants 
const int trigPin = 2;
const int echoPin = 1;
long distance;
long duration;

// SD shield constants
const int sdPin = 3;
TMRpcm tmrpcm;

// audio settings
TMRpcm audio;

// button constants
const int button1Pin = 4; // attractions
bool button1 = false;
const int button2Pin = 5; // food
bool button2 = false;
const int button3Pin = 6; // state parks
bool button3 = false;
const int button4Pin = 7; // historical sites
bool button4 = false;
const int button5Pin = 8; // historical figures
bool button5 = false;

const int button6Pin = 9; // food
bool button6 = false;
const int button7Pin = 10; // gas
bool button7 = false;

// const int buttonOR = 13; // ultrasonic override

void ultrasonic() {
  // clears the trigPin
  digitalWrite (trigPin, LOW);
  delayMicroseconds (2);
  // sets the trigPin on HIGH state for 10 microseconds
  digitalWrite (trigPin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPin, LOW); 
  // reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn (echoPin, HIGH);
  // calculating the distance
  distance = duration * 0.0343/2; // cm
}

void ultrago() {
  if (distance > 0 && distance <= 50 ) {
    start = true;
  }
  else if (distance > 50) {
    end1 = true;
  }
}

void buttonsAllOn() {
  button1 = true;
  button2 = true;
  button3 = true;
  button4 = true;
  button5 = true;
  button6 = true;
  button7 = true;
}
void buttonsAllOff() {
  button1 = false;
  button2 = false;
  button3 = false;
  button4 = false;
  button5 = false;
  button6 = false;
  button7 = false;
}
/*void setButtonsOff(int x) {
  for( int i = 1 ; i <= 7 ; i++ ) {
    if( i != x ) {
       
    }
  }
} */

Motor motor1(5);

class Motor {
  Servo servo; 
  int pos;
  int increment;
  int updateInterval;
  unsigned long lastUpdate;
}

public:
  Motor(int interval) {
    updateInterval = interval;
    increment = 1;
  }

void Attach(int pin) {
  servo.attach(pin);
}

void Detach() {
  servo.detach();
}

void Update() {
  if ((millis() - lastUpdate) > updateInterval) { // time to update
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      Serial.println(pos);
      if ((pos >= 100) || (pos <= 0)) { // end of sweep
        // reverse direction
        increment = -increment;
      }
    }
}

void setup() {
  // put your setup code here, to run once:
  
  // UltraSonic Sensor
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);

  // tmrpcm
  audio.speakerPin = 12;
  audio.setVolume(5); // 0-7

  // motor
  motor1.Attach(11);
}

void loop() {
  // put your main code here, to run repeatedly:
   
   ultrasonic();
   ultrago();
  
  // when ultrasonic detects
   while(start) {
    // intro plays
    if(start) {
      tmrpcm.play( "intro.wav" ); // PLACE FILE
      while(audio.isPlaying() == 1) {
        motor1.Update();
      }
    }
    
    if(audio.isPlaying() == 0) {
      buttonsAllOn();
    }
    
    if( digitalRead(button1Pin) == HIGH && button1 ) {
      button2 = false;
      button3 = false;
      button4 = false;
      button5 = false;
      button6 = false;
      button7 = false;

      tmrpcm.play( "attractions.wav" );
      while(audio.isPlaying() == 1) {
        motor1.Update();
      }
      Wire.beginTransmission(9);
      Wire.write(1);
      Wire.endTransmission();
    }
    else if( digitalRead(button2Pin) == HIGH && button2 ) {
      button1 = false;
      button3 = false;
      button4 = false;
      button5 = false;
      button6 = false;
      button7 = false;

      tmrpcm.play( "food1.wav" );
      while(audio.isPlaying() == 1) {
        motor1.Update();
      }
      Wire.beginTransmission(9);
      Wire.write(2);
      Wire.endTransmission();
    }
    else if( digitalRead(button3Pin) == HIGH && button3 ) {
      button1 = false;
      button2 = false;
      button4 = false;
      button5 = false;
      button6 = false;
      button7 = false;

      tmrpcm.play( "stateparks.wav" );
      while(audio.isPlaying() == 1) {
        motor1.Update();
      }
      Wire.beginTransmission(9);
      Wire.write(3);
      Wire.endTransmission();
    }
    else if( digitalRead(button4Pin) == HIGH && button4 ) {
      button1 = false;
      button2 = false;
      button3 = false;
      button5 = false;
      button6 = false;
      button7 = false;

      tmrpcm.play( "historicalsites.wav" );
      Wire.beginTransmission(9);
      Wire.write(4);
      Wire.endTransmission();
      
    }
    else if( digitalRead(button5Pin) == HIGH && button5 ) {
      button1 = false;
      button2 = false;
      button3 = false;
      button4 = false;
      button6 = false;
      button7 = false;

      tmrpcm.play( "historicalfigures.wav" );
      while(audio.isPlaying() == 1) {
        motor1.Update();
      }
      Wire.beginTransmission(9);
      Wire.write(5);
      Wire.endTransmission();
    }
    else if( digitalRead(button6Pin) == HIGH && button6 ) {
      button1 = false;
      button2 = false;
      button3 = false;
      button4 = false;
      button5 = false;
      button7 = false;

      tmrpcm.play( "food2.wav" );
      while(audio.isPlaying() == 1) {
        motor1.Update();
      }
      Wire.beginTransmission(9);
      Wire.write(6);
      Wire.endTransmission();
    }
    else if( digitalRead(button7Pin == HIGH && button7 ) {
      button1 = false;
      button2 = false;
      button3 = false;
      button4 = false;
      button5 = false;
      button6 = false;

      tmrpcm.play( "gas.wav" );
      while(audio.isPlaying() == 1) {
        motor1.Update();
      }
      Wire.beginTransmission(9);
      Wire.write(7);
      Wire.endTransmission();
    }
   
    if ( end1 ) {
      tmrpcm.play( "ending.wav" );
      while (audio.isPlaying() == 1) {
        motor1.Update();
      }
      return;
    }
   }
 
}
