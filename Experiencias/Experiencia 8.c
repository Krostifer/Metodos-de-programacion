//Christofer Rodriguez, 20.239.786-7, christofer.rodriguez@usach.cl, secion L-6
#include <stdio.h>
#include <stdlib.h>

typedef struct shanoi
{
            int *A;  //Arreglo que representa la torre de origen 
            int *B;  //Arreglo que representa la torre de destino
            int *C;  //Arreglo que representa la torre auxiliar
            int size;  //Tamaño maximo de los arreglos igual a la cantidad de discos a usar
            
            int n_A;  //Cantidad de discos en A
            int n_B;  //Cantidad de discos en B
            int n_C;  // Cantidad de discos en C

            int idEstado;  // Identificacion del estado actual
            int idEstadoAnterior; // Identificacion del estado del cual proviene
            int transicion;  //Operacion que se realizo para generar este
} hanoi;

//"Borra" un estado de una lista y lo retorna para utilizarlo (copia el estado y actualiza el indice del ultimo elemento para que cuando se agregue uno nuevo lo reemplace)
hanoi sacarEstado (hanoi * lista, int *lenLista)  
{
	hanoi pop;

	//Copiar torres
	pop.A = (int*)malloc(sizeof(int)*lista[0].size);
	for (int i=0; i < lista[0].size; i++)
	{
		pop.A[i] = lista[0].A[i];
	}

	pop.B = (int*)malloc(sizeof(int)*lista[0].size);
	for (int i=0; i < lista[0].size; i++)
	{
		pop.B[i] = lista[0].B[i];
	}

	pop.C = (int*)malloc(sizeof(int)*lista[0].size);
	for (int i=0; i < lista[0].size; i++)
	{
		pop.C[i] = lista[0].C[i];
	}
	//

	pop.size = lista[0].size;
	pop.n_A = lista[0].n_A;
	pop.n_B = lista[0].n_B;
	pop.n_C = lista[0].n_C;
	pop.idEstado = lista[0].idEstado;
	pop.idEstadoAnterior = lista[0].idEstadoAnterior;
	pop.transicion = lista[0].transicion;

	*lenLista = *lenLista-1;

	return pop;
}


//Agrega un estado a una lista de estados
hanoi * agregarEstado (hanoi * lista, int * lenLista, hanoi estadoAgregar)
{
	hanoi * nuevaLista = (hanoi*)malloc(sizeof(hanoi)*((*lenLista)+1));
	
	for (int i = 0; i < *lenLista; ++i){
		
		//Copiar las torres***************************************************
		nuevaLista[i].A = (int*)malloc(sizeof(int)*lista[i].size);
        for (int j=0; j < lista[i].size; j++)
        {
            nuevaLista[*lenLista].A[i] = lista[i].A[j];
        }

        nuevaLista[i].B = (int*)malloc(sizeof(int)*lista[i].size);
        for (int j=0; j < lista[i].size; j++)
        {
            nuevaLista[*lenLista].B[i] = lista[i].B[j];
        }

		nuevaLista[i].C = (int*)malloc(sizeof(int)*lista[i].size);
        for (int j=0; j < lista[i].size; j++)
        {
            nuevaLista[*lenLista].C[i] = lista[i].C[j];
        }
		//************************************************************

		nuevaLista[i].size = lista[i].size;
		nuevaLista[i].n_A = lista[i].n_A;
		nuevaLista[i].n_B = lista[i].n_B;
		nuevaLista[i].n_C = lista[i].n_C;

		nuevaLista[i].idEstado = lista[i].idEstado;
		nuevaLista[i].idEstadoAnterior = lista[i].idEstadoAnterior;
		nuevaLista[i].transicion = lista[i].transicion;
	}

	//Aqui se agrega el nuevo elemento
	//Copiar las torres*************************************************
	nuevaLista[*lenLista].A = (int*)malloc(sizeof(int)*estadoAgregar.size);
	for (int i=0; i < estadoAgregar.size; i++)
    {
        nuevaLista[*lenLista].A[i] = estadoAgregar.A[i];
    }

    nuevaLista[*lenLista].B = (int*)malloc(sizeof(int)*estadoAgregar.size);
    for (int i=0; i < estadoAgregar.size; i++)
    {
        nuevaLista[*lenLista].B[i] = estadoAgregar.B[i];
    }

    nuevaLista[*lenLista].C = (int*)malloc(sizeof(int)*estadoAgregar.size);
    for (int i=0; i < estadoAgregar.size; i++)
    {
        nuevaLista[*lenLista].C[i] = estadoAgregar.C[i];
    }
	//******************************************************************************

	nuevaLista[*lenLista].size = estadoAgregar.size;
	nuevaLista[*lenLista].n_A = estadoAgregar.n_A;
	nuevaLista[*lenLista].n_B = estadoAgregar.n_B;
	nuevaLista[*lenLista].n_C = estadoAgregar.n_C;

	nuevaLista[*lenLista].idEstado = estadoAgregar.idEstado;
	nuevaLista[*lenLista].idEstadoAnterior = estadoAgregar.idEstadoAnterior;
	nuevaLista[*lenLista].transicion = estadoAgregar.transicion;
	
	free(lista);
	
	*lenLista = *lenLista + 1;

	return nuevaLista;
}

