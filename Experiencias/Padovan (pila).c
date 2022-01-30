//Christofer Rodriguez, 20.239.786-7, christofer.rodriguez@usach.cl, secion L-6
#include <stdio.h>
#include <time.h>
//Creamos la funcion recursiva para calcular el padovan
int padovan (int n){
	//Primero definimos el caso base del problema
	if (n == 0 || n == 1 || n == 2){
		//Devolvemos el valor del caso base
		return 1;
	}
	//Ahora definimos la llamada recursiva del caso general
	else {
		int pado = padovan(n-2) + padovan(n-3);
		return pado;
	}
}

int main(){
	//Definimos las variables
	int n;
	time_t t_inicial, t_final;

	//Pedimos al usuario ingresar el numero del Padovan que desean conocer
	printf("Ingrese el numero de Padovan que desea calcular: \n");
	scanf("%d", &n);

	//Tomamos el tiempo antes de iniciar
	t_inicial = time(NULL);
	//Calculamos el Padovan
	int resultado = padovan(n);
	//Tomamos el tiempo luego de calcular el Padovan
	t_final = time(NULL);
	
	//Mostramos por pantalla el resultado del calculo y el tiempo demorado
	printf("El Padovan de %d es: %d, esto se calculo en: %f segundos.\n", n, resultado, difftime(t_final,t_inicial));

	return 0;
}