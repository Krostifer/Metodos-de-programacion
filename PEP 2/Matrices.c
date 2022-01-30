#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Función que crea la matriz dado el tamaño, se le agregan valores aleatoreamente, en este caso, acorde al tamaño
*/
int ** crearMatriz(int tamanio){
	int ** matriz = (int **)malloc(sizeof(int*)*tamanio);
	
	for (int i = 0; i < tamanio; ++i){
		matriz[i] = (int *)malloc(sizeof(int)*tamanio);
	}
	for (int i = 0; i < tamanio; ++i){
		for (int j = 0; j < tamanio; ++j){
			matriz[i][j] = rand()%tamanio;
		}
	}
	return matriz;
}

/**  INICIO - ACÁ DEBE IR EL CÓDIGO DEL ESTUDIANTE  **/
/*****************************************************/
int buscarMayor (int ** matriz, int tamanio, int inicio_i, int final_i, int inicio_j, int final_j)
{
	if (tamanio == 2)  //Caso base de una matriz 2x2 
	{
		int mayor = 0;

		if (matriz[inicio_i][inicio_j] > mayor)
		{
			mayor = matriz[inicio_i][inicio_j];
		}

		if (matriz[inicio_i][inicio_j+1] > mayor)
		{
			mayor = matriz[inicio_i][inicio_j+1];
		}

		if (matriz[inicio_i+1][inicio_j] > mayor)
		{
			mayor = matriz[inicio_i+1][inicio_j];
		}

		if (matriz[inicio_i+1][inicio_j+1] > mayor)
		{
			mayor = matriz[inicio_i+1][inicio_j+1];
		}

		return mayor;
	}
	
	else  //Caso general donde reduciremos el tamaño de la matriz
	{		
		int mayor=0;

		if (buscarMayor(matriz, tamanio/2, inicio_i, (final_i/2), inicio_j, (final_j/2)) > mayor)
		{
			mayor = buscarMayor(matriz, tamanio/2, inicio_i, (final_i/2), inicio_j, (final_j/2));
		}

		if (buscarMayor(matriz, tamanio/2, inicio_i, (final_i/2), (inicio_j+final_j)/2, final_j ) > mayor)
		{
			mayor = buscarMayor(matriz, tamanio/2, inicio_i, (final_i/2), (inicio_j+final_j)/2, final_j );
		}

		if (buscarMayor(matriz, tamanio/2, (inicio_i+final_i)/2, final_i, inicio_j, final_j) > mayor)
		{
			mayor = buscarMayor(matriz, tamanio/2, (inicio_i+final_i)/2, final_i, inicio_j, final_j);
		}

		if (buscarMayor(matriz, tamanio/2, (inicio_i+final_i)/2, final_i, (inicio_j+final_j)/2, final_j) > mayor)
		{
			mayor = buscarMayor(matriz, tamanio/2, (inicio_i+final_i)/2, final_i, (inicio_j+final_j)/2, final_j);
		}

		return mayor;
	}
}

/*****************************************************/
/**  FIN - ACÁ DEBE IR EL CÓDIGO DEL ESTUDIANTE  **/


/*
FUNCIÓN PRINCIPAL
*/
int main(){
	int n, i=0, validacion = 0; //Varibles a utilizar dentro del código
	while (validacion == 0){ //Validación de que el valor ingresado por el usuario sea una potencia de 2.
		printf("Ingrese el tamanio de la matriz, cuyo valor sea resultado de una potencia de 2:");
		scanf("%d",&n);
		while((int)pow(2,i) <= n){
			if((int)pow(2,i)==n)
				validacion = 1;
			i++;
		}
		if(validacion == 0){
			printf("\nEl valor ingresado no es valido para el problema.\n");
		}
	}
	//Se crea la matriz a trabajar
	int ** matriz = crearMatriz(n);

	//*** ACÁ EL ALUMNO DEBERÁ LLAMAR A LA FUNCIÓN QUE CREO
	/********************************************************/
	int resultado = buscarMayor(matriz, n, 0, n, 0, n);
	printf("El mayor numero dentro de la matriz es: %d\n", resultado);
	/********************************************************/
	//*** FIN DEL 

	printf("La matriz es:\n");
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < n; ++j){
			printf("%4d ", matriz[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < n; ++i){
		free(matriz[i]);
	}
	free(matriz);

	return 0;
}