//Agrega una transicion a la lista de transiciones ralizadas para llegar a la solucion
int * agregarTransicion(int* listado, int* tamanio, int transicion)
{
	int* nuevo=(int*)malloc(sizeof(int)*(*tamanio+1));

	for (int i = 0; i < *tamanio; ++i)
	{
		nuevo[i] = listado[i];
	}

	nuevo[*tamanio]=transicion;
	*tamanio=*tamanio+1;

	free(listado);

	return nuevo;
}

//Funcion que muestra las transiciones hechas para llegar a la solucion
void mostrarSolucion(hanoi estadoActual, hanoi * cerrados, int cantCerrados)
{
	int idBuscado = estadoActual.idEstadoAnterior;

	int posEstadoAnterior = 0, cantidad = 1;
	int* transiciones = (int*)malloc(sizeof(int)*1);
	transiciones[0]=estadoActual.transicion;

	while(idBuscado != 0)
	{
		for (int i = 0; i < cantCerrados; ++i)
		{
			if(idBuscado == cerrados[i].idEstado)
			{
				posEstadoAnterior = i;
			}
		}
		idBuscado = cerrados[posEstadoAnterior].idEstadoAnterior;
		transiciones = agregarTransicion(transiciones, &cantidad, cerrados[posEstadoAnterior].transicion);
	}

	for (int i = cantidad; i > 0; i--)
	{
		if(transiciones[i]==0)
			printf("Inicio");
		if(transiciones[i]==1)
			printf("A->B");
		if(transiciones[i]==2)
			printf("A->C");
		if(transiciones[i]==3)
			printf("B->A");
		if(transiciones[i]==4)
			printf("B->C");
		if(transiciones[i]==5)
			printf("C->A");
		if(transiciones[i]==6)
			printf("C->B");
		printf("\n");
	}
	printf("Fin\n");
	
}
//********************** VERIFICARIFICACIONES ****************************

//Comprueba que el estado ingresado sea el estado final del problema
int esFinal (hanoi estado, int cantDiscos)
{
	if (estado.n_B == cantDiscos)  //Si la cantidad de elementos en la torre B es igual a la cantidad de discos, significa que todos los discos están en la torre B
	{
		return 1;  //Retorna verdadero, indicando que esl estado ingresado es el el estado final del problema
	}

	else
	{
		return 0;  //Retorna falso, indicando que el estado ingresado no es el estado final del problema
	}
}

