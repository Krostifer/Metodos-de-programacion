//Rut: 20.239.786-7
//Seccion: L6
//Fecha de creacion: 16/08/2020, ultima revision 31/08/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE_STACK 100  //Tamaño maximo inicial de una pila (stack)
#define INIT_SIZE_QUEUE 100  //Tamaño maximo inicial de una cola


//****************************************************************************************** TORRES DE HANOI ******************************************************************************************

//********************************************** FUNCIONES ENTREGADAS *************************************************
//Se define la estructura de una pila
typedef struct spila
{
	int *array;  //Arreglo donde de guardarán los discos(valor numerico que lo represente)
	int size;  //Tamaño inicial de la pila
	int top;  //Indice donde se encuentra el primer valor de la pila (Más arriba)

} pila;

//Creación de una pila vacia
pila* crear_pila()
{
	pila *p = malloc(sizeof(pila));  //Se asigana memoria para la pila
	p-> array = malloc(INIT_SIZE_STACK*sizeof(int));  //Se asigna memoria para el arreglo dentro de la pila
	p-> size = INIT_SIZE_STACK;  //Se establece el tamaño inicial de la pila
	p-> top = -1;  //Indice del primer elemento (más arriba) de la pila, por defecto -1 que significa que está vacia
	return p;  //Se retorna el puntero a la pila 
}

//Consultar si la pila esta vacia
int pilaVacia(pila *S)  //Recibe como argumento una pila a verificar
{
	if (S-> top != -1)  //Indice del top dentro de una pila vacia
	{
		return 0;  //La pila no está vacia
	}

	else
	{
		return 1;  //La pila está vacia
	}
}

//Efectua un push de X en la pila S
void insertar(pila *S, int x)  //Recibe como argumento la pila donde se ejecutará el push y el elemento a ingresar (numero entero)
{
	if (S-> top+1 > S-> size)  //En caso de que se acabe el espacio para almacener elementos en la pila
	{
		S-> size = 2 * S-> size;  //Se duplica el tamaño de la pila
		S-> array = realloc(S-> array, S-> size*sizeof(int));  //Se reasignan los elementos de la lista a la nueva direccion de memoria

		if (S -> array == NULL)  //En caso de que el array no exista
		{
			exit(0);  //Sale de la función
		}
	}

	S-> top = S-> top+1;  //Se actualiza la posición del elemento de más arriba
	S-> array[S-> top] = x;  //Se asigna el valor dentro de la pila 	
}

//Efectua un pop en la pila S dejando el resultado en x*
int extraer(pila *S, int *x)  //Recibe como argumento una pila donde se extraerá un elemento y una variable para guardar aquél elemento
{
	if (pilaVacia(S))  ////Retorna verdadero o falso, dependiendo si la pila esta vacia
	{
		return 0;  //La pila está vacia por lo que no puede extraer un numeros
	}

	else
	{
		S-> top = S-> top-1;  //Actualiza la posición del elemento de más arriba en la pila
		*x = S-> array[S-> top+1];  //Se guarda el valor extraido en x
		return 1;
	}
}

//Busca el elemento x en la pila *S, retorna verdadero o falso
int buscar_pila(pila *S, int x)  //Recibe como argumento una pila donde buscar y el elemento a buscar dentro de esa lista
{
	if (pilaVacia(S))  //Si la pila está vacia, sale de la funcion
	{
		return 0;  //Retorna falso
	}

	else  //Si no está vacia
	{
		for(int k=0; k <= S-> top; k++)  //Bucle para buscar el elemento dentro del arreglo de la pila
		{
			if (S-> array[k] == x)
			{
				return 1;  //Si se encuentra retorna 1 (Verdadero)
			}
		}

		return 0;  //Si a pesar de no estar vacia, no encuentra el elementro, retorna 0 (Valso)
	}
}

//Imprime la pila de manera horizontal
void imprimir_pila(pila *S)  //Recibe como argumento una pila a imprimir
{

	printf(": ");  //Se imprime el inicio

	for (int k=1; k <= S->top; k++)  //Bucle para imprimir cada elemento del arreglo de una pila, parte desde k=1 ya que el elemento 0, es el elemento identificador de la pila
	{
		printf("%d", S-> array[k]);

		if (k < S-> top)  //Comprueba de que queden numeros del array por añadir y asi agregar una coma(,)
		{
			printf(", ");
		}
	}
	printf("\n");  //Salto de linea para separar cada estado
}



