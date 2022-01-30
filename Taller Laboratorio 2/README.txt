Al ejecutar el programa, se mostrará el siguiente menú de opciones:

1) Caníbales y misioneros
2) Cubo mágico
3) Salir

Junto a estas 3 opciones, se mostrará el siguiente mensaje:

Ingrese opción:

Seguido de este mensaje se debe ingresar el numero de la opción a la cual se desea acceder mediante el teclado. 
(Favor solo ingresar NUMEROS para el correcto funcionamiento de este programa)

Una vez ingresada la opción deseada podría ocurrir una de las siguientes opciones dependiendo de lo que ingrese el usuario.

1) Si el numero ingresado es "1" se ejecutarán el problema de los caníbales y misioneros, al momento de ejecutarse, 
   se le pedirá al usuario que ingrese mediante el teclado la cantidad caníbales y misioneros se desean utilizar (solo 1 número para ambos).
	*Solamente se aceptarán valores naturales, sin incluir el cero. En caso de ingresar un valor invalido, se le dirá que vuelva a intentarlo ingresando un valor valido y será devuelto al menú inicial.

   En caso de ingresar un valor valido, el programa comenzará a buscar la solución del problema de los caníbales y misioneros con la cantidad de caníbales y misioneros
   ingresada por el usuario, en caso de que el programa encuentre una o más soluciones para el problema, el programa le mostrará al usuario de manera separada cada solución encontrada.
   En cada solución se mostrará paso a paso, como cambia el estado de la isla B (isla destino); cada paso mostrará 3 elementos, el primero de ellos indica la cantidad de caníbales presentes en la isla B,
   el segundo elemento indica la cantidad de misioneros presentes en la isla B y el tercero indica si el bote se encuentra en la isla B o en la isla A mediante un 1 o un 0 respectivamente.
   Luego de mostrar la(s) solución(es), el usuario será devuelto al menú principal para que elija una nueva opción.

   Ejemplo:  < 1 | 2 | 1 > -> 1 Caníbal, 2 misioneros, bote en la isla B.

   En caso de que el programa no encuentre una solución para el problema, se le mostrará al usuario un mensaje de que no se pudo encontrar una solución para el problema y el usuario será devuelto al menú principal
   para que elija una nueva opción.


2) Si el numero ingresado es "2" se ejecutará el cuadrado mágico, una vez ejecutado, se le pedirá al usuario ingresar mediante el teclado el número máximo que pueden tener los elementos del cubo.
	*Solamente se aceptarán valores naturales, sin incluir el cero. En caso de ingresar un valor invalido, se le dirá que vuelva a intentarlo ingresando un valor valido y será devuelto al menú inicial.
	*Se recomienda ingresar valores menores a 10, esto debido al tiempo que se puede llegar a demorar el programa en encontrar todas las soluciones.

   En caso de que el valor máximo entregado sea un valor valido, el programa comenzará a generar todas las posibles soluciones y a filtrarlas. Luego de obtener las soluciones que cumplen las restricciones,
   se le mostrará al usuario cada una de las soluciones indicando el número de la solución, una matriz de 3x3 que será la representación del cuadrado mágico y la suma con la que cumple los requisitos el cuadrado mágico.
   Luego de mostrar todas las soluciones el usuario será devuelto al menú principal para que elija una nueva opción.

   Ejemplo:

   solución 1:
   4 9 2
   3 5 7
   8 1 6
   Suma: 15

   	*Para que la solución sea un cuadrado mágico debe cumplir las siguientes condiciones:
		1) La suma de cada elemento de una fila, debe ser igual al del resto de las filas
		2) La suma de cada elemento de una columna, debe ser igual al del resto de las columnas, además esta debe ser igual a la suma en las filas
		3) La suma de cada elemento de una diagonal, debe ser igual al de la otra diagonal, esta a su vez debe ser igual a la suma en sus filas y columnas
		4) No ser una copia de otra solución con elementos cambiados de lugar y no ser una solución trivial (llena solamente de un mismo número, por ejemplo, solamente 1)
		5) Ningún número dentro del cuadrado mágico se puede repetir

    En caso de que no se encuentren cuadrados que cumplan todas estas condiciones, se le mostrará un mensaje al usuario indicando que no se pudieron encontrar soluciones y será devuelto al menú principal para que elija una nueva opción.

3) Si el numero ingresado es "3" se saldrá del menú y el programa terminará.

*) Si el usuario ingresa un número que no sea uno de los 3 mostrados como opciones, se mostrará un mensaje indicando que se ha ingresado una opción invalida y el usuario será devuelto al menú principal para que ingrese una nueva opción.

   