//Revisa que el estado entregado no se encuentre dentro de la lista de estados cerrados
int noEstaCerrado (hanoi estado, hanoi * estadosCerrados, int lenCerrados)
{
	for (int i=0; i < lenCerrados; i++)
	{
		int torresIguales = 0;

		if (estado.n_A == estadosCerrados[i].n_A)
		{
			int igualesA = 0; //Cuenta la cantidad de elementos iguales que hay en la torre A

			for (int a=0; a < estado.n_A; a++)
			{
				if (estado.A[a] == estadosCerrados[i].A[a])
				{
					igualesA += 1;
				}
			}

			if (igualesA == estado.n_A)
			{
				torresIguales += 1;
			}
		}

		if (estado.n_B == estadosCerrados[i].n_B)
		{
			int igualesB = 0; //Cuenta la cantidad de elementos iguales que hay en la torre B

			for (int b=0; b < estado.n_B; b++)
			{
				if (estado.B[b] == estadosCerrados[i].B[b])
				{
					igualesB += 1;
				}
			}

			if (igualesB == estado.n_B)
			{
				torresIguales += 1;
			}
		}

		if (estado.n_C == estadosCerrados[i].n_C)
		{
			int igualesC = 0; //Cuenta la cantidad de elementos iguales que hay en la torre B

			for (int c=0; c < estado.n_C; c++)
			{
				if (estado.C[c] == estadosCerrados[i].C[c])
				{
					igualesC += 1;
				}
			}

			if (igualesC == estado.n_C)
			{
				torresIguales += 1;
			}
		}

		if (torresIguales == 3)
		{
			return 0;  //Si la cantidad de torres iguales es igual a 3 (cantidad e torres totales), significa que el estado ya se encuentra, por lo que retorna 0
		}
	}

	return 1;  //Si sale del ciclo, significa que no encontro un estado igual, por lo que retornará verdadero
}

//Revisa que el estado entregado no se encuentre dentro de la lista de estados abiertos
int noEstaAbierto (hanoi estado, hanoi * estadosAbiertos, int lenAbiertos)
{
	for (int i=0; i < lenAbiertos; i++)
	{
		int torresIguales = 0;

		if (estado.n_A == estadosAbiertos[i].n_A)
		{
			int igualesA = 0; //Cuenta la cantidad de elementos iguales que hay en la torre A

			for (int a=0; a < estado.n_A; a++)
			{
				if (estado.A[a] == estadosAbiertos[i].A[a])
				{
					igualesA += 1;
				}
			}

			if (igualesA == estado.n_A)
			{
				torresIguales += 1;
			}
		}

		if (estado.n_B == estadosAbiertos[i].n_B)
		{
			int igualesB = 0; //Cuenta la cantidad de elementos iguales que hay en la torre B

			for (int b=0; b < estado.n_B; b++)
			{
				if (estado.B[b] == estadosAbiertos[i].B[b])
				{
					igualesB += 1;
				}
			}

			if (igualesB == estado.n_B)
			{
				torresIguales += 1;
			}
		}

		if (estado.n_C == estadosAbiertos[i].n_C)
		{
			int igualesC = 0; //Cuenta la cantidad de elementos iguales que hay en la torre B

			for (int c=0; c < estado.n_C; c++)
			{
				if (estado.C[c] == estadosAbiertos[i].C[c])
				{
					igualesC += 1;
				}
			}

			if (igualesC == estado.n_C)
			{
				torresIguales += 1;
			}
		}

		if (torresIguales == 3)
		{
			return 0;  //Si la cantidad de torres iguales es igual a 3 (cantidad e torres totales), significa que el estado ya se encuentra, por lo que retorna 0
		}
	}

	return 1;  //Si sale del ciclo, significa que no encontro un estado igual, por lo que retornará verdadero
}

//Verifica que se pueda realizar la accion de mover un disco desde la torre A a la torre B
int verificarAB(hanoi estado, hanoi * estadosAbiertos, int lenAbiertos, hanoi * estadosCerrados, int lenCerrados)  //Recibe como argumento el estado al que se desea saber si se puede hacer moverAB
{
	if (estado.n_B == 0 && noEstaCerrado(estado, estadosCerrados, lenCerrados) && noEstaAbierto(estado, estadosAbiertos, lenAbiertos))
	{
		return 1;  //Retorna verdadero si la nueva torre está vacia y es un estado nuevo
	}

	else if (estado.A[estado.n_A - 1] < estado.B[estado.n_B - 1] && noEstaCerrado(estado, estadosCerrados, lenCerrados) && noEstaAbierto(estado, estadosAbiertos, lenAbiertos))  //Se comprueba de que el disco superior de A sea más pequeño que el de B y que el nuevo estado no este ya en cerrados o abiertos
	{
		return 1;  //Retorna verdadero
	}

	else
	{
		return 0;  //Retorna Falso
	}
}

