#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE_STACK 100

//Se define la estructura de una pila
typedef struct spila
{
	int *array;
	int size;
	int top;

} pila;

//Creación de una pila vacia
pila* crear_pila()
{
	pila *p = malloc(sizeof(pila));
	p-> array = malloc(INIT_SIZE_STACK*sizeof(int));
	p-> size = INIT_SIZE_STACK;
	p-> top = -1;
	return p;
}

//Consultar si la pila esta vacia
int pilaVacia(pila *S)
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
void insertar(pila *S, int x)
{
	if (S-> top+1 > S-> size)
	{
		S-> size = 2 * S-> size;
		S-> array = realloc(S-> array, S-> size*sizeof(int));

		if (S -> array == NULL)
		{
			exit(0);  //Sale de la función ya que el array no existe
		}
	}

	S-> top = S-> top+1;
	S-> array[S-> top] = x; 	
}

//Efectua un pop en la pila S dejando el resultado en x*
//Retorna verdadero o falso, dependiendo si la pila esta vacia
int extraer(pila *S, int *x)
{
	if (pilaVacia(S))
	{
		printf("La pila esta vacia\n");
		return 0;  //La pila está vacia por lo que no puede extraer un numeros
	}

	else
	{
		S-> top = S-> top-1;
		*x = S-> array[S-> top+1];
		return 1;
	}
}

//Busca el elemento x en la pila *S, retorna verdadero o falso
int buscar_pila(pila *S, int x)
{
	if (pilaVacia(S))
	{
		return 0;
	}

	else
	{
		for(int k=0; k <= S-> top; k++)
		{
			if (S-> array[k] == x)
			{
				return 1;
			}
		}

		return 0;
	}
}

//Imprime la pila de manera horizontal
void imprimir_pila(pila *S) {

	printf(": ");

	for (int k=1; k <= S->top; k++)
	{
		printf("%d", S-> array[k]);

		if (k < S-> top)  //Comprueba de que queden numeros del array por añadir y asi agregar una coma(,)
		{
			printf(", ");
		}
	}
	printf("\n");
}



//*****************************************SOLUCION*******************************************

void iniciarDiscos (int numeroDiscos, pila *A)
{

	for (int k=numeroDiscos; k>0; k--)
	{
		insertar(A,k);
	}
}

void idDiscos(pila *S, int x)
{
	S-> top = S-> top+1;
	S-> array[S-> top] = x; 	
}

void reconocerId (pila *A, pila *B, pila *C, int id)
{
	if (buscar_pila(A,id))
	{
		imprimir_pila(A);
	}

	else if (buscar_pila(B,id))
	{
		imprimir_pila(B);
	}

	else if (buscar_pila(C,id))
	{
		imprimir_pila(C);
	}
}


void torres(int N, pila *A, pila *B, pila *C)  //N=Cantidad de discos, A=Pila de origen, B=Pila auxiliar, C=Pila de destino
{
	if (N == 1)  //Caso base en donde solo quede un disco en la torre A
	{
		int disco_pop;
		extraer(A, &disco_pop);
		insertar(C, disco_pop);

		//******************************** IMPRIMIR ******************************
		reconocerId (A, B, C, -1);
		reconocerId (A, B, C, -2);
		reconocerId (A, B, C, -3);
		printf("\n");
		//******************************** IMPRIMIR ******************************
	}

	else
	{
		torres(N-1, A, C, B);

		int disco_pop;
		extraer(A, &disco_pop);
		insertar(C, disco_pop);

		//******************************** IMPRIMIR ******************************
		reconocerId (A, B, C, -1);
		reconocerId (A, B, C, -2);
		reconocerId (A, B, C, -3);
		printf("\n");
		//******************************** IMPRIMIR ******************************

		torres(N-1,B, A, C);


	}
}



int main()
{
	
	pila* pila_A = crear_pila();
	idDiscos(pila_A,-1);
	pila* pila_B = crear_pila();
	idDiscos(pila_B,-2);
	pila* pila_C = crear_pila();
	idDiscos(pila_C,-3);
	/*
	int discos;
	printf("Ingrese la cantidad de discos para las torres de Hanoi: \n");
	scanf("%d", &discos);
	*/

	
	iniciarDiscos(3, pila_A);  //Se inicia el juego con los discos indicados
	printf("Inicio del proceso\n");
	imprimir_pila(pila_A);  //Se imprime el estado incial de las pilas
	imprimir_pila(pila_B);  //Se imprime el estado incial de las pilas
	imprimir_pila(pila_C);  //Se imprime el estado incial de las pilas
	printf("\n");  //Salto de linea para separar los estados

	torres(3, pila_A, pila_B, pila_C);

	printf("Final del proceso\n");
	imprimir_pila(pila_A);  //Se imprime el estado incial de las pilas
	imprimir_pila(pila_B);  //Se imprime el estado incial de las pilas
	imprimir_pila(pila_C);  //Se imprime el estado incial de las pilas
	printf("\n");  //Salto de linea para separar los estados

	return 0;

}