# Resumen de Ventanas de Tiempo para Sistema de TinyML con ESP32 y MPU6050
### Introducción
El sistema combina un ESP32, un microcontrolador potente y versátil, con un MPU6050, un sensor que integra un acelerómetro y un giroscopio, para detectar y analizar gestos. En el contexto de TinyML, este conjunto permite ejecutar modelos de machine learning directamente en el dispositivo, optimizando el rendimiento y la eficiencia energética.

### Importancia de las Ventanas de Tiempo
Las ventanas de tiempo son cruciales en el procesamiento de señales para la detección de gestos, ya que definen el período sobre el cual se recopilan los datos del sensor para su análisis. Una ventana bien definida mejora la precisión del modelo al capturar la información relevante de un gesto, mientras que minimiza el ruido y los datos innecesarios.

### Configuración de Ventanas de Tiempo
- Tamaño de la Ventana
Duración óptima: Depende del gesto específico, pero generalmente oscila entre 100 ms y 1 s.
- Consideraciones: Debe ser lo suficientemente larga para abarcar todo el gesto, pero lo suficientemente corta para evitar la inclusión de movimientos irrelevantes.
- Solapamiento
Propósito: Mejorar la detección permitiendo cierta continuidad entre ventanas consecutivas.
*Recomendación*: Un solapamiento del 25% al 50% suele ser efectivo.
- Frecuencia de Muestreo
Ideal para MPU6050: Entre 50 Hz y 100 Hz.
Justificación: Suficiente para capturar la mayoría de los gestos sin generar cantidades excesivas de datos.
### Recomendaciones
- Experimentación: La elección óptima de la configuración de las ventanas puede variar según el contexto de aplicación. Es crucial experimentar con diferentes tamaños de ventana, solapamientos y frecuencias de muestreo.
- Preprocesamiento: Aplicar filtros, como un filtro de paso bajo, puede ayudar a suavizar los datos del sensor y mejorar la detección de gestos.
- Optimización del Modelo: Entrenar el modelo de TinyML con datos que reflejen la configuración de las ventanas de tiempo elegida para asegurar la coherencia entre la recolección de datos y la inferencia.

### Ejemplo de implementación de solapamiento
Para implementar el solapamiento de ventanas de tiempo en un sistema PlatformIO que utiliza un ESP32 y una MPU6050 para la detección de gestos, puedes seguir estos pasos básicos. El solapamiento te permite asegurarte de que los gestos que ocurren entre dos ventanas de tiempo consecutivas no se pierdan. Aquí tienes una guía general sobre cómo controlarlo:

1. Definir Parámetros de la Ventana de Tiempo

Primero, define los parámetros clave como el tamaño de la ventana de tiempo (windowSize) y el tamaño del solapamiento (overlapSize). Por ejemplo, si tu ventana es de 200 ms y quieres un solapamiento del 50%, el tamaño del solapamiento será de 100 ms.

```
unsigned long windowSize = 200; // en milisegundos
unsigned long overlapSize = 100; // en milisegundos
unsigned long lastWindowStartTime = 0;
```
2. Configurar el Muestreo de Datos

Configura la MPU6050 para muestrear datos a una tasa adecuada. Esto se hace normalmente en la configuración (setup()) del sketch de PlatformIO en el .cpp.
```
#include <Arduino.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

MPU6050 sensor;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  sensor.initialize();
  if (!sensor.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }
}

```
3. Bucle Principal para el Muestreo y el Solapamiento

En el bucle principal (loop()), debes controlar el tiempo para comenzar una nueva ventana de muestreo y aplicar el solapamiento. Esto se puede hacer guardando el tiempo de inicio de la ventana actual y comprobando si el tiempo actual ha superado el tiempo de inicio más el tamaño de la ventana menos el tamaño del solapamiento.
```
void loop() {
  unsigned long currentTime = millis();
  
  // Comprueba si es el momento de comenzar una nueva ventana teniendo en cuenta el solapamiento
  if (currentTime - lastWindowStartTime >= (windowSize - overlapSize)) {
    // Procesar los datos de la ventana actual...

    // Iniciar una nueva ventana
    lastWindowStartTime = currentTime - overlapSize; // Ajusta para el solapamiento
    
    // Muestrear y almacenar datos de la MPU6050...
  }

  // Aquí puedes añadir el código para leer los datos de la MPU6050 y procesarlos
}
```
4. Procesamiento de Datos

Dentro de la ventana de tiempo, debes recoger y almacenar los datos de la MPU6050, y luego procesar estos datos para detectar gestos. La recopilación de datos puede incluir lecturas de acelerómetro y giroscopio, y el procesamiento puede implicar filtrado, extracción de características y clasificación mediante un modelo de TinyML.

##### Consideraciones Adicionales

- Gestión de la Memoria: Asegúrate de gestionar eficientemente la memoria al almacenar los datos de las ventanas, especialmente si estás trabajando con ventanas de tiempo grandes o con una alta tasa de muestreo.
- Sincronización: Es importante mantener una sincronización precisa para que las ventanas de tiempo y los solapamientos funcionen como se espera. La función millis() ofrece una buena base, pero ten en cuenta su precisión y posible desbordamiento.
- Depuración: Utiliza la consola serial para depurar y verificar que las ventanas y el solapamiento están funcionando como se espera.