//Verifica que se pueda realizar la accion de mover un disco desde la torre A a la torre C
int verificarAC(hanoi estado, hanoi * estadosAbiertos, int lenAbiertos, hanoi * estadosCerrados, int lenCerrados)  //Recibe como argumento el estado al que se desea saber si se puede hacer moverAC
{
	if (estado.n_C == 0 && noEstaCerrado(estado, estadosCerrados, lenCerrados) && noEstaAbierto(estado, estadosAbiertos, lenAbiertos))
	{
		return 1;  //Retorna verdadero si la nueva torre está vacia y es un estado nuevo
	}
	
	else if (estado.A[estado.n_A - 1] < estado.C[estado.n_C - 1] && noEstaCerrado(estado, estadosCerrados, lenCerrados) && noEstaAbierto(estado, estadosAbiertos, lenAbiertos))  //Se comprueba de que el disco superior de A sea más pequeño que el de C y que el nuevo estado no este ya en cerrados o abiertos
	{
		return 1;  //Retorna verdadero
	}

	else
	{
		return 0;  //Retorna falso
	}
}

//Verifica que se pueda realizar la accion de mover un disco desde la torre B a la torre A
int verificarBA(hanoi estado, hanoi * estadosAbiertos, int lenAbiertos, hanoi * estadosCerrados, int lenCerrados)  //Recibe como argumento el estado al que se desea saber si se puede hacer moverBA
{
	if (estado.n_A == 0 && noEstaCerrado(estado, estadosCerrados, lenCerrados) && noEstaAbierto(estado, estadosAbiertos, lenAbiertos))
	{
		return 1;  //Retorna verdadero si la nueva torre está vacia y es un estado nuevo
	}

	else if (estado.B[estado.n_B - 1] < estado.A[estado.n_A - 1] && noEstaCerrado(estado, estadosCerrados, lenCerrados) && noEstaAbierto(estado, estadosAbiertos, lenAbiertos))  //Se comprueba de que el disco superior de B sea más pequeño que el de A y que el nuevo estado no este ya en cerrados o abiertos
	{
		return 1;  //Retorna verdadero
	}

	else
	{
		return 0;  //Retorna falso
	}
}

//Verifica que se pueda realizar la accion de mover un disco desde la torre B a la torre C
int verificarBC(hanoi estado, hanoi * estadosAbiertos, int lenAbiertos, hanoi * estadosCerrados, int lenCerrados)  //Recibe como argumento el estado al que se desea saber si se puede hacer moverBC
{
	if (estado.n_C == 0 && noEstaCerrado(estado, estadosCerrados, lenCerrados) && noEstaAbierto(estado, estadosAbiertos, lenAbiertos))
	{
		return 1;  //Retorna verdadero si la nueva torre está vacia y es un estado nuevo
	}

	if (estado.B[estado.n_B - 1] < estado.C[estado.n_C - 1] && noEstaCerrado(estado, estadosCerrados, lenCerrados) && noEstaAbierto(estado, estadosAbiertos, lenAbiertos))  //Se comprueba de que el disco superior de B sea más pequeño que el de C y que el nuevo estado no este ya en cerrados o abiertos
	{
		return 1;  //Retorna verdadero
	}

	else
	{
		return 0;  //Retorna falso
	}
}

//Verifica que se pueda realizar la accion de mover un disco desde la torre C a la torre A
int verificarCA(hanoi estado, hanoi * estadosAbiertos, int lenAbiertos, hanoi * estadosCerrados, int lenCerrados)  //Recibe como argumento el estado al que se desea saber si se puede hacer moverCA
{
	if (estado.n_A == 0 && noEstaCerrado(estado, estadosCerrados, lenCerrados) && noEstaAbierto(estado, estadosAbiertos, lenAbiertos))
	{
		return 1;  //Retorna verdadero si la nueva torre está vacia y es un estado nuevo
	}

	else if (estado.C[estado.n_C - 1] < estado.A[estado.n_A - 1] && noEstaCerrado(estado, estadosCerrados, lenCerrados) && noEstaAbierto(estado, estadosAbiertos, lenAbiertos))  //Se comprueba de que el disco superior de C sea más pequeño que el de A y que el nuevo estado no este ya en cerrados o abiertos
	{
		return 1;  //Retorna verdadero
	}

	else
	{
		return 0;  //Retorna falso
	}
}

