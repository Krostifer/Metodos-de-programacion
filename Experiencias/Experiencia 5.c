//Christofer Rodriguez, 20.239.786-7, christofer.rodriguez@usach.cl, secion L-6
#include <stdio.h>
#include <time.h>
//Creamos la funcion recursiva para calcular el padovan iterativamente
int padovan_It (int n){
	//Primero definimos los casos base del problema
	if (n == 0 || n == 1 || n == 2){
		//Devolvemos el valor del caso base
		return 1;
	}
	//Ahora definimos el ciclo para calcular el Padovan
	else {
		//Definimos los tres primeros numeros de la sucesion
		int a = 1, b = 1, c = 1;
		//Definimos el resto de las variables
		int i = 0;
		int suma;
		//Se incia el ciclo para calcular la sucesion
		while(i < n-2){
			//Caalculamos el Padovan que sigue en la sucesion
			suma = a + b;
			//Comenzamos a mover los numeros a la izquierda para seguir calculando los siguientes numeros de la sucesion
			a = b;
			b = c;
			c = suma;
			//Hacemos avanzar el contador
			i ++;
		}
		return suma;
	}
}

//Creamos la funcion recursiva de pila para calcular el padovan
int padovan_P (int n){
	//Primero definimos el caso base del problema
	if (n == 0 || n == 1 || n == 2){
		//Devolvemos el valor del caso base
		return 1;
	}
	//Ahora definimos la llamada recursiva del caso general
	else {
		int pado = padovan_P(n-2) + padovan_P(n-3);
		return pado;
	}
}

//Creamos la funcion recursiva de cola para calcular el padovan
int padovan_C (int n, int a, int b, int c){

	//Definimos los casos base del problema
	if (n == 0 || n == 1 || n == 2){
		//Devolvemos el valor del ultimo padovan calculado o en el caso base un 1
		return c;
	}
	//Ahora definimos el caso general
	else {

		int suma = a + b;
		//Comenzamos a mover los numeros a la izquierda para seguir calculando los siguientes numeros de la sucesion
		a = b;
		b = c;
		c = suma;
		//Hacemos bajar el numero
		n --;
		//Hacemos las llamada recursiva
		return(padovan_C(n,a,b,c));
		}

}


int main(){
	//Definimos las variables
	int n;
	time_t t_inicial, t_final;

	//Pedimos al usuario ingresar el numero del Padovan que desean conocer
	printf("Ingrese el numero de Padovan que desea calcular: \n");
	scanf("%d", &n);

	//Tomamos el tiempo antes de iniciar la iteracion
	t_inicial = time(NULL);
	//Calculamos el Padovan iterativamente
	int resultado_It = padovan_It(n);
	//Tomamos el tiempo luego de calcular el Padovan
	t_final = time(NULL);
	//Mostramos por pantalla el resultado del calculo y el tiempo demorado
	printf("El Padovan de %d es: %d, esto se calculo en: %f segundos iterativamente.\n", n, resultado_It, difftime(t_final,t_inicial));



	//Tomamos el tiempo antes de iniciar la recursion de pila
	t_inicial = time(NULL);
	//Calculamos el Padovan por recursion de pila
	int resultado_P = padovan_P(n);
	//Tomamos el tiempo luego de calcular el Padovan
	t_final = time(NULL);

	//Mostramos por pantalla el resultado del calculo y el tiempo demorado
	printf("El Padovan de %d es: %d, esto se calculo en: %f segundos por recursion de pila.\n", n, resultado_P, difftime(t_final,t_inicial));



	//Tomamos el tiempo antes de iniciar la recursion de cola
	t_inicial = time(NULL);
	//Calculamos el Padovan por recursion de cola
	int resultado_C = padovan_C(n,1,1,1);
	//Tomamos el tiempo luego de calcular el Padovan
	t_final = time(NULL);

	//Mostramos por pantalla el resultado del calculo y el tiempo demorado
	printf("El Padovan de %d es: %d, esto se calculo en: %f segundos por recursion de cola.\n", n, resultado_C, difftime(t_final,t_inicial));


	return 0;
}