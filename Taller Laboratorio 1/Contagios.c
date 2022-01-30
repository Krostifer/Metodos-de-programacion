#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INIT_SIZE_QUEUE 100

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
	cola *c = malloc(sizeof(cola));
	c->array = malloc(INIT_SIZE_QUEUE*sizeof(int));
	c->size=0; // largo cero
	c->capacity=INIT_SIZE_QUEUE; // largo máximo inicial
	c->tail=0;
	c->head=0; // se considera vacía si head==tail
	return(c); // ojo que retorna el puntero
}

//Pregunta si la cola se encuetra llena
int colaLlena(cola *Q)
{
	if (Q->capacity == Q->size)  //Si la cantidad de elementos actuales es igual a la capacidad maxima, significa que está llena)
	{
		return 1;  //La pila está llena
	}

	else
	{
		return 0;  //La pila no se encuentra llena
	}
}


// encolamos el valor x en Q.
// Si se acaba el espacio entonces se duplica la capacidad
void encolar(cola * Q, int x)
{
    if (colaLlena(Q) == 1)
    { // si esta llena duplicamos capacidad
        Q-> capacity = 2 * Q-> capacity; // duplicamos la capacidad
        Q-> array = realloc(Q-> array,Q-> capacity * sizeof(cola));
        // en este caso se cumple que head==tail
        // movemos lo que está antes de head después del último
        memcpy(Q-> array+  Q-> size, Q-> array, Q-> head);
        Q->tail = Q->head + Q->size; // después del primero
    }

    //ahora se asegura espacio disponible -> encolar
    Q->array[Q->tail] = x; // se encola

    if (Q->tail == Q->capacity)
    { // si se pasó
        Q->tail = 0; // vuelta al inicio
    } 
	else 
	{ // si no, puesto disponible en +1
        Q->tail = Q->tail + 1;
        Q->size = Q->size+1; // actualizo el tamaño 
    }
}


//Se pregunta si la cola está vacía
int colaVacia(cola *Q)
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
int desencolar(cola *Q)
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

//*******************************************************************************************************
int leerMatriz(int filas, int columnas, int (*a)[columnas], char* filename, cola * contagiosI, cola * contagiosJ)
{
    FILE *pf;
    pf = fopen (filename, "r");

    if (pf == NULL) {
    	printf("Archivo no existe\n");
        return 0;
    }

    int aux;
    fscanf(pf, "%d", &aux);
    fscanf(pf, "%d", &aux);
    

    for(int i = 0; i < filas; ++i)
    {
        for(int j = 0; j < columnas; ++j)
        {
        
            if (fscanf(pf, "%d", &(a[i][j])) == EOF) 
            {
            	printf("Formato de archivo incorrecto\n");
              	return(0);
            } 

            else if (a[i][j] == 2)  //Al encontrarse con un contagiado (2), lo agrega inmediatamente a la lista de contagiados
            {
            	printf("x: %d, y: %d\n", i,j);
            	encolar(contagiosI, i);
            	encolar(contagiosJ, j);
            }
        }
    }

    fclose (pf);
    return 1; 
}