//********************************************** DEFINICION DE FUNCIONES NUEVAS *************************************************

//Ingresa los discos de manera ordenada dentro de la pila de origen
void iniciarDiscos (int numeroDiscos, pila *A)  //Recibe como argumento el numero de discos con los que se jugará y la pila de origen
{

	for (int k = numeroDiscos; k > 0; k--)  //Bucle para ingresar los discos desde el más grande al más pequeño
	{
		insertar(A,k);
	}
}

//Agrega un "id" para identificar cada pila en todo momento del proceso
void idDiscos(pila *S, int x)  //Recibe como argumentos la pila a "marcar" y el id que tendrá
{
	S-> top = S-> top+1;  //Se actualiza la posición del elemento superior de la pila
	S-> array[S-> top] = x;  //Se agrega el id dentro del arreglo de la pila
}

//Identifica la pila que tiene el id entregado
void reconocerId (pila *A, pila *B, pila *C, int id)  //Recibe como argumento las 3 pilas representando las 3 torres y el id que se desea encontrar
{
	if (buscar_pila(A,id))  //En caso de ser la pila buscada, se mostrará en pantalla
	{
		imprimir_pila(A);
	}

	else if (buscar_pila(B,id))  //En caso de ser la pila buscada, se mostrará en pantalla
	{
		imprimir_pila(B);
	}

	else if (buscar_pila(C,id))  //En caso de ser la pila buscada, se mostrará en pantalla
	{
		imprimir_pila(C);
	}
}

//Función que implementa el proceso para encontrar la solución de las torres de Hanoi
void torres(int N, pila *A, pila *B, pila *C)  //Recibe como argumentos la N = Cantidad de discos, A = Pila de origen, B = Pila auxiliar, C = Pila de destino
{
	if (N == 1)  //Caso base en donde solo quede un disco en la torre A
	{
		int disco_pop;
		extraer(A, &disco_pop);
		insertar(C, disco_pop);

		//*************************** IMPRESION DE LAS PILAS ***************************
		reconocerId (A, B, C, -1);
		reconocerId (A, B, C, -2);
		reconocerId (A, B, C, -3);
		printf("\n");
		//*************************** IMPRESION DE LAS PILAS ***************************
	}

	else
	{
		torres(N-1, A, C, B);  //Llamada recursiva para mover los discos desde el origen a la torre auxiliar

		int disco_pop;
		extraer(A, &disco_pop);  
		insertar(C, disco_pop);  //Se mueve el disco más grande que quedó en la torre de origen hacia la torre de destino

		//*************************** IMPRESION DE LAS PILAS ***************************
		reconocerId (A, B, C, -1);
		reconocerId (A, B, C, -2);
		reconocerId (A, B, C, -3);
		printf("\n");
		//*************************** IMPRESION DE LAS PILAS ***************************

		torres(N-1,B, A, C);  //Llamada recursiva para mover los discos que quedaron en la torre auxiliar hacia la torre de destino
	}
}

//Funcion que ejecuta el problema de hanoi
int hanoi()
{
	pila* pila_A = crear_pila();  //Se crea la pila de origen
	idDiscos(pila_A,-1);  //Se agrega el id a la torre de origen (-1)
	pila* pila_B = crear_pila();  //Se crea la torre auxiliar
	idDiscos(pila_B,-2);  //Se agrega el id a la torre auxiliar (-2)
	pila* pila_C = crear_pila();  //Se crea la torre de destino
	idDiscos(pila_C,-3);  //Se agrega el id a la torre de destino(-3)
	
	int discos;  //Se crea la variable para almacenar la cantidad de discos a usar
	printf("Ingrese la cantidad de discos para las torres de Hanoi: ");  //Se solicita ingresar la cantidad de discos
	scanf("%d", &discos);  //Se asigna el valor a la varible anteriormente definida
	printf("\n");

	if (discos <= 0 )
	{
		printf("Favor volver a intentarlo ingresando un valor valido\n");
		return 0;
	}

	
	iniciarDiscos(discos, pila_A);  //Se agregan los discos a la torre de origen
	
	printf("Inicio del proceso\n");
	imprimir_pila(pila_A);  //Se imprime el estado incial de las pilas
	imprimir_pila(pila_B);  //Se imprime el estado incial de las pilas
	imprimir_pila(pila_C);  //Se imprime el estado incial de las pilas
	printf("\n");  //Salto de linea para separar los estados

	torres(discos, pila_A, pila_B, pila_C);

	printf("Se ha terminado el proceso de las Torres de Hanoi.\n");
}



