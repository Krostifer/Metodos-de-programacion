Al ejecutar el programa, se mostrará el siguiente menú de opciones:

1)Torres de Hanoi
2)Contagios
3)Salir

Junto a estas 3 opciones, se mostrará el siguiente mensaje:

Ingrese opción:

Seguido de este mensaje se debe ingresar el numero de la opción a la cual se desea acceder mediante el teclado. 
(Favor solo ingresar NUMEROS para el correcto funcionamiento de este programa)

Una vez ingresada la opción deseada podría ocurrir una de las siguientes opciones dependiendo de lo que ingrese el usuario.

1) Si el numero ingresado es "1" se ejecutarán las torres de Hanoi, al momento de ejecutarse, se le pedirá al usuario que ingrese mediante el teclado la cantidad de discos que desea tengan las torres de Hanoi.

   	*Solamente se aceptarán valores naturales, sin incluir el cero. En caso de ingresar un valor invalido, se le dirá que vuelva a intentarlo ingresando un valor valido y será devuelto al menú inicial.

   En caso de ingresar un valor valido, el programa comenzará a simular la resolución del problema de las torres de Hanoi, se mostrará paso a paso el estado de las 3 torres hasta llegar al estado final
   donde todos los discos estarán en la última torre, en este momento se indicará que se terminó el proceso de las torres de Hanoi y el usuario será devuelto al menú principal para que pueda ingresar una nueva elección.

2) Si el numero ingresado es "2" se ejecutará el contagio en un plano, una vez ejecutado, se le pedirá al usuario ingresar mediante el teclado el nombre del archivo que contiene la matriz para este problema junto con su extensión

   	*El documento con la matriz para el problema debe cumplir con las siguientes características, primero en caso de que el archivo se encuentre dentro de la misma carpeta del programa, solo se debe ingresar su nombre y su extensión,
    	en caso de no encontrarse en la misma carpeta, se debe ingresar la ruta completa del archivo para que sea abierto por el programa.
   	Segundo, dicho documento de texto en primera línea debe tener solo 2 números, estos números indican la cantidad de filas y columnas que tiene la matriz respectivamente, debajo de esta primera línea se debe escribir la matriz
    	que representa el plano de contagio, un "2" representa a una persona contagiada, un "1" representa a una persona sana y un "0" indica que en ese lugar no hay personas; cada número debe ir separado por un espacio de los otros números en su fila.
	
	Ejemplo de documento bien escrito:
	
	3 4
	2 1 1 1
        0 0 0 0
	0 0 1 2

	En caso de que no se respete una de estas condiciones, se le indicará al usuario el problema que ocurrió y será devuelto al menú principal para ingresar una nueva opción.

	Problemas que pueden existir:
		"Archivo no existe", este mensaje será entregado cuando el programa no encuentre el archivo indicado por el usuario.
		"Formato de archivo incorrecto", este mensaje será entregado cuando exista un error en el contenido del documento.
		"En el plano ingresado, inicialmente no hay ningún contagiado para contagiar", este mensaje será mostrado cuando no exista ningún contagiado (2) dentro de la matriz.
		"En el plano ingresado, inicialmente todas las personas ya estan contagiadas", este mensaje será mostrado cuando no exista ninguna persona sana (1) dentro de la matriz.
		"En el plano ingresado, inicialmente no hay ninguna persona.", este mensaje será mostrado cuando no exista ninguna persona (Matriz llena de 0).

	Dentro de la carpeta se encuentran dos archivos: example1.txt y example2.txt, en donde se podrá ver un caso en donde si se infectan todas las personas y uno donde no se puede infectar a todas las personas respectivamente.

  En caso de que el programa encuentre el documento indicado y cumpla con el formato correcto, se iniciará la simulación del contagio en el plano dado, en caso de que se pueda contagiar satisfactoriamente a todas las personas en el plano,
  se mostrará al usuario un mensaje indicando la cantidad de tiempo que se demoró en contagiar todo el plano (Ejemplo: "El tiempo de contagio es T=3"). Si no se pudo contagiar a todas las personas presentes en el plano, se mostrará un
  mensaje indicando que no se pudo contagiar a todas las personas.
  Luego de terminar el programa habiendo contagiado a todas las personas o no, el usuario será devuelto al menú principal para que ingrese una nueva opción.

3) Si el numero ingresado es "3" se saldrá del menú y el programa terminará.

*) Si el usuario ingresa un número que no sea uno de los 3 mostrados como opciones, se mostrará un mensaje indicando que se ha ingresado una opción invalida y el usuario será devuelto al menú principal para que ingrese una nueva opción.

  
		 