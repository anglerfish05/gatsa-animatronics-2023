#include <Servo.h>
#include <Wire.h>

// pneumatics
int signalPin1 = 8;
int signalPin2 = 9;

//i2c constants
String answer = "on";
byte x = 0;

// motor constants
Motor motor1(5); // bear head
Motor motor2(5);
Motor motor3(5);
Motor motor4(5);
Motor motor5(5);

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

void Update1() {
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

void Update2() {
  if ((millis() - lastUpdate) > updateInterval) { // time to update
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      Serial.println(pos);
      /* if ((pos >= 100) || (pos <= 0)) { // end of sweep
        // reverse direction
        increment = -increment;
      }  */
    }
}

Motor motor1(5);
Motor motor2(5);
Motor motor3(5);
Motor motor4(5);

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

void setup() {
  // put your setup code here, to run once:
  pinMode(signalPin1, OUTPUT);
  pinMode(signalPin2, OUTPUT);
  
  motor1.Attach(4);
  motor2.Attach(5);
  motor3.Attach(6);
  motor4.Attach(7);

  Wire.begin(9);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  if( x == 1 ) {
    motor1.Update2();
  }
  else if( x == 2 ) {
    motor2.Update1();
  }
  else if( x == 3 ) {
    motor3.Update2();
  }
  else if( x == 4 ) {
    motor4.Update2();
  }
  else if( x == 5 ) {
    digitalWrite(signalPin1, HIGH);
    digitalWrite(signalPin2, HIGH);
    delay(5000);
    digitalWrite(signalPin1, LOW);
    digitalWrite(signalPin2, LOW);
  }
  else if( x == 6 ) {
    
  }
  else {
    
  }
}
