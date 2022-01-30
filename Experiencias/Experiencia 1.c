//Christofer Rodriguez, 20.239.786-7, christofer.rodriguez@usach.cl, secion L-6
#include <stdio.h>
int main(){
    float a, b, c;
    //Ingreso y asignacion de datos
    printf("Ingrese el primer lado del triangulo: ");
    scanf("%f", &a);
    
    printf("Ingrese el segundo lado del triangulo: ");
    scanf("%f", &b);
    
    printf("Ingrese el tercer lado del triangulo: ");
    scanf("%f", &c);
    
	//Salidas segun los datos ingresados
	
    if(a==0 || b==0 || c==0){
        printf("Las medidas ingresadas no corresponden a un triangulo");
    } else if(a==b && a==c){
        printf("Las medidas ingresadas corresponden a un triangulo equilatero");
    } else if(a==b || a==c || b==c){
        printf("Las medidas ingresadas corresponden a un triangulo isoceles");
    } else{
		printf("Las medidas ingresadas corresponden a un triangulo escaleno");
	}
	return 0;
}
