#include <Servo.h>

Servo horizontalServo;  // X-axis
Servo verticalServo;    // Y-axis

// Analog pins for LDRs
int ldrTopLeft = A0;
int ldrTopRight = A1;
int ldrBottomLeft = A2;
int ldrBottomRight = A3;

// Initial angles
int hAngle = 90;
int vAngle = 90;

void setup() {
  horizontalServo.attach(9);  // X-axis servo
  verticalServo.attach(10);   // Y-axis servo
  Serial.begin(9600);
  horizontalServo.write(hAngle);
  verticalServo.write(vAngle);
}

void loop() {
  int tl = analogRead(ldrTopLeft);
  int tr = analogRead(ldrTopRight);
  int bl = analogRead(ldrBottomLeft);
  int br = analogRead(ldrBottomRight);

  int avgTop = (tl + tr) / 2;
  int avgBottom = (bl + br) / 2;
  int avgLeft = (tl + bl) / 2;
  int avgRight = (tr + br) / 2;

  int tolerance = 50;

  // Vertical tracking
  if (abs(avgTop - avgBottom) > tolerance) {
    if (avgTop > avgBottom) {
      vAngle = vAngle + 1;
      if (vAngle > 180) vAngle = 180;
    } else {
      vAngle = vAngle - 1;
      if (vAngle < 0) vAngle = 0;
    }
    verticalServo.write(vAngle);
    delay(15);
  }

  // Horizontal tracking
  if (abs(avgLeft - avgRight) > tolerance) {
    if (avgLeft > avgRight) {
      hAngle = hAngle + 1;
      if (hAngle > 180) hAngle = 180;
    } else {
      hAngle = hAngle - 1;
      if (hAngle < 0) hAngle = 0;
    }
    horizontalServo.write(hAngle);
    delay(15);
  }

  // Optional: Debug output
  Serial.print("TL:"); Serial.print(tl);
  Serial.print(" TR:"); Serial.print(tr);
  Serial.print(" BL:"); Serial.print(bl);
  Serial.print(" BR:"); Serial.println(br);
  delay(200);
}