//****************************************************************************************** CONTAGIOS ******************************************************************************************

//********************************************** FUNCIONES ENTREGADAS *************************************************
//Se define la estructura que tendrá una cola
typedef struct scola 
{
	int head;  //Primer elemento en la cola
	int tail;  //El lugar desocupado después del último en la cola
	int size;  //Largo de la cola
	int capacity;  //Largo máximo de la cola
	int *array;  // Arreglo donde se encuetra almacenada la cola
} cola;

//Se crea una cola vacia
cola * crear_cola() 
{
	cola *c = malloc(sizeof(cola));  //Se asigna la memoria para la cola
	c-> array = malloc(INIT_SIZE_QUEUE*sizeof(int));  //Se asigna la memoria para el array de valores
	c-> size=0;  // Largo cero
	c-> capacity=INIT_SIZE_QUEUE;  // Largo maximo inicial de la cola
	c-> tail=0;  //Final de la cola
	c-> head=0;  //Se considera vacía si head==tail
	return(c);  // Retorna un puntero hacia la cola
}

//Pregunta si la cola se encuetra llena
int colaLlena(cola *Q)  //Recibe como argumenro la cola a revisar
{
	if (Q->capacity == Q-> size)  //Si la cantidad de elementos actuales es igual a la capacidad maxima, significa que está llena)
	{
		return 1;  //La pila está llena
	}

	else
	{
		return 0;  //La pila no se encuentra llena
	}
}


//Encolamos (añadimos) el valor x en la cola Q.
//Si se acaba el espacio entonces se duplica la capacidad de la cola Q.
void encolar(cola * Q, int x)  //Recibe como argumenro una cola y un elemento (numero) a ingresar en la cola
{
    if (colaLlena(Q) == 1)
    { // si esta llena duplicamos capacidad
        Q-> capacity = 2 * Q-> capacity; // duplicamos la capacidad
        Q-> array = realloc(Q-> array,Q-> capacity * sizeof(cola));
        //En este caso se cumple que head==tail
        //Movemos lo que está antes de head después del último
        memcpy(Q-> array+  Q-> size, Q-> array, Q-> head);
        Q->tail = Q->head + Q->size; // Después del primero
    }

    //Se asegura espacio disponible -> encolar
    Q-> array[Q-> tail] = x; // Se encola x

    if (Q-> tail == Q-> capacity)  //Si se pasó
    {  
        Q-> tail = 0;  //Vuelta al inicio
    } 
	else  //Si no se puede, puesto disponible en +1
	{ 
        Q-> tail = Q-> tail + 1;
        Q-> size = Q-> size+1; // actualizo el tamaño 
    }
}


//Se pregunta si la cola está vacía
int colaVacia(cola *Q)  //Recibe como argumento la cola a revisar
{
	if (Q-> size == 0)
	{
		return 1;  //La cola se encuentra vacia
	}

	else
	{
		return 0;  //La cola no se encuentra vacia
	}
}

//Se saca el primero de la cola y actualizan los números
int desencolar(cola *Q)  //Recibe como argumento la cola donde se sacará el elemento
{
	if (colaVacia(Q))
	{
		return 0;  //La cola está vacia, por lo que no se puede desencolar algo
	}

	
	else
	{
		int x = Q-> array[Q-> head];  //El primer elemento de la cola

		if (Q-> head == Q-> capacity)  //Si se paso, vuelve al inicio
		{
			Q->head = 0;
		}
			
		else  //Sino, se mueve al siguiente
		{
			Q-> head = Q-> head + 1;
		}

		return x;
		
	}
}

//********************************************** DEFINICION DE FUNCIONES NUEVAS *************************************************

