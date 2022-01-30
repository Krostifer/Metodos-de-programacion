#include <stdio.h>

int cercano(int *array, int inicio, int final, int comparar)  //Lista de numero, indice inicial del array, indice final del array, numero a buscar en la lista
{
	int centro = (inicio+final)/2;  //Calculamos el centro del array para disminuir los casos

	if (array[centro] == comparar)  //Caso base en el que el numero en el centro del array es el buscado
	{
		return array[centro];
	}

	else if (inicio == final || inicio > final)  //Caso base cuando el numero a buscar no se encuentra dentro del array
	{

		if (comparar - array[centro-1] == array[centro]-comparar)  //En caso de que la diferencia entre el numero central con el numero a buscar y el numero anterior con el numero a buscar sea la misma
		{
			if (array[centro-1] < array[centro])  //En caso de que la diferencia sea la misma, se devolvera el numero menor
			{
				return array[centro-1];
			}

			else
			{
				return array[centro];
			}
		}

		else if (comparar - array[centro-1] < array[centro]-comparar)  //En caso de que el numero a la izquierda del centro sea más cercano al numero a buscar
		{
			return array[centro-1];
		}

		else  //En caso de que el numero central sea más cercano al numero a buscar que el numero a su izquierda
		{
			return array[centro];
		}
	}

	else if (array[centro] > comparar)  //Caso general cuando el numero en el centro sea mayor al numero buscado, disminuimos la busqueda a la parte del array menor al numero central (Izquierda)
	{
		return cercano(array,inicio, centro-1, comparar);
	}

	else if (array[centro] < comparar)  //Caso general cuando el numero en el centro sea menor al numero buscado, disminuimos la busqueda a la parte del array mayor al numero central (Derecha)
	{
		return cercano(array, centro+1, final, comparar);
	}

}

int main()
{

	int a[] = {1,4,5,9,9,10,11,13,35};  //Se define el array con los numeros ordenados
	int inicio = 0, numero;  //Se define el indice inicial del array y se crea la variable para almacenar el numero a buscar

	printf("Indique el numero al que desea buscar su cercano: ");
	scanf("%d", &numero);
	
	printf("\nEl numero mas cercano a: %d dentro de la lista es: %d \n", numero, cercano(a,inicio,8,numero));  //**EL TERCER PARAMETRO EL EL INDICE FINAL DEL ARRAY, PARA QUE FUNCIONE SE DEBE CAMBIAR SI SE MODIFICA EL ARRAY**

	return 0;
}