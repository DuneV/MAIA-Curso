# Bienvenidos a TensorFlow Lite
En este modulo nos centraremos en la evaluación de un modelo basico en TensorFlow Lite, para realizar este simplemente clonaremos la libreria [Tensor Flow Lite Arduino](https://github.com/tensorflow/tflite-micro-arduino-examples/tree/main). Una vez agregada esta en el espacio de **libs deps** de PlatformIO como se ve a continuación (ignorando el board_build.partitions), ajuste de igual forma el monitor_speed a 115200:
### En caso de que no sea compatible tfmicro, utilice:
```
lib_deps = tanakamasayuki/TensorFlowLite_ESP32@^1.0.0
```
![enter image description here](https://hackster.imgix.net/uploads/attachments/1035509/image_xw9FmVMM7x.png?auto=compress,format&w=740&h=555&fit=max)
# Ejemplos

Una vez compilado el proyecto se tomaran los archivos correspondientes a la carpeta /.pio/libdeps, donde se encontrara con la carpeta "hello_world". Copie los elementos del hello_world.ino a su carpeta raiz /src, a su archivo main.cpp. 

Despues de la inclusión de "Arduino.h". Seguido a esto copie todos los archivos headers (.h) y cpp que encuentre en la carpeta, asegurando de esta manera la siguiente estructura de carpetas:
```
-a----     30/05/2022  12:33 a. m.           1573 constants copy.h
-a----     30/05/2022  12:33 a. m.            791 constants.cpp
-a----     30/05/2022  12:33 a. m.           1573 constants.h
-a----     22/01/2024  10:09 a. m.           4171 main.cpp
-a----     30/05/2022  12:33 a. m.              1 main_functions.h
-a----     30/05/2022  12:33 a. m.          16969 model.cpp
-a----     30/05/2022  12:33 a. m.           1295 model.h
-a----     30/05/2022  12:33 a. m.           1020 output_handler.cpp
-a----     30/05/2022  12:33 a. m.           1161 output_handler.h
```

## Reconocimiento

Para este caso el modelo que exportamos desde nuestro ejemplo desarrollador en colab, podemos hacer uso de este ingresandolo en la variable:
```
alignas(8) const  unsigned  char g_model[] =
```
O creando una nueva e importandola desde los demás archivos, teniendo en cuenta que son los posibles valores del seno reemplazandolo por el dispuesto en la carpeta creada.

## Experimentar

La gestión de archivos del ejemplo se realiza para tener una forma estructurada de hacer la lectura del modelo de tal forma que se pueda tener varios de estos, en el caso de solo estar interesado en utilizar 1 modelo, puede importarlo directamente desde el archivo main.cpp. 

## Salida
La posible salida del sistema es la siguiente los calculos asociados a la aproximación del seno.
```
x_value: 1.2566366*2^1, y_value: 1.0674761*2^-1
```
## Archivo
Si es necesario el proyecto se encuentra en la carpeta **test_PF**, importelo de ser necesario desde platformIO. 
