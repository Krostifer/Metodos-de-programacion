#include <stdio.h>

int main(){
	
	float PI = 3.1415926535, perimetro, area;
	int radio = 20;
	
	perimetro = 2 * PI * radio;
	area = PI * radio * radio;
	
	printf("El perimetro de la circunferencia es: %f y el area es: %f", perimetro, area);
	return 0;
}