#include <LIDARLite.h>
#include <Servo.h>
#include <Wire.h>

LIDARLite lidarLite;
Servo servo;

int servoPin = 9;

void setup() {
  servo.attach(servoPin);
  
  Serial.begin(9600);

  lidarLite.begin(0, true);
  lidarLite.configure(0);
}

void loop() {

  // Current angle we're at
  int angle;

  // Leftcorner and righr corner
  int leftMax = 0;
  int leftAng = 0;
  
  int rightMax = 0;
  int rightAng = 91;
  
  // Loop through all angles
  for (angle = 0; angle <= 90; angle++) {

    // Update direction and take measuremnt
    servo.write(angle);
    delay(10);
    int dist = lidarLite.distance();

    if (dist > leftMax) {
      leftMax = dist;
      leftAng = angle;
    }
  }

  for (angle = 91; angle < 180; angle++) {

    // Update direction and take measuremnt
    servo.write(angle);
    delay(10);
    int dist = lidarLite.distance();

    if (dist > rightMax) {
      rightMax = dist;
      rightAng = angle;
    }
  }

}