//Verifica que se pueda realizar la accion de mover un disco desde la torre C a la torre B
int verificarCB(hanoi estado, hanoi * estadosAbiertos, int lenAbiertos, hanoi * estadosCerrados, int lenCerrados)  //Recibe como argumento el estado al que se desea saber si se puede hacer moverCB
{
	if (estado.n_B == 0 && noEstaCerrado(estado, estadosCerrados, lenCerrados) && noEstaAbierto(estado, estadosAbiertos, lenAbiertos))
	{
		return 1;  //Retorna verdadero si la nueva torre está vacia y es un estado nuevo
	}

	else if (estado.C[estado.n_C - 1] < estado.B[estado.n_B - 1] && noEstaCerrado(estado, estadosCerrados, lenCerrados) && noEstaAbierto(estado, estadosAbiertos, lenAbiertos))  //Se comprueba de que el disco superior de C sea más pequeño que el de B y que el nuevo estado no este ya en cerrados o abiertos
	{
		return 1;  //Retorna verdadero
	}

	else
	{
		return 0; //Retorna falso
	}
	
}


//********************** TRANSICIONES ****************************

//Funcion que genera el nuevo estado luego de mover un disco desde A a B
hanoi moverAB(hanoi estadoAntiguo, int tamanio, int nuevoId)
{
	hanoi nuevoEstado;

	nuevoEstado.B = (int*)malloc(sizeof(int)*tamanio);  //Torre que recibe el disco
	for (int i=0; i < estadoAntiguo.n_B; i++)
	{
		nuevoEstado.B[i] = estadoAntiguo.B[i];
	}
	nuevoEstado.B[estadoAntiguo.n_B] = estadoAntiguo.A[estadoAntiguo.n_A];  //Pasamos el ultimo elemento de la torre A al final de la torre B

	nuevoEstado.A = (int*)malloc(sizeof(int)*tamanio);  //Torre que se le quita un disco
	for (int i=0; i < estadoAntiguo.n_A - 1; i++)  //Se ve hasta n_A -1 ya que pasamos el ultimo elemento a la torre B
	{
		nuevoEstado.A[i] = estadoAntiguo.A[i];
	}

	nuevoEstado.C = (int*)malloc(sizeof(int)*tamanio);  //Torre que se mantiene igual
	for (int i=0; i < estadoAntiguo.n_C; i++)
	{
		nuevoEstado.C[i] = estadoAntiguo.C[i];
	}

	nuevoEstado.size = tamanio;
	nuevoEstado.n_A = estadoAntiguo.n_A - 1;
	nuevoEstado.n_B = estadoAntiguo.n_B + 1;
	nuevoEstado.n_C = estadoAntiguo.n_C;

	nuevoEstado.idEstado = nuevoId;
	nuevoEstado.idEstadoAnterior = estadoAntiguo.idEstado;
	nuevoEstado.transicion = 1;

	return nuevoEstado;
}

//Funcion que genera el nuevo estado luego de mover un disco desde A a C
hanoi moverAC(hanoi estadoAntiguo, int tamanio, int nuevoId)
{	
	hanoi nuevoEstado;

	nuevoEstado.C = (int*)malloc(sizeof(int)*tamanio);  //Torre que recibe el disco
	for (int i=0; i < estadoAntiguo.n_C; i++)
	{
		nuevoEstado.C[i] = estadoAntiguo.C[i];
	}
	nuevoEstado.C[estadoAntiguo.n_C] = estadoAntiguo.A[estadoAntiguo.n_A];  //Pasamos el ultimo elemento de la torre A al final de la torre C

	nuevoEstado.A = (int*)malloc(sizeof(int)*tamanio);  //Torre que se le quita un disco
	for (int i=0; i < estadoAntiguo.n_A - 1; i++)  //Se ve hasta n_A -1 ya que pasamos el ultimo elemento a la torre C
	{
		nuevoEstado.A[i] = estadoAntiguo.A[i];
	}

	nuevoEstado.B = (int*)malloc(sizeof(int)*tamanio);  //Torre que se mantiene igual
	for (int i=0; i < estadoAntiguo.n_B; i++)
	{
		nuevoEstado.B[i] = estadoAntiguo.B[i];
	}

	nuevoEstado.size = tamanio;
	nuevoEstado.n_A = estadoAntiguo.n_A - 1;
	nuevoEstado.n_B = estadoAntiguo.n_B;
	nuevoEstado.n_C = estadoAntiguo.n_C + 1;

	nuevoEstado.idEstado = nuevoId;
	nuevoEstado.idEstadoAnterior = estadoAntiguo.idEstado;
	nuevoEstado.transicion = 2;

	return nuevoEstado;
}