//*Esta función es una modificación de una función entregada por el profesor Pablo Román en clases*
//Lee el documento donde se encuentra la matriz para el problema de los contagios
//Recibe como argumento la cantidad de filas y columnas de la matriz, la matriz, el nombre del documento a leer, las colas donde se guardarán las coordenadas de i e j de los infectados iniciales respectivamente
int leerMatriz(int filas, int columnas, int (*a)[columnas], char* filename, cola * contagiosI, cola * contagiosJ)  
{
    FILE *pf;  //Se crea un archivo file
    pf = fopen (filename, "r");  //Se abre el archivo en modo lectura

    if (pf == NULL)  //Si el archivo no existe, sale de la funcion e indica que el elemento ingresado no existe 
    {
    	printf("Archivo no existe\n");
        return 0;
    }

    int aux;  //Se crea una variable para guardar los dos primeros numeros del documento (dimensiones de la matriz)
    fscanf(pf, "%d", &aux);  //Primer elemento de la matriz
    fscanf(pf, "%d", &aux);  //Segundo elemento de la matriz
    
    for(int i = 0; i < filas; ++i)  //Se recorren las filas
    {
        for(int j = 0; j < columnas; ++j)  //Se recorren las columnas
        {
        
            if (fscanf(pf, "%d", &(a[i][j])) == EOF)  //Se asegura de que el elemento sea valido y se guarda el valor leido en la posicion i,j dentro de la matriz 
            {
            	printf("Formato de archivo incorrecto\n");
              	return 0;  //Sale de la funcion indicando que el formato del documento es incorrecto
            } 

            else if (a[i][j] == 2)  //Al encontrarse con un contagiado (2), lo agrega inmediatamente a la lista de contagiados
            {
            	encolar(contagiosI, i);  //Posición en i del contagiado
            	encolar(contagiosJ, j);  //Posición en j del contagiado
            }
        }
    }

    fclose (pf);  //Se cierra el archivo abierto
    return 1;  //Retorna 1 indicando que salió de la función sin problemas
}

//********************************** CONDICIONES PARA CONTAGIAR ***************************************

//Revisa si la "persona" puede contagiar a la persona en la posición superior
int puedoContagiarNorte (int i, int j, int columnas, int matriz[][columnas])  //Recibe como argumentos la posición i y j de la persona, la cantidad de columnas de la matriz y la matriz
{
	if (i-1 >= 0 && matriz[i-1][j] == 1)  //Revisa que la posición superior a el sea una posición dentro de la matriz y si la persona en esa posición es una persona sana
	{
		return 1;  //Retorna 1 indicando que se puede contagiar
	}

	else  //En caso de que la posición superior no sea valida o no se pueda contagiar
	{
		return 0;  //Retorna 0 indicando que no puede contagiar
	}
}

//Revisa si la "persona" puede contagiar a la persona en la posición inferior
int puedoContagiarSur (int i, int j, int columnas, int matriz[][columnas], int filas)  //Recibe como argumentos la posición i y j de la persona, la cantidad de columnas de la matriz, la matriz y la cantidad de filas de la matriz
{
	if (i+1 < filas && matriz[i+1][j] == 1) //Revisa que la posición inferior a el sea una posición dentro de la matriz y si la persona en esa posición es una persona sana
	{
		return 1;  //Retorna 1 indicando que se puede contagiar
	}

	else  //En caso de que la posición superior no sea valida o no se pueda contagiar
	{
		return 0;  //Retorna 0 indicando que no puede contagiar
	}
}

//Revisa si la "persona" puede contagiar a la persona a la derecha
int puedoContagiarEste (int i, int j, int columnas, int matriz[][columnas])  //Recibe como argumentos la posición i y j de la persona, la cantidad de columnas de la matriz y la matriz
{
	if (j+1 < columnas && matriz[i][j+1] == 1)  //Revisa que la posición a la derecha de él sea una posición dentro de la matriz y si la persona en esa posición es una persona sana
	{
		return 1;  //Retorna 1 indicando que se puede contagiar
	}

	else  //En caso de que la posición a la derecha no sea valida o no se pueda contagiar
	{
		return 0;  //Retorna 0 indicando que no puede contagiar
	}
}

int puedoContagiarOeste (int i, int j, int columnas, int matriz[][columnas])//Recibe como argumentos la posición i y j de la persona, la cantidad de columnas de la matriz y la matriz
{
	if (j-1 >= 0 && matriz[i][j-1] == 1)  //Revisa que la posición a la izquierda de él sea una posición dentro de la matriz y si la persona en esa posición es una persona sana
	{
		return 1;  //Retorna 1 indicando que se puede contagiar
	}

	else  //En caso de que la posición a la izquierda no sea valida o no se pueda contagiar
	{
		return 0;  //Retorna 0 indicando que no puede contagiar
	}
}

