#include <stdio.h>

int main(){
	
	int a=3, b=12, c=21, operacion1, operacion2;
	
	operacion1 = (c/a) + (b/a);
	operacion2 = (a+b+c)/a + (b+a)/(c+b);
	
	printf("El resultado de la primera expresion es: %d y el de la segunda expresion es: %d", operacion1, operacion2);
	return 0;
}