#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 sensor;
float ax, ay, az;
float vx0 = 0.0f;
float vy0 = 0.0f;
float vx = 0.0f;
float vy = 0.0f;
int readTime = 10; // read every 10 milliseconds
int angle = 85;
float g = 9.81f; // gravity
float finalVelocity = 0.0f;


void setup() {
  Serial.begin(57600);
  Wire.begin();
  sensor.initialize();
  if (sensor.testConnection()) Serial.println("Sensor initialized");
  else Serial.println("Error initializing sensor");
}

void loop() {
  sensor.getAcceleration(&ax, &ay, &az);
  Serial.print("a[x y z]:\t");
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  vx = horizontalVel(vx0, calculateVelocityX(ax));
  vy = verticalVel(vy0, calculateVelocityY(ay));
  finalVelocity += sqrt(pow(vx, 2) + pow(vy, 2));
  Serial.printf("Final velocity: %f", finalVelocity);
  delay(readTime);
}

float horizontalVel(int v0, int actualVel) {
  return vx * cos(angle);
}

float verticalVel(int v0, int actualVel) {
  return vy * sin(angle) - g * readTime;
}

void calculateVelocityX(float ax) {
  vx0 = vx0 + (ax * readTime);
}

void calculateVelocityY(float ay) {
  vy0 = vy0 + (ay * readTime);
}