//Cuenta la cantidad de personas sanas (1) que hay actualmente en la matriz
int sanos(int filas, int columnas, int matriz[][columnas])  //Recibe como argumento la cantidad de filas y columnas de la matriz junto con la matriz
{
	int noContagiados = 0;  //Se crea la varible donde se guardará la cantidad de personas sanas y se establece inicialmente en cero

	for (int i = 0; i < filas; ++i)  //Se recorren las filas de la matriz
	{
		for (int j = 0; j < columnas; ++j)  //Se recorren las columnas de la matriz
		{
			if (matriz[i][j] == 1)  //Si la posición i,j es igual a 1, significa que hay una persona sana
			{
				noContagiados++;  //Se suma 1 a la cantidad de personas sanas
			}
		}
	}

	return noContagiados;  //Retorna la cantidad total de personas sanas
}

//Cuenta la cantidad de contagiados en el plano
int enfermos(int filas, int columnas, int matriz[][columnas])  //Recibe como entrada la matriz con las personas, la cantidad de filas y columnas de la matriz
{
	int contagiados = 0;  //Se crea la variable para almacenar la cantidad de contagiados 

	for (int i = 0; i < filas; ++i)  //Se recorren las filas de la matriz
	{
		for (int j = 0; j < columnas; ++j)  //Se recorren las columnas de la matriz
		{
			if (matriz[i][j] == 2)  //Si la persona está contagiada (2) se añade a la cuenta de contagiados
			{
				contagiados++;  //Se suma 1 a la cantidad de personas enfermas
			}
		}
	}

	return contagiados;  //Se retorna la cantidad total de contagiados (enfermos)
}

