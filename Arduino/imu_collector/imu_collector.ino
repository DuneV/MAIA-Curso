#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Aceleration on X;Y;Z (m/s^2) ; gyrox;gyroy;gyroz(rad/s) ;temperature (°C) */
  Serial.print(a.acceleration.x);
  Serial.print(";");
  Serial.print(a.acceleration.y);
  Serial.print(";");
  Serial.print(a.acceleration.z);
  Serial.print(";");
  Serial.print(g.gyro.x);
  Serial.print(";");
  Serial.print(g.gyro.y);
  Serial.print(";");
  Serial.print(g.gyro.z);
  Serial.print(";");
  Serial.print(temp.temperature);
  Serial.println("");
  delay(200);
}
