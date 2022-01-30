//Christofer Rodriguez, 20.239.786-7, christofer.rodriguez@usach.cl, seccion L-6
#include <stdio.h>

int main(){
	//Se establecen las variables
	int largo = 0, numero = 0;
	int lista[100];

	//Bucle para perdir los numero al usuario
	while(numero != -1){
		//Se muestran las instrucciones al usuario y se pide ingrese un numero
		printf("Ingrese un numero para odernar (si desea terminar ingrese -1): \n" );
		scanf("%d",&numero);
		
		if (numero != -1){
			//Se asigna el numero ingresado dentro del arreglo
			lista[largo] = numero;
			//Hacemos avanzar el contador para asignar los numeros en el arreglo y ademas saber la cantidad de numeros
			largo++;
		}
	}
	//Establecemos las variables para los nuevos ciclos de ordenamiento
	int i = 0, aux = 0, j = 0;

	//Ciclo para ordenar
	while (i < largo){
		// j es la posicion del numero con el que se comparara i
		j = i+1;	
		// Se compara si i es menor que j, si lo es, se intercambian
		while (j < largo){
			if(lista[i] < lista[j]){
				aux = lista[i];
				lista[i] = lista[j];
				lista [j] = aux;
				j++;
			} else{
				j++;
			}
		} 
		i++;
	} 
	printf("\n\n");
	printf("***Lista ordenada***\n", largo);

	//Se muestra por pantalla la lista ordenada
	for(int c = 0; c < largo; c++){

		printf("%d\n", lista[c]);
	}

	return 0;
}