//Función que realiza el contagio en la matriz
//Recibe como argumentos las filas y columnas de la matriz, la matriz, las cola con las coordenadas en i y j respectivamanete de los contagiados
int contagiar(int filas, int columnas, int matriz[][columnas], cola * contagiosI, cola * contagiosJ)
{
	int t = 0;  //Se crea la variable del tiempo transcurrido y se incia en cero
	int contagiados = enfermos(filas, columnas, matriz);  //Se crea la variable con los contagiados actuales en la matriz y se calcula la cantidad con la funcion enfermos
	int contagiosRevisar = contagiados;  //Inicialmente se deberá revisar a todos los contagiados
	int i, j;  //Se crea la variable i y j para almacenar las coordenadas de la persona que contagiará

	while (contagiosRevisar != 0)  //Mientras que la cantidad de contagiados a reviar no sea cero, se revisará si puede contagiar
	{
		for (int k = 0; k < contagiosRevisar; k++)  //Ciclos de paso de tiempo en donde se comprobará si la persona puede contagiar a sus alrededores
		{
			i = desencolar(contagiosI);  //Se desencola la coordenada en i de la primera persona en la cola de contagiados y se almacena 
			j = desencolar(contagiosJ);  //Se desencola la coordenada en j de la primera persona en la cola de contagiados y se almacena

			//Ya que al crear un arreglo la memoria puede contener valores previos, esta condicion se asegura de que se esten utilizando indices dentro de la matriz
			//Cuando la cola está "vacia", los otros indices siguen teniendo valores previos los cuales exeden los limites de la matriz
			//Esto ocurre cuando no se puede contagiar a todas las personas, por lo que en ese caso, restorna -1
			if (i > filas || j > columnas)  
			{
				return -1;  //Retorna -1 indicando que no se pudieron contagiar todas la personas del plano
			}
			

			if (puedoContagiarNorte(i, j, columnas, matriz))  //Si la persona ingresada puede contagiar a la persona al norte, se procede a contagiarla
			{
				matriz[i-1][j] = 2;  //Se cambia el valor de la persona al norte desde 1(Sana) a 2(Contagiada)
				encolar(contagiosI, i-1);  //Se encola la coordena i de la nueva persona contagiada en la cola de contagiosI
				encolar(contagiosJ, j);  //Se encola la coordena j de la nueva persona contagiada en la cola de contagiosJ

				if (sanos(filas, columnas, matriz) == 0)  //Se calcula si es que siguen quedando personas sanas en el plano luego de contagiar
				{
					return t+1;  //Debe retornar t+1 ya que está haciendo un nuevo cambio, pero como escapa de la función antes de terminar el ciclo, debemos sumarle 1 a t
				}
			}

		
			if (puedoContagiarSur(i, j,columnas, matriz, filas))  //Si la persona ingresada puede contagiar a la persona al sur, se procede a contagiarla
			{
				matriz[i+1][j] = 2;  //Se cambia el valor de la persona al sur desde 1(Sana) a 2(Contagiada)
				encolar(contagiosI, i+1);  //Se encola la coordena i de la nueva persona contagiada en la cola de contagiosI
				encolar(contagiosJ, j);  //Se encola la coordena j de la nueva persona contagiada en la cola de contagiosJ

				if (sanos(filas, columnas, matriz) == 0)  //Se calcula si es que siguen quedando personas sanas en el plano luego de contagiar
				{
					return t+1;  //Debe retornar t+1 ya que está haciendo un nuevo cambio, pero como escapa de la función antes de terminar el ciclo, debemos sumarle 1 a t
				}
			}

		
			if (puedoContagiarEste(i, j, columnas, matriz))  //Si la persona ingresada puede contagiar a la persona al este, se procede a contagiarla
			{
				matriz[i][j+1] = 2;  //Se cambia el valor de la persona al este desde 1(Sana) a 2(Contagiada)
				encolar(contagiosI, i);  //Se encola la coordena i de la nueva persona contagiada en la cola de contagiosI
				encolar(contagiosJ, j+1);  //Se encola la coordena j de la nueva persona contagiada en la cola de contagiosJ

				if (sanos(filas, columnas, matriz) == 0)  //Se calcula si es que siguen quedando personas sanas en el plano luego de contagiar
				{
					return t+1;  //Debe retornar t+1 ya que está haciendo un nuevo cambio, pero como escapa de la función antes de terminar el ciclo, debemos sumarle 1 a t
				}
			}

		
			if (puedoContagiarOeste(i, j, columnas, matriz))  //Si la persona ingresada puede contagiar a la persona al oeste, se procede a contagiarla
			{
				matriz[i][j-1] = 2;  //Se cambia el valor de la persona al oeste desde 1(Sana) a 2(Contagiada)
				encolar(contagiosI, i);  //Se encola la coordena i de la nueva persona contagiada en la cola de contagiosI
				encolar(contagiosJ, j-1);  //Se encola la coordena j de la nueva persona contagiada en la cola de contagiosJ

				if (sanos(filas, columnas, matriz) == 0)  //Se calcula si es que siguen quedando personas sanas en el plano luego de contagiar
				{
					return t+1;  //Debe retornar t+1 ya que está haciendo un nuevo cambio, pero como escapa de la función antes de terminar el ciclo, debemos sumarle 1 a t
				}
			}
		}

		contagiosRevisar = enfermos(filas, columnas, matriz) - contagiados;  //La diferencia entre enfermos y contagios, son los contagiados nuevos que se revisaran en el for
		contagiados = enfermos(filas, columnas, matriz);  //Se actualiza la nueva contidad de contagiados en el plano
		t++;  //Se incrementa en 1 el tiempo pasado luego de terminar un ciclo de contagio
	}

	return -1;  //Retorna -1 indicando que luego de contagiar, aun quedan personas sanas que no se pueden contagiar
}

