#define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN    "l8Q1_FgYRJsQ7wfs4J1q2lKxh-moLuWh"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Asd";
char pass[] = "00000000";

#define ENA 32
#define IN1 14
#define IN2 27

#define ENB 33
#define IN3 26
#define IN4 25

int motorSpeed = 200;

void leftMotorForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, motorSpeed);
}

void leftMotorBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, motorSpeed);
}

void rightMotorForward() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, motorSpeed);
}

void rightMotorBackward() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, motorSpeed);
}

void carForward() {

  leftMotorForward();
  rightMotorForward();

  Serial.println("FORWARD");
}

void carBackward() {

  leftMotorBackward();
  rightMotorBackward();

  Serial.println("BACKWARD");
}

void carLeft() {

  leftMotorBackward();

  rightMotorForward();

  Serial.println("LEFT");
}

void carRight() {

  leftMotorForward();

  rightMotorBackward();

  Serial.println("RIGHT");
}

void carStop() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  Serial.println("STOP");
}


BLYNK_WRITE(V0) {

  int value = param.asInt();

  if (value == 1) {
    carForward();
  } else {
    carStop();
  }
}

// V1 = Backward
BLYNK_WRITE(V1) {

  int value = param.asInt();

  if (value == 1) {
    carBackward();
  } else {
    carStop();
  }
}

BLYNK_WRITE(V2) {

  int value = param.asInt();

  if (value == 1) {
    carLeft();
  } else {
    carStop();
  }
}

BLYNK_WRITE(V3) {

  int value = param.asInt();

  if (value == 1) {
    carRight();
  } else {
    carStop();
  }
}

BLYNK_WRITE(V4) {

  int value = param.asInt();

  if (value == 1) {
    carStop();
  }
}

BLYNK_WRITE(V5) {

  motorSpeed = param.asInt();

  // Safety limits
  if (motorSpeed < 0) {
    motorSpeed = 0;
  }

  if (motorSpeed > 255) {
    motorSpeed = 255;
  }

  Serial.print("Speed = ");
  Serial.println(motorSpeed);
}

void setup() {

  Serial.begin(115200);

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  carStop();

  Blynk.begin(
    BLYNK_AUTH_TOKEN,
    ssid,
    pass
  );

  Serial.println("ESP32 CAR STARTED");
}

void loop() {

  Blynk.run();
}