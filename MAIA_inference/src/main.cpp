#include <Arduino.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>

#include <TensorFlowLite_ESP32.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include "tensorflow/lite/micro/system_setup.h"
#include "modelg.h"

Adafruit_MPU6050 mpu;

const int numSamples = 40;
int samplesRead = 0;

// Variables globales utilizadas para TensorFlow Lite (Micro)
tflite::MicroErrorReporter tflErrorReporter;

// Incluir todas las operaciones de TFLM. Puedes eliminar esta línea y
// solo incluir las operaciones que necesitas para reducir el tamaño compilado del sketch.
tflite::AllOpsResolver tflOpsResolver;

const tflite::Model* tflModel = nullptr;
tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

// Crear un búfer de memoria estática para TFLM, el tamaño puede necesitar
// ser ajustado según el modelo que estés utilizando
constexpr int tensorArenaSize = 8 * 1024;
byte tensorArena[tensorArenaSize] __attribute__((aligned(16)));

// Array para mapear el índice del gesto a un nombre
const char* GESTURES[] = {
  "front",
  "slicer"
};

#define NUM_GESTURES (sizeof(GESTURES) / sizeof(GESTURES[0]))

void setup(void) {
  // Inicializar la comunicación serial a 115200 bps
  Serial.begin(115200);
  
  // Esperar hasta que la consola serial esté abierta antes de continuar
  while (!Serial)
    delay(10);

  // Inicializar el sensor MPU6050
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  // Obtener la representación de modelo TFL
  tflModel = tflite::GetModel(model);

  // Verificar la compatibilidad del esquema del modelo
  if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema mismatch!");
    while (1);
  }

  // Crear un intérprete para ejecutar el modelo
  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, tensorArenaSize, &tflErrorReporter);

  // Asignar memoria para los tensores de entrada y salida del modelo
  tflInterpreter->AllocateTensors();

  delay(100);
}

void loop() {
   while(samplesRead < numSamples) {
      // Obtener nuevos eventos del sensor con las lecturas
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);

      // Normalizar los datos del IMU entre 0 y 1 y almacenar en el tensor de entrada del modelo
      tflInputTensor->data.f[samplesRead * 6 + 0] = (a.acceleration.x + 5) / 10; 
      tflInputTensor->data.f[samplesRead * 6 + 1] = (a.acceleration.y + 2.5) / 5; 
      tflInputTensor->data.f[samplesRead * 6 + 2] = (a.acceleration.z + 10) / 20; 
      tflInputTensor->data.f[samplesRead * 6 + 3] = (g.gyro.x + 1.5) / 3; 
      tflInputTensor->data.f[samplesRead * 6 + 4] = (g.gyro.y+ 3) / 6; 
      tflInputTensor->data.f[samplesRead * 6 + 5] = (g.gyro.z + 1.75) / 3.5; 
      
      samplesRead++;
      
      if (samplesRead == numSamples) {
        // Ejecutar inferencia
        TfLiteStatus invokeStatus = tflInterpreter->Invoke();
        if (invokeStatus != kTfLiteOk) {
          Serial.println("Invoke failed!");
          while (1);
          return;
        }

        // Imprimir las salidas del modelo para cada gesto
        for (int i = 0; i < NUM_GESTURES; i++) {
          Serial.print(GESTURES[i]);
          Serial.print(": ");
          Serial.println(tflOutputTensor->data.f[i], 6);
        }
        
        samplesRead = 0; // Reiniciar el contador de muestras
      }

      delay(50); // Esperar 50 milisegundos antes de la próxima lectura
   }
}
