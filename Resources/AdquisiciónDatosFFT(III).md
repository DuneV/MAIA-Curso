# Tratamiento de datos

El tratamiento de datos hace parte fundamental de la migración de sistemas basados en ML a embebidos. Aún más cuando la optimización y ahorro de memoria se convierten en fundamentos claves para la migración de estos interpretadores. Ahora bien, para el tratamiento se han propuesto 4 ejes aplicables en los modelos de tiny ML, necesarios para la mejora y recreación de resultados en la ESP32.

1. **PCA (Análisis de Componentes Principales):**
   - PCA es una técnica de análisis multivariante que se utiliza para simplificar la complejidad en conjuntos de datos de alta dimensionalidad. Su objetivo principal es transformar los datos originales en un nuevo conjunto de variables no correlacionadas llamadas componentes principales. Estos componentes capturan la mayor varianza en los datos, lo que permite reducir la dimensionalidad manteniendo la información más importante.

2. **Adquisición FFT (Transformada Rápida de Fourier):**
   - La Transformada Rápida de Fourier (FFT) es un algoritmo eficiente para calcular la transformada de Fourier discreta de una secuencia de datos. En el contexto de adquisición de datos, la FFT se utiliza comúnmente para analizar las componentes de frecuencia en una señal. Convierte una señal desde el dominio del tiempo al dominio de la frecuencia.

3. **KALMAN vs Complementario:**
   - KALMAN y el filtro complementario son dos enfoques diferentes para la fusión de datos en sistemas de sensores. El filtro de Kalman es un algoritmo de estimación que utiliza mediciones pasadas y presentes para predecir el estado futuro de un sistema. El filtro complementario combina información de diferentes sensores de una manera ponderada para mejorar la precisión y la robustez de las estimaciones.

4. **Reconocimiento de ventana de muestreo:**
   - El reconocimiento de ventana de muestreo se refiere al proceso de identificar y utilizar ventanas específicas de datos para el análisis o procesamiento. En el contexto del muestreo de señales, las ventanas se aplican para limitar la duración de la señal considerada en un instante dado, lo que puede ser crucial para aplicaciones como el procesamiento de señales en tiempo real.