//Funcion que genera el nuevo estado luego de mover un disco desde B a A
hanoi moverBA(hanoi estadoAntiguo, int tamanio, int nuevoId)
{	
	hanoi nuevoEstado;

	nuevoEstado.A = (int*)malloc(sizeof(int)*tamanio);  //Torre que recibe el disco
	for (int i=0; i < estadoAntiguo.n_A; i++)
	{
		nuevoEstado.A[i] = estadoAntiguo.A[i];
	}
	nuevoEstado.A[estadoAntiguo.n_A] = estadoAntiguo.B[estadoAntiguo.n_B];  //Pasamos el ultimo elemento de la torre B al final de la torre A

	nuevoEstado.B = (int*)malloc(sizeof(int)*tamanio);  //Torre que se le quita un disco
	for (int i=0; i < estadoAntiguo.n_B - 1; i++)  //Se ve hasta n_A -1 ya que pasamos el ultimo elemento a la torre A
	{
		nuevoEstado.B[i] = estadoAntiguo.B[i];
	}

	nuevoEstado.C = (int*)malloc(sizeof(int)*tamanio);  //Torre que se mantiene igual
	for (int i=0; i < estadoAntiguo.n_C; i++)
	{
		nuevoEstado.C[i] = estadoAntiguo.C[i];
	}

	nuevoEstado.size = tamanio;
	nuevoEstado.n_A = estadoAntiguo.n_A + 1;
	nuevoEstado.n_B = estadoAntiguo.n_B - 1;
	nuevoEstado.n_C = estadoAntiguo.n_C;

	nuevoEstado.idEstado = nuevoId;
	nuevoEstado.idEstadoAnterior = estadoAntiguo.idEstado;
	nuevoEstado.transicion = 3;

	return nuevoEstado;
}

//Funcion que genera el nuevo estado luego de mover un disco desde B a C
hanoi moverBC(hanoi estadoAntiguo, int tamanio, int nuevoId)
{	
	hanoi nuevoEstado;

	nuevoEstado.C = (int*)malloc(sizeof(int)*tamanio);  //Torre que recibe el disco
	for (int i=0; i < estadoAntiguo.n_C; i++)
	{
		nuevoEstado.C[i] = estadoAntiguo.C[i];
	}
	nuevoEstado.C[estadoAntiguo.n_C] = estadoAntiguo.B[estadoAntiguo.n_B];  //Pasamos el ultimo elemento de la torre B al final de la torre C

	nuevoEstado.B = (int*)malloc(sizeof(int)*tamanio);  //Torre que se le quita un disco
	for (int i=0; i < estadoAntiguo.n_B - 1; i++)  //Se ve hasta n_A -1 ya que pasamos el ultimo elemento a la torre C
	{
		nuevoEstado.B[i] = estadoAntiguo.B[i];
	}

	nuevoEstado.A = (int*)malloc(sizeof(int)*tamanio);  //Torre que se mantiene igual
	for (int i=0; i < estadoAntiguo.n_A; i++)
	{
		nuevoEstado.A[i] = estadoAntiguo.A[i];
	}

	nuevoEstado.size = tamanio;
	nuevoEstado.n_A = estadoAntiguo.n_A;
	nuevoEstado.n_B = estadoAntiguo.n_B - 1;
	nuevoEstado.n_C = estadoAntiguo.n_C + 1;

	nuevoEstado.idEstado = nuevoId;
	nuevoEstado.idEstadoAnterior = estadoAntiguo.idEstado;
	nuevoEstado.transicion = 4;

	return nuevoEstado;
}

