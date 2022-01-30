#include <stdio.h>

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

int main()
{
	int buscar;  //Definimos las variables de la raiz a buscar y el 
	int inicio = 1;  // Inicio de la "lista" para la busqueda binaria

	printf("Ingrese el numero al cual desea calcular su raiz cuadrada: ");
	scanf("%d",& buscar);

	if (buscar < 0)  //Como debemos calcular la raiz de un numero entero positivo, comprobamos de que lo sea, si no lo es, terminara el programa.
	{
		printf("Favor volver a intentarlo e ingresar un valor valido\n");
		return 0;
	}

	int final = buscar;  //Final sera igual a buscar, ya que sera el final de la "lista" para la busqueda binaria. 

	printf("\n La raiz cuadrada de: %d, es: %d \n", buscar, raiz(buscar,inicio,final));

	return 0;
}