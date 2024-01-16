#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>

// Crear un objeto para manejar el sensor MPU6050
Adafruit_MPU6050 mpu;

void setup(void) {
  // Inicializar la comunicación serial a 115200 bps
  Serial.begin(115200);
  
  // Esperar hasta que la consola serial esté abierta antes de continuar
  while (!Serial)
    delay(10);

  // Inicializar el sensor MPU6050
  mpu.begin();

  // Configurar el rango del acelerómetro a +/-2g
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);

  // Configurar el rango del giroscopio a +/-500 grados por segundo
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // Configurar el ancho de banda del filtro a 5 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  // Esperar un breve tiempo para que el sensor se estabilice
  delay(100);
}

void loop() {
  // Obtener nuevos eventos del sensor con las lecturas
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Imprimir las lecturas en el formato "acel_x;acel_y;acel_z;gyro_x;gyro_y;gyro_z;temp"
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

  // Esperar 50 milisegundos antes de la próxima lectura frecuencia de muestreo f = 1 / ts donde ts = x/1000; delay (x); 
  delay(50);
}
