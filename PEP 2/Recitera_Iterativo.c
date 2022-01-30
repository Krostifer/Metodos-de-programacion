#include <stdio.h>
#include <stdlib.h>

//Crea un arreglo
int * crearArray(int tamanio)  //Recibe como argumento el tamaño del arreglo a generar
{
	int * arreglo = (int*)malloc(sizeof(int)*tamanio);

	for (int i = 0; i < tamanio; ++i)
	{
		arreglo[i] = rand()%50 + 1;
	}
	return arreglo;
}
/*************************************************/

//Buscará la distancia deseada dentro de los numeros iterativamente y retornará el arreglo con los resultados
int * distanciaIterativa(int * arreglo, int distancia, int tamanio)  //Recibe como argumento el arreglo, la distancia a buscar y el tamaño del arreglo
{
	int * respuesta = (int*)malloc(sizeof(int)*3);  //Se crea el arreglo para almacenar la respuesta final

	for (int i = 0; i < tamanio; i++)
	{
		for (int j = 0; j < tamanio; j++)
		{
			if (arreglo[i]-arreglo[j] == distancia)
			{
				respuesta[0] = 1;
				respuesta[1] = arreglo[i];
				respuesta[2] = arreglo[j];

				return respuesta;
			}
		}
	}
	//Si sale del for, significa que no encontro numeros con la diferencia buscada
	respuesta[0] = 0;
	respuesta[1] = 0;
	respuesta[2] = 0;

	return respuesta;
}

/*************************************************/
/*
FUNCIÓN PRINCIPAL
*/
int main()
{
	int n, d;
	printf("Ingrese el tamanio del arreglo a generar: ");
	scanf("%d",&n);

	printf("Ingrese la distancia a buscar: ");
	scanf("%d",&d);

	int * arreglo = crearArray(n);

	printf("\nARREGLO: ");
	for (int i = 0; i < n; ++i)
	{
		printf("%d - ",arreglo[i]);
	}
	printf("\n");

	/**************************/

	int * resultado = distanciaIterativa(arreglo, d, n);

	printf("La respuesta es: ");
	for (int i = 0; i < 3; i++)
	{
		printf("%d - ",resultado[i] );
	}
	printf("\n");

	/**************************/
	free(arreglo);
	free(resultado);

	return 0;
}