//Funcion que genera el nuevo estado luego de mover un disco desde C a A
hanoi moverCA(hanoi estadoAntiguo, int tamanio, int nuevoId)
{	
	hanoi nuevoEstado;

	nuevoEstado.A = (int*)malloc(sizeof(int)*tamanio);  //Torre que recibe el disco
	for (int i=0; i < estadoAntiguo.n_A; i++)
	{
		nuevoEstado.A[i] = estadoAntiguo.A[i];
	}
	nuevoEstado.A[estadoAntiguo.n_A] = estadoAntiguo.C[estadoAntiguo.n_C];  //Pasamos el ultimo elemento de la torre C al final de la torre A

	nuevoEstado.C = (int*)malloc(sizeof(int)*tamanio);  //Torre que se le quita un disco
	for (int i=0; i < estadoAntiguo.n_C - 1; i++)  //Se ve hasta n_A -1 ya que pasamos el ultimo elemento a la torre A
	{
		nuevoEstado.C[i] = estadoAntiguo.C[i];
	}

	nuevoEstado.B = (int*)malloc(sizeof(int)*tamanio);  //Torre que se mantiene igual
	for (int i=0; i < estadoAntiguo.n_B; i++)
	{
		nuevoEstado.B[i] = estadoAntiguo.B[i];
	}

	nuevoEstado.size = tamanio;
	nuevoEstado.n_A = estadoAntiguo.n_A + 1;
	nuevoEstado.n_B = estadoAntiguo.n_B;
	nuevoEstado.n_C = estadoAntiguo.n_C - 1;

	nuevoEstado.idEstado = nuevoId;
	nuevoEstado.idEstadoAnterior = estadoAntiguo.idEstado;
	nuevoEstado.transicion = 5;

	return nuevoEstado;
}

//Funcion que genera el nuevo estado luego de mover un disco desde C a B
hanoi moverCB(hanoi estadoAntiguo, int tamanio, int nuevoId)
{	
	hanoi nuevoEstado;

	nuevoEstado.B = (int*)malloc(sizeof(int)*tamanio);  //Torre que recibe el disco
	for (int i=0; i < estadoAntiguo.n_B; i++)
	{
		nuevoEstado.B[i] = estadoAntiguo.B[i];
	}
	nuevoEstado.B[estadoAntiguo.n_B] = estadoAntiguo.C[estadoAntiguo.n_C];  //Pasamos el ultimo elemento de la torre C al final de la torre B

	nuevoEstado.C = (int*)malloc(sizeof(int)*tamanio);  //Torre que se le quita un disco
	for (int i=0; i < estadoAntiguo.n_C - 1; i++)  //Se ve hasta n_A -1 ya que pasamos el ultimo elemento a la torre B
	{
		nuevoEstado.C[i] = estadoAntiguo.C[i];
	}

	nuevoEstado.A = (int*)malloc(sizeof(int)*tamanio);  //Torre que se mantiene igual
	for (int i=0; i < estadoAntiguo.n_A; i++)
	{
		nuevoEstado.A[i] = estadoAntiguo.A[i];
	}

	nuevoEstado.size = tamanio;
	nuevoEstado.n_A = estadoAntiguo.n_A;
	nuevoEstado.n_B = estadoAntiguo.n_B + 1;
	nuevoEstado.n_C = estadoAntiguo.n_C - 1;

	nuevoEstado.idEstado = nuevoId;
	nuevoEstado.idEstadoAnterior = estadoAntiguo.idEstado;
	nuevoEstado.transicion = 6;

	return nuevoEstado;
}



//**********************************************************************************************************************************