//********************************** CONDICIONES PARA CONTAGIAR ***************************************
int puedoContagiarNorte (int i, int j, int columnas, int matriz[][columnas])
{
	if (i-1 >= 0 && matriz[i-1][j] == 1)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

int puedoContagiarSur (int i, int j, int columnas, int matriz[][columnas], int filas)
{
	if (i+1 < filas && matriz[i+1][j] == 1)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

int puedoContagiarEste (int i, int j, int columnas, int matriz[][columnas] )
{
	if (j+1 < columnas && matriz[i][j+1] == 1)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

int puedoContagiarOeste (int i, int j, int columnas, int matriz[][columnas])
{
	if (j-1 >= 0 && matriz[i][j-1] == 1)
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

int sanos(int filas, int columnas, int matriz[][columnas])
{
	int sanos = 0;

	for (int i = 0; i < filas; ++i)
	{
		for (int j = 0; j < columnas; ++j)
		{
			if (matriz[i][j] == 1)
			{
				sanos++;
			}
		}
	}

	return sanos;
}

//Cuenta la cantidad de contagiados en el plano
int enfermos(int filas, int columnas, int matriz[][columnas])  //Recibe como entrada la matriz con las personas, la cantidad de filas y columnas de la matriz
{
	int enfermo = 0;  //Se crea la variable para almacenar la cantidad de contagiados 

	for (int i = 0; i < filas; ++i)
	{
		for (int j = 0; j < columnas; ++j)
		{
			if (matriz[i][j] == 2)  //Si la persona está contagiada (2) se añade a la cuenta de enfermos
			{
				enfermo++;
			}
		}
	}

	return enfermo;  //Se retorna la cantidad total de contagiados (enfermos)
}

//************************* CONTAGIAR *****************************************************************

int contagiar(int filas, int columnas, int matriz[][columnas], cola * contagiosI, cola * contagiosJ)
{
	int t = 0;  //Tiempo transcurrido
	int contagiados = enfermos(filas, columnas, matriz);
	int contagiosRevisar = contagiados;  //Inicialmente se de deberá revisar a todos los contagiados
	printf("Cantidad contagiados: %d\n", contagiosRevisar);
	int i, j;

	while (contagiosRevisar != 0)
	{
		for (int k = 0; k < contagiosRevisar; k++)  //Ciclos de paso de tiempo
		{
			printf("Comence el for\n");
			i = desencolar(contagiosI);
			printf("i: %d\n",i );
			j = desencolar(contagiosJ);
			printf("j: %d\n",j );

			//Ya que al crear un arreglo la memoria puede contener valores previos, esta condicion se asegura de que se esten utilizando indices dentro de la matriz
			//Cuando la cola está "vacia", los otros indices siguen teniendo valores previos los cuales exeden los limites de la matriz
			//Esto ocurre cuando no se puede contagiar a todas las personas, por lo que en ese caso, restorna -1
			if (i > filas || j > columnas)  
			{
				return -1;
			}
			

			//******************************** COMPROBAR MOVIMIENTOS**********************************************
			printf("\n");
			printf("Norte: %d\n", puedoContagiarNorte(i, j, columnas, matriz) );
			printf("Sur: %d\n", puedoContagiarSur(i, j, columnas, matriz, filas) );
			printf("Este: %d\n", puedoContagiarEste(i, j, columnas, matriz));
			printf("Oeste: %d\n", puedoContagiarOeste(i, j, columnas, matriz));
			printf("Tiempo: %d\n", t);
			printf("\n");


			if (puedoContagiarNorte(i, j, columnas, matriz))
			{
				matriz[i-1][j] = 2;
				encolar(contagiosI, i-1);
				encolar(contagiosJ, j);

				//********************************************
				printf("Norte\n");
				for(int i = 0; i < 4; ++i)
			    {
			        for(int j = 0; j < 4; ++j)
			            printf("%3d ", matriz[i][j]);
			        puts("");
		    	}
		    	printf("\n");

		    //********************************************
				if (sanos(filas, columnas, matriz) == 0)
				{
					return t+1;  //Debe retornar t+1 ya que está haciendo un nuevo cambio, pero como escapa de la función antes de terminar el ciclo, debemos sumarle 1 a t
				}
			}

		
			if (puedoContagiarSur(i, j,columnas, matriz, filas))
			{
				matriz[i+1][j] = 2;
				encolar(contagiosI, i+1);
				encolar(contagiosJ, j);

				//********************************************
				printf("Sur\n");
				for(int i = 0; i < 4; ++i)
		    	{
		        	for(int j = 0; j < 4; ++j)
		            	printf("%3d ", matriz[i][j]);
		        	puts("");
		    	}
		    	printf("\n");
		    	//********************************************

				if (sanos(filas, columnas, matriz) == 0)
				{
					return t+1;  //Debe retornar t+1 ya que está haciendo un nuevo cambio, pero como escapa de la función antes de terminar el ciclo, debemos sumarle 1 a t
				}
			}

		
			if (puedoContagiarEste(i, j, columnas, matriz))
			{
				matriz[i][j+1] = 2;
				encolar(contagiosI, i);
				encolar(contagiosJ, j+1);

				//********************************************
				//printf("Sanos Este: \n", sanos(matriz, filas, columnas));
				printf("Este\n");

				for(int i = 0; i < 4; ++i)
			    {
			        for(int j = 0; j < 4; ++j)
			            printf("%3d ", matriz[i][j]);
			        puts("");
			    }
			    printf("\n");
			    //********************************************
			    //printf("Sanos Este: \n", sanos(matriz, filas, columnas));
				if (sanos(filas, columnas, matriz) == 0)
				{
					return t+1;  //Debe retornar t+1 ya que está haciendo un nuevo cambio, pero como escapa de la función antes de terminar el ciclo, debemos sumarle 1 a t
				}
			}

		
			if (puedoContagiarOeste(i, j, columnas, matriz))
			{
				printf("Entre a Oeste\n");
				matriz[i][j-1] = 2;
				encolar(contagiosI, i);
				encolar(contagiosJ, j-1);

				//********************************************
				printf("Oeste\n");
				for(int i = 0; i < 4; ++i)
			    {
			        for(int j = 0; j < 4; ++j)
			            printf("%3d ", matriz[i][j]);
			        puts("");
			    }
			    printf("\n");
			    //********************************************

				if (sanos(filas, columnas, matriz) == 0)
				{
					return t+1;  //Debe retornar t+1 ya que está haciendo un nuevo cambio, pero como escapa de la función antes de terminar el ciclo, debemos sumarle 1 a t
				}
			}
		}

		printf("Enfermos = %d\n", enfermos(filas, columnas, matriz) );
		contagiosRevisar = enfermos(filas, columnas, matriz) - contagiados;  //La diferencia entre enfermos y contagios, son los contagiados nuevos que se revisaran en el for
		contagiados = enfermos(filas, columnas, matriz);  //Se actualiza la nueva contidad de contagiados en el plano
		printf("En el proximo loop se revisaran: %d\n", contagiosRevisar);
		t++;
	}

	return -1;
}


//**********************************************************************


int main()
{
	//**********************************************************************


	//int matriz[3][4];
	cola * contagiosI = crear_cola();
    cola * contagiosJ = crear_cola();
    char nombreArchivo[100];

    printf("Ingrese nombre de archivo matriz P: ");
    scanf("%s", &nombreArchivo);
    printf("\n");

    FILE* miarchivo = NULL;
    int filas, columnas;
    miarchivo = fopen(nombreArchivo, "r");
	if (miarchivo == NULL)
	{
		printf("Archivo no existe\n");
		return 0;
	}

	fscanf(miarchivo, "%d", &filas);
	fscanf(miarchivo, "%d", &columnas);
	fclose(miarchivo);

	int matriz [filas][columnas];


    int r = leerMatriz(filas, columnas, matriz, nombreArchivo, contagiosI, contagiosJ);

    if (r==0) {
      // debiesen mostrar error
      return(0);
    }

    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
            printf("%3d ", matriz[i][j]);
        puts("");
    }
    //********************************************************************
    
	int resultado = contagiar(filas, columnas,matriz, contagiosI, contagiosJ);
    if (resultado == -1)
    {
    	printf("No se logro contagiar a todas las personas.\n");
    }

    else
    {
    	printf("T = %d \n", resultado);
    }

	return 0;
}