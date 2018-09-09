#include <math.h>

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
  double angle;

  // Leftcorner and righr corner
  double leftMax = 0;
  double leftAng = 0;
  
  double rightMax = 0;
  double rightAng = 91;
  
  // Find left corner
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

  // Find right corner
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

  // Convert from polar to rectangular coordinates
  double left_x = leftMax * cos(leftAng * 3.14 / 180);
  double left_y = leftMax * sin(leftAng * 3.14 / 180);
  double right_x = rightMax * cos(rightAng * 3.14 / 180);
  double right_y = rightMax * sin(rightAng * 3.14 / 180);

  // Get distance between both points
  double dist = sqrt(pow(left_x-right_x, 2) + pow(left_y - right_y, 2));

  // Print value
  Serial.print(dist);
  Serial.println(" cm");

  // Exit from loop routine
  exit(0);
}
