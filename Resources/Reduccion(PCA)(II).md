# PCA
La reducción de dimensionalidad es una técnica común en proyectos de aprendizaje automático, eliminando información no crucial para acelerar el entrenamiento y mejorar la clasificación. Ahora, con la capacidad de ejecutar Machine Learning en placas Arduino y para este caso [ESP32](https://www.espressif.com/en/products/socs/esp32), se vuelve esencial, especialmente en dispositivos con recursos limitados como en nuestro caso. En un proyecto de clasificación de gestos, la alta dimensionalidad de las características impedía la instalación de la mayoría de los clasificadores en algunas tarjetas como puede ser la **MCU8266**. Se explorara la reducción de dimensionalidad como método puede llegar a superar este desafío. 

Se optará por comenzar con PCA (Análisis de Componentes Principales) entre los numerosos algoritmos disponibles para la reducción de dimensionalidad, dada su amplia utilización.  Para el ejemplo se hará uso del paquete Python micromlgen, se le recomienda leer la documentación de __git__ de introducción para familiarizarse con él. Es importante recordar instalar siempre la última versión, ya que se publican actualizaciones frecuentes. A continuación se encuentra del repositorio:

```
https://github.com/eloquentarduino/micromlgen.git
```
Para instalar el paquete ejecute:
```
pip install --upgrade micromlgen
```
Ahora, convertir un transformador PCA de sklearn a C simple se ha vuelto sencillo utilizando el puerto del método mágico. Además de la conversión de clasificadores SVM/RVM, micromlgen también permite exportar PCA. A continuación veremos el siguiente ejemplo:

```
from sklearn.decomposition import PCA
from sklearn.datasets import load_iris
from micromlgen import port

if __name__ == '__main__':
    X = load_iris().data
    pca = PCA(n_components=2, whiten=False).fit(X)

    print(port(pca))
```
## PCA en C
Para utilizar el código exportado, primero debemos incluirlo en nuestro boceto. Guarde el contenido en un archivo (lo llamé pca.h) en la misma carpeta de su proyecto .cpp de PlatformIO e inclúyalo.
```
#include "pca.h"

// this was trained on the IRIS dataset, with 2 principal components
Eloquent::ML::Port::PCA pca;
```
El objeto pca ahora puede tomar una matriz de tamaño N como entrada y devolver una matriz de tamaño K como salida, normalmente con K < N.
```
void setup() {
    float x_input[4] = {5.1, 3.5, 1.4, 0.2};
    float x_output[2];

    pca.transform(x_input, x_output);
}
```
Eso es todo: ahora puedes ejecutar tu clasificador en x_output.
```
#include "pca.h"
#include "svm.h"

Eloquent::ML::Port::PCA pca;
Eloquent::ML::Port::SVM clf;

void setup() {
    float x_input[4] = {5.1, 3.5, 1.4, 0.2};
    float x_output[2];
    int y_pred;

    pca.transform(x_input, x_output);

    y_pred = clf.predict(x_output);
}
```


### Referencia
[1] https://eloquentarduino.github.io/2020/06/arduino-dimensionality-reduction-pca-for-machine-learning-projects/
