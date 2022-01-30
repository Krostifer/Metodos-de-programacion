//Christofer Rodriguez, 20.239.786-7, christofer.rodriguez@usach.cl, secion L-6
#include <stdio.h>
#include <time.h>
//Creamos la funcion recursiva para calcular el padovan

int padovan (int n, int a, int b, int c){

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
		return(padovan(n,a,b,c));
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
	int resultado = padovan(n,1,1,1);
	//Tomamos el tiempo luego de calcular el Padovan
	t_final = time(NULL);
	
	//Mostramos por pantalla el resultado del calculo y el tiempo demorado
	printf("El Padovan de %d es: %d, esto se calculo en: %f segundos.\n", n, resultado, difftime(t_final,t_inicial));

	return 0;
}