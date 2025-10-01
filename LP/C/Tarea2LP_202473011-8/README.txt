Nombre: Joaquin Muñoz
Rol: 202473011-8

*Correcta ejecucion*:
-use el comando run en la terminal para iniciar la compilación, una vez compilado muévase a la carpeta creada usando cd output
ya en la carpeta usar ./main.exe para ejecutar el programa

*cosas a tener en cuenta*:

-IMPORTANTE hay dos carpetas que contienen funcionalmente el mismo juego, la unica diferencia es que en una uso
funciones retardantes para hacer mas dinamico el juego y en la otra pues no, para efectos formales la tarea que entrego
es la que esta en la carpeta llamada no_sleep

-decidi que la municion extra sera dada por aliens especificos, los skaters dan perforadora con 25% de probabilidad
y los especiales dan especial con la misma probabilidad, tome esa decicion porque asi se sentia mas divertido, se que
no es eso lo que escifica la tarea pero te juro que es mas divertido asi.

-los typedef estan en un archivo aparte porque tenerlos en el resto de archivos me daba errores de compilacion que 
no supe solucionar

-aveces y solo aveces aliens mueren de la nada, ni idea porque.

-hice testeo con valgrind y se lekean 16 bytes de 24720 que uso, no le puse mucha atención porque representa el 0,06% de
la memoria usada


Alien Especial: Bulldozer, tiene 5 de HP y se mueve igual que un Alien Drone
Arma Especial: Triple disparo, dispara en la columa del jugador en en las dos adyacentes, actuando como un disparo normal pero por tres columnas