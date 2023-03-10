#include <FastLED.h>
#include <SPI.h>
#include <SD.h>
#define SD_ChipSelectPin 53
#include <Servo.h>
#include <Wire.h>
#include <pcmRF.h>
#include <pcmConfig.h>
#include <TMRpcm.h>

// motor constants
int enA = 5;
int in1 = 21;

// rgb constants
#define LED_TYPE WS2812B
CRGB headLightsLeft[13]; // num leds per strip
CRGB headLightsRight[13];
CRGB leftLights[30];
CRGB centerLights[30];
CRGB rightLights[30];

// general constants
bool start = false;
bool end1 = false;
bool end2 = false;

// UltraSonic Sensor constants 
const int trigPin = 3;
const int echoPin = 2;
long distance;
long duration;

// audio settings
TMRpcm audio;

// button constants
const int button1Pin = 22; // attractions
bool button1 = false;
const int button2Pin = 23; // food
bool button2 = false;
const int button3Pin = 24; // state parks
bool button3 = false;
const int button4Pin = 25; // historical sites
bool button4 = false;
const int button5Pin = 26; // historical figures
bool button5 = false;
const int button6Pin = 27; // food
bool button6 = false;
const int button7Pin = 28; // gas
bool button7 = false;

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

void lightsOff() {
  fill_solid(headLightsLeft, 13, CRGB::Black);
  fill_solid(headLightsRight, 13, CRGB::Black);
  fill_solid(leftLights, 6, CRGB::Black);
  fill_solid(centerLights, 8, CRGB::Black);
  fill_solid(rightLights, 6, CRGB::Black);
  FastLED.show();
}
void mainLightsOff() {
  fill_solid(leftLights, 6, CRGB::Black);
  fill_solid(centerLights, 8, CRGB::Black);
  fill_solid(rightLights, 6, CRGB::Black);
  FastLED.show();
}
void lightsOn() {
  fill_solid(headLightsLeft, 13, CRGB(243, 231, 50));
  fill_solid(headLightsRight, 13, CRGB(243, 231, 50));
  fill_solid(leftLights, 6, CRGB(243, 231, 50));
  fill_solid(centerLights, 8, CRGB(243, 231, 50));
  fill_solid(rightLights, 6, CRGB(243, 231, 50));
  FastLED.show();
}
void centerLightsOn() {
  fill_solid(centerLights, 8, CRGB(243, 231, 50));
  FastLED.show();
}
void leftLightsOn() {
  fill_solid(leftLights, 6, CRGB(243, 231, 50));
  FastLED.show();
}
void rightLightsOn() {
  fill_solid(rightLights, 6, CRGB(243, 231, 50));
  FastLED.show();
}

void setup() {
  // put your setup code here, to run once:
  // button 
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  pinMode(button5Pin, INPUT);
  pinMode(button6Pin, INPUT);
  pinMode(button7Pin, INPUT);
        
  // rgb
  FastLED.addLeds<LED_TYPE, 6, GRB> (headLights, 20);
  FastLED.addLeds<LED_TYPE, 7, GRB> (leftLights, 30);
  FastLED.addLeds<LED_TYPE, 8, GRB> (centerLights, 30);
  FastLED.addLeds<LED_TYPE, 9, GRB> (rightLights, 30);
  FastLED.setBrightness(50);

  // i2c
  Wire.begin();
  
  // UltraSonic Sensor
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);

  // tmrpcm
  audio.speakerPin = 11;
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
  return;   // don't do anything more if not
  }
  audio.setVolume(7); // 0-7

  // motor
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  analogWrite(enA, 100);
}

void loop() {
  // put your main code here, to run repeatedly:
   
   ultrasonic();
   ultrago();
  
  // when ultrasonic detects
   while(start) {
    // intro plays
    if(start) {
      lightsOn();
      motor.write(MF);
      delay(5000); //audio time
      motor.write(MS);
      mainLightsOff();
      buttonsAllOn();
    }
    
    else if( digitalRead(button1Pin) == HIGH && button1 ) {
      button2 = false;
      button3 = false;
      button4 = false;
      button5 = false;
      button6 = false;
      button7 = false;

      centerLightsOn();
      motor.write(MF);
      Wire.beginTransmission(9);
      Wire.write(1);
      audio.play( "attractions.wav" );
      Wire.endTransmission();
      delay(5000); // audio time
      motor.write(MS);
      mainLightsOff();
      buttonsAllOn();
      Wire.beginTransmission(2);
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

      leftLightsOn();
      motor.write(MF);
      Wire.beginTransmission(9);
      Wire.write(3);
      audio.play( "stateparks.wav" );
      Wire.endTransmission();
      delay(5000); // audio time
      motor.write(MS);
      mainLightsOff();
      buttonsAllOn();
      Wire.beginTransmission(2);
      Wire.write(2);
      Wire.endTransmission();
    }
    
    else if( digitalRead(button4Pin) == HIGH && button4 ) {
      button1 = false;
      button2 = false;
      button3 = false;
      button5 = false;
      button6 = false;
      button7 = false;

      rightLightsOn();
      motor.write(MF);
      Wire.beginTransmission(9);
      Wire.write(4);
      audio.play( "historicalsites.wav" );
      Wire.endTransmission();
      delay(5000); // audio time
      motor.write(MS);
      mainLightsOff();
      buttonsAllOn();
      Wire.beginTransmission(2);
      Wire.write(2);
      Wire.endTransmission();   
    }
    
    else if( digitalRead(button5Pin) == HIGH && button5 ) {
      button1 = false;
      button2 = false;
      button3 = false;
      button4 = false;
      button6 = false;
      button7 = false;

      leftLightsOn();
      rightLightsOn();
      motor.write(MF);
      Wire.beginTransmission(9);
      Wire.write(5);
      audio.play( "historicalfigures.wav" );
      Wire.endTransmission();
      delay(5000); // audio time
      motor.write(MS);
      mainLightsOff();
      buttonsAllOn();
      Wire.beginTransmission(2);
      Wire.write(2);
      Wire.endTransmission();
    }
    
    else if( digitalRead(button6Pin) == HIGH && button6 ) {
      button1 = false;
      button2 = false;
      button3 = false;
      button4 = false;
      button5 = false;
      button7 = false;

      centerLightsOn();
      motor.write(MF);
      audio.play( "food.wav" );
      delay(5000); // audio time
      motor.write(MS);
      mainLightsOff();
      buttonsAllOn();
    }
    
    else if ( digitalRead(button7Pin == HIGH && button7 ) ) {
      button1 = false;
      button2 = false;
      button3 = false;
      button4 = false;
      button5 = false;
      button6 = false;

      centerLightsOn();
      motor.write(MF);
      audio.play( "gas.wav" );
      delay(5000); // audio time
      motor.write(MS);
      mainLightsOff();
      buttonsAllOn();
    }
   
    if ( end1 ) {
      lightsOn();
      motor.write(MF);
      audio.play( "ending.wav" );
      delay(5000); // audio time
      motor.write(MS);
      lightsOff();
      return;
    }
   }
 
}
