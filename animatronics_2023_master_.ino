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
const int trigPin = 3;
const int echoPin = 2;
long distance;
long duration;

// SD shield constants
const int sdPin = 4;
TMRpcm tmrpcm;

// audio settings
TMRpcm audio;

// button constants
const int button1Pin = 5; // attractions
const int button2Pin = 6; // food
const int button3Pin = 7; // state parks
const int button4Pin = 8; // historical sites
const int button5Pin = 9; // historical figures

const int button6Pin = 10; // food
const int button7Pin = 11; // gas

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

void setup() {
  // put your setup code here, to run once:
  // UltraSonic Sensor
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  
  audio.speakerPin = 12;
}

void loop() {
  // put your main code here, to run repeatedly:
   ultrasonic();
   ultrago();
  
  // when ultrasonic detects
   while(start) {
    if(start) {
      tmrpcm.play( "intro.wav" ); // PLACE FILE
    }
    
   }
 
}