//Función que ejecuta el problema de contagios en el plano
int contagioEnPlano ()
{
	cola * contagiosI = crear_cola();  //Se crea la cola contagiosI para almacenar la coordenada i de los contagiados
    cola * contagiosJ = crear_cola();  //Se crea la cola contagiosJ para almacenar la coordenada j de los contagiados
    char nombreArchivo[100];  //Se crea la varible para almacenar el nombre del archivo a leer

    printf("Ingrese nombre de archivo matriz P: ");  //Se pide ingresar el nombre del archivo a leer
    scanf("%s", &nombreArchivo);  //Se guarda el nombre del archivo a leer en la variable nombreArchivo
    printf("\n");

    FILE* miarchivo = NULL;  //Se crea la variable archivo y se inicia en NULL para indicar que no hay nada
    int filas, columnas;  //Se crean las variables para guardas la cantidad de filas y columnas que posee la matriz

    miarchivo = fopen(nombreArchivo, "r");  //Se abre el archivo en modo lectura
	if (miarchivo == NULL)  //Indica que el archivo a leer no existe
	{
		printf("Archivo no existe\n");
		return 0;
	}

	fscanf(miarchivo, "%d", &filas);  //Lee el primer numero del documento que indica la cantidad de filas que tendrá la matriz y se guarda en filas
	fscanf(miarchivo, "%d", &columnas);  //Lee el segundo numero del documento que indica la cantidad de columnas que tendrá la matriz y se guarda en columnas
	fclose(miarchivo);  //Se cierra el archivo leido

	int matriz [filas][columnas];  //Se crea la matriz con la cantidad de filas y columnas indicadas en el documento

    int resultadoLectura = leerMatriz(filas, columnas, matriz, nombreArchivo, contagiosI, contagiosJ);  //Se lee la el documento que contiene el plano a contagiar

    if (resultadoLectura == 0)  //En caso de que haya ocurrido un error al leer el documento
    {
      //Se mostrará el error de la función leerMatriz y saldrá de la función
      return(0);
    }

	//************************************************************* Verificacion de condiciones iniciales *****************************************************************
	if (enfermos(filas, columnas, matriz) == 0 && sanos(filas, columnas, matriz) == 0)  //Revisa de que en el documento entregado inicialmente existan personas (contagiadas o sanas)
    {
    	printf("En el plano ingresado, inicialmente no hay ninguna persona.\n");
    	return 0;  //Se sale de la función
    }

    else if (enfermos(filas, columnas, matriz) == 0)  //Revisa de que en el documento entregado inicialmente existan contagiados
    {
    	printf("En el plano ingresado, inicialmente no hay ningun contagiado para contagiar.\n");
    	return 0;  //Se sale de la función
    }

	else if (sanos(filas, columnas, matriz) == 0)  //Revisa de que en el documento entregado inicialmente existan personas sanas para contagiar
    {
    	printf("En el plano ingresado, inicialmente todas las personas ya estan contagiadas.\n");
    	return 0;  //Se sale de la función
    }



	//******************************************** Procesamiento ******************************************************
    
	int resultado = contagiar(filas, columnas,matriz, contagiosI, contagiosJ);  //Se procede a contagiar a las personas de la matriz

	//******************************************** Salida ******************************************************

    if (resultado == -1)  //Si es que la función contagiar retorna -1 significa que no se logró contagiar a todas las personas del plano
    {
    	printf("No se logro contagiar a todas las personas.\n");
    }

    else  //Si se lograron contagiar a todas las personas, la función contagiar retornará el tiempo 
    {
    	printf("El tiempo de contagio es T=%d \n", resultado);  //Se muestra el tiempo que se demoró en contagiar a todas las personas del plano
    }

	return 0;  //Se salé de la función 
}


//********************************************** MENU PRINCIPAL *****************************************************************
//Funcion encargada de mostrar el menu del programa y ejecutar las distintas opciones de este, no recibe argumentos al momento de ser llamada.
int menu()
{
	int eleccion;  //Variable para almacenar la opcion ingresada por el usuario

	while(1)  //Se crea una tautologia para que el menu sea mostrado mientras no se salga de la funcion al ingresar la opcion 3
	{
		// Se muestran las opciones la usuario
		printf("\n");
		printf("1) Torres de Hanoi\n2) Contagios\n3) Salir\n");
		printf("Ingrese una opccion: ");
		scanf("%d", &eleccion);  //Se lee la opcion ingresada por el usuario y se almacena en la variable previamente creada
		printf("\n");

		if (eleccion == 1)
		{
			hanoi();  //Se llama a la funcion que ejecuta el problema de las torres de Hanoi
		}
		else if (eleccion == 2)
		{
			contagioEnPlano();  //Se llama a la funcion que ejecuta el problema de contagios en un plano
		}
		else if (eleccion == 3)
		{
			return 0;  //Se sale de la funcion terminando el probrama
		}
		else
		{
			printf("Opccion invalida\n");  //En caso de que el usuario ingrese una opcion invalida
		}
	}
}

//********************************************** EJECUCIÓN DEL PROGRAMA *****************************************************************
int main()
{
	menu();

	return 0;
}