# Filtro Kalman vs Complementario
### Complementario de la IMU MPU-6050

El filtro complementario es una técnica simple y eficaz para combinar las señales del acelerómetro y del giroscopio de la MPU-6050. Este enfoque aprovecha la precisión a largo plazo del acelerómetro en la medición de la inclinación y la capacidad del giroscopio para detectar movimientos rotacionales rápidos pero con error acumulativo a corto plazo.

- **Implementación en PlatformIO:** En el entorno de Arduino, el filtro complementario se implementa tomando las lecturas de aceleración y velocidad angular, y combinándolas mediante una constante de tiempo que define la proporción en la que contribuyen al resultado final. Este proceso se realiza mediante una simple ecuación ponderada que favorece el giroscopio para movimientos rápidos y el acelerómetro para estabilidad a largo plazo.
- **Ajuste del Filtro:** La clave para un filtro complementario efectivo es ajustar correctamente la constante de tiempo (o el factor de filtro) para equilibrar las contribuciones del acelerómetro y del giroscopio. Esto depende del tipo de movimiento esperado y del nivel de ruido presente en los datos del sensor.


### Kalman de la IMU MPU-6050

El Filtro de Kalman es más sofisticado y ofrece una solución más robusta para la fusión de datos sensoriales. Utiliza un enfoque de modelado estadístico para predecir el estado del sistema y actualizar estas predicciones con las mediciones reales, minimizando el error estimado.

-**Implementación en PlatformIO:** La implementación del Filtro de Kalman en Arduino requiere un modelo matemático del sistema y una estimación de los errores de medición y del proceso. El filtro se aplica a través de un conjunto de ecuaciones que actualizan las estimaciones de estado y las incertidumbres asociadas con esas estimaciones cada vez que se recibe una nueva medición.

-**Optimización del Filtro:** La eficacia del Filtro de Kalman depende en gran medida de la precisión de las estimaciones iniciales y de la modelización del sistema y del ruido. Ajustar estos parámetros para el contexto específico de la detección de gestos puede mejorar significativamente la precisión de las estimaciones.

### Comparación y Elección del Filtro


- **Complejidad vs. Rendimiento:** El filtro complementario es menos complejo y más fácil de implementar en un microcontrolador con recursos limitados como el ESP32, lo que lo hace ideal para aplicaciones en tiempo real que requieren baja latencia. El Filtro de Kalman, aunque más preciso, es computacionalmente más intensivo y podría no ser necesario para todos los tipos de gestos.

- **Aplicación Específica:** Para gestos simples y movimientos donde la precisión a largo plazo no es crítica, un filtro complementario puede ser suficiente. Para aplicaciones que requieren una alta precisión y donde los errores acumulativos del giroscopio pueden ser problemáticos, el Filtro de Kalman podría ser la mejor opción.
