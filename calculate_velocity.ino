#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 sensorFinal;
int ax, ay, az;
float vx0 = 0.0f;
float vy0 = 0.0f;
float vx = 0.0f;
float vy = 0.0f;
int readTime = 200; // read every 10 milliseconds
int angle = 85;
float g = 9.81f; // gravity
float finalVelocity = 0.0f;


void setup() {
  Serial.begin(57600);
  Wire.begin();
  sensorFinal.initialize();
  if (sensorFinal.testConnection()) Serial.println("Sensor initialized");
  else Serial.println("Error initializing sensor");
}

void loop() {
  sensorFinal.getAcceleration(&ax, &ay, &az);
  while (az != -1 && ax > -200) {
    Serial.print("a[x y z]:\t");
    Serial.print(ax); Serial.print("\t");
    Serial.print(ay); Serial.print("\t");
    Serial.print(az); Serial.print("\t");
    vx = horizontalVel(vx0, calculateVelocityX(ax));
    vy = verticalVel(vy0, calculateVelocityY(ay));
    finalVelocity += sqrt(pow(vx, 2) + pow(vy, 2));
    Serial.print("Final velocity: "); Serial.print(finalVelocity);
    Serial.print("\n\n");
    delay(readTime);
  }
}

float horizontalVel(float v0, float actualVel) {
  return vx * cos(angle);
}

float verticalVel(float v0, float actualVel) {
  return vy * sin(angle) - g * (readTime / 1000);
}

float calculateVelocityX(int ax) {
  vx0 = vx0 + (ax * (readTime / 1000));
  return vx0;
}

float calculateVelocityY(int ay) {
  vy0 = vy0 + (ay * (readTime / 1000));
  return vy0;
}
