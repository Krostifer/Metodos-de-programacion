#include <stdio.h>
#include <stdlib.h>


int * crearArray(int tamanio)
{
	int * arreglo = (int*)malloc(sizeof(int)*tamanio);

	for (int i = 0; i < tamanio; ++i)
	{
		arreglo[i] = rand()%50 + 1;
	}

	return arreglo;
}

//Buscará la distancia deseada dentro de los numeros recursivamente y retornará el arreglo con los resultados
int * distanciaRecursiva (int * arreglo, int tamanio, int distancia, int i, int j)  //Recibe como argumentos el arreglo y su tamaño, la distancia a buscar, indice inicial de i y j para comparar
{
	if (i == tamanio)  //Caso base donde no quedan elementos para comparar (pivote es el ultimo numero) y no se encontro una coincidencia
	{
		int * respuesta = (int*)malloc(sizeof(int)*3);  //Se crea el arreglo para almacenar la respuesta final
		respuesta[0] = 0;
		respuesta[1] = 0;
		respuesta[2] = 0;

		return respuesta;  //Retorna el arreglo con la respuesta de que no encontro coincidencia con la distancia
	}

	else if (j == tamanio)  //Caso en el que el pivote se haya restado con todos los otros numeros
	{
		return distanciaRecursiva(arreglo, tamanio, distancia, i+1, 0);  //Se hace la llamada recursiva con el numero siguiente en el arreglo
	}

	else  //Caso general
	{
		if (arreglo[i]-arreglo[j] == distancia)  //Si la resta es igual a la diferencia, retornará el arreglo con la solución
		{
			int * respuesta = (int*)malloc(sizeof(int)*3);  //Se crea el arreglo para almacenar la respuesta final
			respuesta[0] = 1;
			respuesta[1] = arreglo[i];
			respuesta[2] = arreglo[j];
		
			return respuesta;  //Retorna el arreglo con la respuesta final
		}

		else
		{
			return distanciaRecursiva(arreglo, tamanio, distancia, i, j+1);  //Llamada recursiva para comparar al pivote con el siguiente numero
		}
	}
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
	for (int i = 0; i < n; ++i){
		printf("%d - ",arreglo[i]);
	}
	printf("\n");

	/**************************/
	int * resultado = distanciaRecursiva(arreglo, n, d, 0, 1);

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