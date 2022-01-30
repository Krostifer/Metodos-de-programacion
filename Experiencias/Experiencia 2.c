//Christofer Rodriguez, 20.239.786-7, christofer.rodriguez@usach.cl, seccion L-6
#include <stdio.h>

int main(){
	
	int b1=0, b2=0, operacion;
	
	printf("Bienvenido al juego de los bidones.\nEn este juego tienes el bidon 1 con 3 lts max. y el bidon 2 con 5 lts max.\n");
	printf("Ganaras este juego si logras que el bidon 2 tenga 4 lts, solo con las siguientes operaciones:\n");
	printf("(Al mover el agua, solo se mueve lo que permita su capacidad, dejando el resto en el bidon original)\n");
	
	while(b2 != 4){
		
		printf("\nEl estado actual de los bidones es: Bidon 1 = %d lts y Bidon 2 = %d lts\n", b1, b2);
		printf("\nEscriba el numero de la operacion que desea usar:\n (1)Llenar b1\n (2)Llenar b2\n (3)Vaciar b1\n (4)Vaciar b2\n (5)Mover de b1 a b2\n (6)Mover de b2 a b1\n (7)Rendirse\n");
		scanf("%d", &operacion);
		
		if (operacion == 1){
			b1 = 3;
		} else if (operacion == 2){
			b2 = 5;
		} else if (operacion == 3){
			b1 = 0;
		} else if (operacion == 4){
			b2 = 0;
		} else if (operacion == 5){
			
			while(b1>0 && b2<5){
				b1 = b1-1;
				b2 = b2+1;
			}
			
		} else if (operacion == 6){
			
			while(b2>0 && b1<3){
				b2 = b2-1;
				b1 = b1+1;
			}
		} else if (operacion == 7){
				printf("Haz decidido rendirte, por lo tanto perdiste el juego. :(");
				return 0;
		} else {
			printf("Por favor introdusca una opcion valida.\n");
		}
	}
	printf("\nEl estado actual de los bidones es: Bidon 1 = %d lts y Bidon 2 = %d lts\n", b1, b2);
	printf("Felicitaciones, haz ganado. :)");
}