int main()
{
	int correlativo = 0;  //Valor que servirá para identidicar los estados
	int cantAbiertos = 0;  //Cantidad inicial de estados en estados abiertos
	int cantCerrados = 0;  //Cantidad inicial de estados en estados cerrados
	hanoi * abiertos = (hanoi *)malloc(sizeof(hanoi)*cantAbiertos);  //Lista de estados abiertos
	hanoi * cerrados = (hanoi *)malloc(sizeof(hanoi)*cantCerrados);  //Lista de estados cerrados

	int discos;
	printf("Ingrese la cantidad de discos para las torres de Hanoi: ");
	scanf("%d", &discos);
	printf("\n");
	if (discos <= 0)
	{
		printf("Favor volver a intentarlo ingresando un valor valido.\n");
		return 0;
	}

	//Definimos el estado inicial**********************************************
	hanoi estadoInicial;

    estadoInicial.A = (int*)malloc(sizeof(int)*discos);  //Se crea el arreglo para la torre A
    for (int i = 0; i < discos; i++)  //Se inicializan los valores iniciales para la torre A poniendo todos los discos en ella
	{
		estadoInicial.A[i] = i+1;
	}

    estadoInicial.B = (int*)malloc(sizeof(int)*discos);  //Se crea el arreglo para la torre B
    for (int i = 0; i< discos; i++)  //Se inicializan los valores del arreglo en cero, ya que inicialmente no hay discos en ella
	{
		estadoInicial.B[i] = 0;
	}

    estadoInicial.C = (int*)malloc(sizeof(int)*discos);  //Se crea el arreglo para la torre C
    for (int i = 0; i < discos; i++)  //Se inicializan los valores del arreglo en cero, ya que inicialmente no hay discos en ella
	{
		estadoInicial.C[i] = 0;
	}

    estadoInicial.size = discos;
    
    estadoInicial.n_A = discos;
    estadoInicial.n_B = 0;
    estadoInicial.n_C = 0;

    estadoInicial.idEstado = 0; 
    estadoInicial.idEstadoAnterior = 0;
    estadoInicial.transicion = 0;
	//***************************************************************************
	abiertos = agregarEstado(abiertos, &cantAbiertos, estadoInicial);

	while (cantAbiertos != 0)
	{
		hanoi estadoActual = sacarEstado(abiertos, &cantAbiertos);  //Se saca el primer estado de la lista de abiertos para trabajar con él
		cerrados = agregarEstado(cerrados, &cantCerrados, estadoActual);  //Se agrega el estado actual a la lista de estados cerrados

		if(esFinal(estadoActual, discos) == 1)  // Si se encontró la solución
		{ 
			mostrarSolucion(estadoActual, cerrados, cantCerrados);  //Acá se imprimen las transiciones aplicadas para llegar a la solucion
			return 0;  //Termina la ejecución del programa
		}

		else  //Caso general donde se aplicarán todas las transiciones posibles verificando previamente si se pueden realizar
		{
			if(verificarAB(moverAB(estadoActual, discos, correlativo), abiertos, cantAbiertos, cerrados, cantCerrados))
			{
				correlativo += 1;
				hanoi nuevoEstado = moverAB(estadoActual, discos, correlativo);
				abiertos = agregarEstado(abiertos, &cantAbiertos, nuevoEstado);
			}

			if(verificarAC(moverAC(estadoActual, discos, correlativo), abiertos, cantAbiertos, cerrados, cantCerrados))
			{
				correlativo += 1;
				hanoi nuevoEstado = moverAC(estadoActual, discos, correlativo);
				abiertos = agregarEstado(abiertos, &cantAbiertos, nuevoEstado);
			}

			if(verificarBA(moverBA(estadoActual, discos, correlativo), abiertos, cantAbiertos, cerrados, cantCerrados))
			{
				correlativo += 1;
				hanoi nuevoEstado = moverBA(estadoActual, discos, correlativo);
				abiertos = agregarEstado(abiertos, &cantAbiertos, nuevoEstado);
			}

			if(verificarBC(moverBC(estadoActual, discos, correlativo), abiertos, cantAbiertos, cerrados, cantCerrados))
			{
				correlativo += 1;
				hanoi nuevoEstado = moverBC(estadoActual, discos, correlativo);
				abiertos = agregarEstado(abiertos, &cantAbiertos, nuevoEstado);
			}

			if(verificarCA(moverBC(estadoActual, discos, correlativo), abiertos, cantAbiertos, cerrados, cantCerrados))
			{
				correlativo += 1;
				hanoi nuevoEstado = moverBC(estadoActual, discos, correlativo);
				abiertos = agregarEstado(abiertos, &cantAbiertos, nuevoEstado);
			}

			if(verificarCB(moverCB(estadoActual, discos, correlativo), abiertos, cantAbiertos, cerrados, cantCerrados))
			{
				correlativo += 1;
				hanoi nuevoEstado = moverCB(estadoActual, discos, correlativo);
				abiertos = agregarEstado(abiertos, &cantAbiertos, nuevoEstado);
			}
		}
	}

	printf("No se encontro una solucion");

	return 0;	
}