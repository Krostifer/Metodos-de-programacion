//Christofer Rodriguez, 20.239.786-7, christofer.rodriguez@usach.cl, seccion L-6
#include <stdio.h>

//************************************ 1.1 Raiz Cuadrada ************************************

int raiz(int numeroBuscar, int inicio, int final)  //Como sabelos las posibles raices del numero a buscar (desde 1 a n), implementaremos una pseudo busqueda binaria
{
	int mitad = (inicio+final)/2;  //Se busca el centro de la "lista" para reducir los casos y se guarda el numero

	if (mitad*mitad == numeroBuscar)  //Caso base en que el numero en el centro es raiz del numero buscado
	{
		return mitad;
	}

	else if (inicio > final)  //Caso base en caso de las raices inexactas, como solo quedara un numero en la "lista" y no es la raiz del numero, se realizara otro ciclo, provocando que el indice inicial supere al final
	{
		if (numeroBuscar - mitad*mitad < (mitad+1)*(mitad+1)-numeroBuscar)  //En caso de que el cuadrado del numero central sea más cercano al numero a buscar que el cuadrado siguiente
		{
			return mitad;
		}

		else  //En caso de que el cuadrado del numero a la derecha del centro este mas cerca del numero a buscar
		{
			return mitad+1;
		}
	}

	else if (mitad*mitad > numeroBuscar)  //Caso general en el que el cuadrado del numero central sea mayor al numero a buscar, se volvera a buscar solo en la parte menor de la "lista" (Izquierda)
	{
		return raiz(numeroBuscar, inicio, mitad-1);
	}

	else if (mitad*mitad < numeroBuscar)  //Caso general en el que el cuadrado del numero central sea mayor al numero a buscar, se volvera a buscar solo en la parte mayor de la "lista" (Derecha)
	{
		return raiz(numeroBuscar, mitad+1, final);
	}
}

//************************************ 1.2 Buscar numero mas cercano ************************************

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
	//Variables para la "busqueda binaria" de la raiz
	int buscar_raiz;  //Definimos la variable de la raiz a buscar
	int inicio_raiz = 1;  // Inicio de la "lista" para la busqueda binaria de la raiz

	//Variables para la busqueda del numero cercano dentro de una lista
	int a[] = {1,4,5,9,9,10,11,13,35};  //Se define el array con los numeros ordenados
	int inicio_cercano = 0, buscar_cercano;  //Se define el indice inicial del array y se crea la variable para almacenar el numero a buscar

	//Ingreso del numero a buscar su raiz
	printf("Ingrese el numero al cual desea calcular su raiz cuadrada: ");
	scanf("%d",&buscar_raiz);

	//Como debemos calcular la raiz de un numero entero positivo, comprobamos de que lo sea, si no lo es, terminara el programa.
	if (buscar_raiz < 0)  
	{
		printf("Favor volver a intentarlo e ingresar un valor valido.\n");
		return 0;  //Si es que se ingresa un valor invalido a buscar su raiz (negativo), el programa terminará sin ejecutar la busqueda de numero cercano
	}

	int final_raiz = buscar_raiz;  //Final sera igual a buscar, ya que sera el final de la "lista" para la busqueda binaria. 

	//Ingreso del numero a buscar su cercano en la lista
	printf("Indique el numero al que desea buscar su cercano: ");
	scanf("%d", &buscar_cercano);

	//Impresion de los resultados de las operaciones 
	printf("\nLa raiz cuadrada de: %d, es: %d. \n", buscar_raiz, raiz(buscar_raiz,inicio_raiz,final_raiz));
	printf("\nEl numero mas cercano a: %d dentro de la lista es: %d. \n", buscar_cercano, cercano(a,inicio_cercano,8,buscar_cercano));  //**EL TERCER PARAMETRO EL EL INDICE FINAL DEL ARRAY, PARA QUE FUNCIONE SE DEBE CAMBIAR SI SE MODIFICA EL ARRAY**
	

	return 0;
}