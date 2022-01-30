#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** leer (char * nombre,int *filas,int *col){
    FILE * archivo = fopen(nombre,"r");
	fscanf(archivo,"%d",filas);
	fscanf(archivo,"%d",col);

	char**mapa=(char**) malloc(sizeof(char *)*5);
	
	int i;
	int j;
	char* saltoBasura;
	for(i=0;i<5;i++){
		fscanf(archivo,"%c",&saltoBasura);
		mapa[i]=(char*) malloc(sizeof(char)*5);
		
		for(j=0;j<5;j++)
				if (j!=5)
					fscanf(archivo,"%c",&(mapa[i][j]));			
	}			

	fclose(archivo);
	
	return mapa;
}

void liberar(char**m){
	int i;
	for(i=0;i<5;i++)
			free(m[i]);
	free(m);
	
}

int mostrar(char** mapa,int fc,int cc){
	printf("\nCaballo: %d,%d\n",fc,cc);
	int i,j;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++)
			printf("%c",mapa[i][j]);
		printf("\n");
	}
	return 1;	
}
//*****************************************************************************************************************************************************************************
//Definimos la estructura de los estados
typedef struct Estado
{
	int ** tablero;  //Varible para almacenar el tablero actual del estado
	int posX;  //Variable para almacenar la posicion en X (columna) del caballo actualmente
	int posY;  //Variable para almacenar la posicion en Y (fila) del caballo actualmente
	int id;  //Variable para identificar el estado
	int idAnterior;  //Variable para almacenar el id del estado que generó a este 

} Estado;

//***************************************************** FUNCIONES PRINCIPALES **************************************************************************************
//Funcion que crea el estado inicial del tablero
Estado tableroInicial (char** matriz, int posXCaballo, int posYCaballo)  //Recibe como argumentos la matriz de caracteres (tablero leido) y la posicion en X e Y del caballo
{
	Estado estadoInicial;

	estadoInicial.tablero = (int **)malloc(sizeof(int*)*5);
	for (int i = 0; i < 5; i++)
	{
		estadoInicial.tablero[i] =  (int*)malloc(sizeof(int)*5);
	}

	for (int fila = 0; fila < 5; fila++)
	{
		for (int columna = 0; columna < 5; columna++)
		{
			if (matriz[fila][columna] == 'C')
			{
				estadoInicial.tablero[fila][columna] = 2;  //Escribe como 2 el lugar donde comienza el caballo
			}

			if (matriz[fila][columna] == '_')
			{
				estadoInicial.tablero[fila][columna] = 0;  //Escribe los espacios vacios como 0
			}

			else if (matriz[fila][columna] == 'P')
			{
				estadoInicial.tablero[fila][columna] = 1;  //Escribe las 'P' como 1 para representar los peones en el tablero
			}
		}
	}

	estadoInicial.posX = posXCaballo;
	estadoInicial.posY = posYCaballo;
	estadoInicial.id = 0;
	estadoInicial.idAnterior = 0;

	return estadoInicial;  //Retorna el estado incial del problema
}

//Funcion que agrega un estado a una lista de estados
Estado * agregarEstado (Estado * listaEstados, int *largoLista, Estado estadoAgregar)  //Recibe como elementos una lista de estados (abiertos o cerrados), la cantidad de elementos que tiene esta lista y el estado a agregar
{
    Estado * nuevaLista = (Estado*)malloc(sizeof(Estado)*((*largoLista)+1));  //Se crea una nueva lista con el tamanio nuevo

    //Copiamos los elementos de la lista antigua a la nueva
    for (int i = 0; i < *largoLista; i++)  //Ciclo para recorrer los elementos de la lista
    {
        //Copiamos el tablero **********************************
		nuevaLista[i].tablero = (int **)malloc(sizeof(int*)*5);
		for (int j = 0; j < 5; j++)
		{
			nuevaLista[i].tablero[j] =  (int*)malloc(sizeof(int)*5);
		}
		//Copiamos cada elemento del tablero
		for (int fila = 0; fila < 5; fila++)
		{
			for (int columna = 0; columna < 5; columna++)
			{
				nuevaLista[i].tablero[fila][columna] = listaEstados[i].tablero[fila][columna];
			}
		}
		//*******************************************************
		nuevaLista[i].posX = listaEstados[i].posX;
		nuevaLista[i].posY = listaEstados[i].posY;
        nuevaLista[i].id = listaEstados[i].id;
        nuevaLista[i].idAnterior = listaEstados[i].idAnterior;
    }

    //Ahora copiamos el nuevo estado al final de la lista
    //Copiamos el tablero **********************************
	nuevaLista[*largoLista].tablero = (int **)malloc(sizeof(int*)*5);
	for (int j = 0; j < 5; j++)
	{
		nuevaLista[*largoLista].tablero[j] =  (int*)malloc(sizeof(int)*5);
	}
	//Copiamos cada elemento del tablero
	for (int fila = 0; fila < 5; fila++)
	{
		for (int columna = 0; columna < 5; columna++)
		{
			nuevaLista[*largoLista].tablero[fila][columna] = estadoAgregar.tablero[fila][columna];
		}
	}
	//*******************************************************
	nuevaLista[*largoLista].posX = estadoAgregar.posX;
	nuevaLista[*largoLista].posY = estadoAgregar.posY;
	nuevaLista[*largoLista].id = estadoAgregar.id;
	nuevaLista[*largoLista].idAnterior = estadoAgregar.idAnterior;

    free(listaEstados);  //Liberamos la memoria utilizada por la antigua lista de estados
    *largoLista = *largoLista + 1;  //Actualizamos el largo de la lista de estados
    return nuevaLista;  //Retornamos la nueva lista con los nuevos estados
}

//Funcion que eliminará el primer elemento de una lista de estados y lo retornará para utilizarlo
Estado extraerEstado (Estado * listaEstados, int *largoLista)  //Recibe como argumentos una lista de estados y la cantidad de elementos que posee esta lista de estados
{
    //Creamos un nuevo estado para almacenar el estado a extraer
    Estado pop;
	//Copiamos el tablero **********************************
    pop.tablero = (int **)malloc(sizeof(int*)*5);
	for (int i = 0; i < 5; i++)
	{
		pop.tablero[i] = (int*)malloc(sizeof(int)*5);
	}

	//Copiamos cada elemento del tablero
	for (int fila = 0; fila < 5; fila++)
	{
		for (int columna = 0; columna < 5; columna++)
		{
			pop.tablero[fila][columna] = listaEstados[0].tablero[fila][columna];
		}
	}
	//*******************************************************
	pop.posX = listaEstados[0].posX;
	pop.posY = listaEstados[0].posY;
	pop.id = listaEstados[0].id;
	pop.idAnterior = listaEstados[0].idAnterior;

    //Actualizamos los elementos de la lista de estados copiando los valores de cada estado en el estado anterior a él
    for (int i = 1; i < *largoLista; ++i)
    {
		for (int fila = 0; fila < 5; fila++)
		{
			for (int columna = 0; columna < 5; columna++)
			{
				listaEstados[i-1].tablero[fila][columna] = listaEstados[i].tablero[fila][columna];
			}
		}
		
		listaEstados[i-1].posX = listaEstados[i].posX;
		listaEstados[i-1].posY = listaEstados[i].posY;
		listaEstados[i-1].id = listaEstados[i].id;
		listaEstados[i-1].idAnterior = listaEstados[i].idAnterior;
    }

    *largoLista = *largoLista - 1;  //Actualizamos la nueva cantidad de elementos que tiene la lista

    return pop;  //Retornamos el estado extraido de la lista
}

//Funcion que agrega una posicion a una lista de posiciones, será utilizada para crear una lista con las posiciones recorridas por el caballo que llego a la solucion
int** agregarPosicion(int** listaPosiciones , int* largoLista, Estado estadoAnterior)  //Recibe como argumentos una lista de posiciones (lista de arreglos), la cantidad de elementos que tiene la lista y un estado
{
	int ** nuevaLista = (int **)malloc(sizeof(int*)*(*largoLista + 1));  //Asigamos memoria para una nueva lista con la transicion nueva

    //Copiamos las transiciones anteriores a la nueva lista
	for (int i = 0; i < *largoLista; ++i)
    {
		nuevaLista[i] = (int*)malloc(sizeof(int)*2);;
        nuevaLista[i][0] = listaPosiciones[i][0];
        nuevaLista[i][1] = listaPosiciones[i][1]; 
	}

    //Agregamos la nueva transicion a la nueva lista
	nuevaLista[*largoLista] =  (int*)malloc(sizeof(int)*2);;
    nuevaLista[*largoLista][0] =  estadoAnterior.posY;
    nuevaLista[*largoLista][1] =  estadoAnterior.posX;

	*largoLista = *largoLista + 1;  //Se actualiza la cantidad de elementos que tiene la lista de posiciones
	free(listaPosiciones);  //Se libera la memoria utilizada por la lista anterior
	return nuevaLista;  //Se retorna la nueva lista de posiciones con la posicion agregada
}

//Funcion que mostrara por pantalla los movimientos realizados por el caballo para "comerse" todos los peones
void imprimirSolucion (Estado * listaCerrados, int largoCerrados, Estado solucion)  //Recibe como argumentos una la lista de estados cerrados, la cantidad de elementos cerrados que hay y el estado solucion
{
	int idBuscado = solucion.idAnterior;
    int indiceEstadoAnterior;
    int largoPosiciones = 1;

    int ** posiciones = (int **)malloc(sizeof(int*)*1);  //Creamos una lista de pares para almacenar las posiciones que tuvo el caballo para comer todos los peones

    posiciones[0] = (int*)malloc(sizeof(int)*2);  //Creamos un arreglo de 2 elementos en la primera posicion de la lista para almacenar la posicion final
    posiciones[0][0] = solucion.posY;
    posiciones[0][1] = solucion.posX;

    while (idBuscado != 0)  //Hasta que llegue al estado inicial
    {
       for (int i = 0; i < largoCerrados; ++i)
       {
			if (idBuscado == listaCerrados[i].id)
            {
				indiceEstadoAnterior = i;
			}
		}
		idBuscado = listaCerrados[indiceEstadoAnterior].idAnterior;
		posiciones = agregarPosicion(posiciones, &largoPosiciones, listaCerrados[indiceEstadoAnterior]);
    }

    posiciones = agregarPosicion(posiciones, &largoPosiciones, listaCerrados[0]);  //Agregamos el estado incial a la lista de transiciones

    //Ahora imprimimos las posiciones de la lista de posiciones
	printf("Movimientos para llegar a la solucion: ");
    for (int i = largoPosiciones-1; i >= 0; i--)  //Ciclo para recorrer la lista de transiciones desde atras hacia adelante
    {
        printf("%d,%d ",posiciones[i][0], posiciones[i][1]);
		if (i-1 >= 0)
		{
			printf("- ");
		}
    }
	printf("\n");

	return;
}

//***************************************************** VERIFICACIONES ***********************************************************************************
//Funcion que se encargar de revisar si es que el estado entregado se encuentra dentro de la lista de estados entregada (abiertos o cerrados)
int noEsta (Estado * listaEstados, int largoLista, Estado estadoActual)  //Recibe como argumentos una lista de estados, la cantidad de elementos que tiene esta lista y el estado que se desea comprobar
{
	int iguales;  //Variable que contará la cantidad de elementos iguales que tienen los tableros
    for (int i = 0; i < largoLista; i++)  //Ciclo para recorrer todos los elementos de la lista de estados abiertos
    {
		iguales = 0;
        for (int fila = 0; fila < 5; fila++)
		{
			for (int columna = 0; columna < 5; columna++)
			{
				if (listaEstados[i].tablero[fila][columna] == estadoActual.tablero[fila][columna])
				{
					iguales = iguales + 1;  //Suma 1 cuando los elementos de cada tablero son iguales
				}
			}

			if (iguales == 25)  //Significa que todos los elementos de ambos tableros comparados son iguales
			{
				return 0;  //Retorna 0 indicando que hay un estado igual a él
			}
		}
    }
    return 1;  //Retorna 1, indicando que no existe un estado con la misma posicion
}

//Funcion que cuenta la cantidad de peones restantes del tablero del estado actual
int peonesRestantes (Estado estadoActual)
{
	int peones = 0 ;

	for (int i = 0; i < 5; i++)  //Ciclo para recorrer las filas
	{
		for (int j = 0; j < 5; j++)  //Ciclo para recorrer las columnas
		{
			if (estadoActual.tablero[i][j] == 1)
			{
				peones = peones + 1;
			}
		}
	}

	return peones;  //Retorna la cantidad de peones presentes en el tablero
}

//Funcion que comprobará si se puede reslizar arribaIzquierda
int puedoArribaIzquierda (Estado estadoActual)
{
	if ((estadoActual.posX - 1) >= 0 && (estadoActual.posY - 2) >= 0 && estadoActual.tablero[estadoActual.posY - 2][estadoActual.posX - 1] != 3)  //Se comprueba que la nueva posicion se encuentre dentro del tablero y que sea una casilla valida
	{
		return 1;  //Retorna 1 indicando que si puede realizar el movimiento
	}

	else
	{
		return 0;  //Retorna 0 indicando que no se puede realizar el movimiento
	}
	
}

//Funcion que comprobará si se puede reslizar arribaDerecha
int puedoArribaDerecha (Estado estadoActual)
{
	if ((estadoActual.posX + 1) < 5 && (estadoActual.posY - 2) >= 0 && estadoActual.tablero[estadoActual.posY - 2][estadoActual.posX + 1] != 3)  //Se comprueba que la nueva posicion se encuentre dentro del tablero y que sea una posicion valida
	{
		return 1;  //Retorna 1 indicando que si puede realizar el movimiento
	}

	else
	{
		return 0;  //Retorna 0 indicando que no se puede realizar el movimiento
	}
	
}

//Funcion que comprobará si se puede reslizar izquierdaArriba
int puedoIzquierdaArriba (Estado estadoActual)
{
	if ((estadoActual.posX - 2) >= 0 && (estadoActual.posY - 1) >= 0 && estadoActual.tablero[estadoActual.posY - 1][estadoActual.posX - 2] != 3)  //Se comprueba que la nueva posicion se encuentre dentro del tablero y que sea una posicion valida
	{
		return 1;  //Retorna 1 indicando que si puede realizar el movimiento
	}

	else
	{
		return 0;  //Retorna 0 indicando que no se puede realizar el movimiento
	}
	
}

//Funcion que comprobará si se puede reslizar derechaArriba
int puedoDerechaArriba (Estado estadoActual)
{
	if ((estadoActual.posX + 2) < 5 && (estadoActual.posY - 1) >= 0 && estadoActual.tablero[estadoActual.posY - 1][estadoActual.posX + 2] != 3)  //Se comprueba que la nueva posicion se encuentre dentro del tablero y que sea una posicion valida
	{
		return 1;  //Retorna 1 indicando que si puede realizar el movimiento
	}

	else
	{
		return 0;  //Retorna 0 indicando que no se puede realizar el movimiento
	}
	
}

//Funcion que comprobará si se puede reslizar abajoIzquierda
int puedoAbajoIzquierda (Estado estadoActual)
{
	if ((estadoActual.posX - 1) >= 0 && (estadoActual.posY + 2) < 5 && estadoActual.tablero[estadoActual.posY + 2][estadoActual.posX - 1] != 3)  //Se comprueba que la nueva posicion se encuentre dentro del tablero y que sea una posicion valida
	{
		return 1;  //Retorna 1 indicando que si puede realizar el movimiento
	}

	else
	{
		return 0;  //Retorna 0 indicando que no se puede realizar el movimiento
	}
	
}

//Funcion que comprobará si se puede reslizar abajoDerecha
int puedoAbajoDerecha (Estado estadoActual)
{
	if ((estadoActual.posX + 1) < 5 && (estadoActual.posY + 2) < 5 && estadoActual.tablero[estadoActual.posY + 2][estadoActual.posX + 1] != 3)  //Se comprueba que la nueva posicion se encuentre dentro del tablero y que sea una posicion valida
	{
		return 1;  //Retorna 1 indicando que si puede realizar el movimiento
	}

	else
	{
		return 0;  //Retorna 0 indicando que no se puede realizar el movimiento
	}
	
}

//Funcion que comprobará si se puede reslizar izquierdaAbajo
int puedoIzquierdaAbajo (Estado estadoActual)
{
	if ((estadoActual.posX - 2) >= 0 && (estadoActual.posY + 1) < 5 && estadoActual.tablero[estadoActual.posY + 1][estadoActual.posX - 2] != 3)  //Se comprueba que la nueva posicion se encuentre dentro del tablero y que sea una posicion valida
	{
		return 1;  //Retorna 1 indicando que si puede realizar el movimiento
	}

	else
	{
		return 0;  //Retorna 0 indicando que no se puede realizar el movimiento
	}
	
}

//Funcion que comprobará si se puede reslizar abajoDerecha
int puedoDerechaAbajo (Estado estadoActual)
{
	if ((estadoActual.posX + 2) < 5 && (estadoActual.posY + 1) < 5 && estadoActual.tablero[estadoActual.posY + 1][estadoActual.posX + 2] != 3)  //Se comprueba que la nueva posicion se encuentre dentro del tablero y que sea una posicion valida
	{
		return 1;  //Retorna 1 indicando que si puede realizar el movimiento
	}

	else
	{
		return 0;  //Retorna 0 indicando que no se puede realizar el movimiento
	}
	
}

//***************************************************** MOVIMIENTOS **************************************************************************************

//Funcion que se encargará de mover al caballo dos casillas arriba y una a la izquierda 
Estado arribaIzquierda (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado a mover y el id que tendrá el nuevo estado generado
{
	Estado nuevoEstado;
	//Creamos el tablero del nuevo estado
	nuevoEstado.tablero = (int **)malloc(sizeof(int*)*5);
	for (int i = 0; i < 5; i++)
	{
		nuevoEstado.tablero[i] = (int*)malloc(sizeof(int)*5);
	}
	//Copiamos el tablero del estado anterior
	for (int fila = 0; fila < 5; fila++)
	{
		for (int columna = 0; columna < 5; columna++)
		{
			nuevoEstado.tablero[fila][columna] = estadoActual.tablero[fila][columna];
		}
	}

	nuevoEstado.posX = estadoActual.posX - 1;
	nuevoEstado.posY = estadoActual.posY - 2;
	if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 0)  //Si la nueva posicion está vacia
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //El caballo dejará una marca de que ya pasó por esta casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 1)  //Si es que en la nueva posicion hay un peon
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //Se "come" al peon y se deja la marca de que el caballo ya pasó por esa casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 2)
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 3;  //Si el caballo ya pasó por esa casilla, solo se le permitirá pasar una vez más por ella
	}
	nuevoEstado.id = idNuevoEstado;
	nuevoEstado.idAnterior = estadoActual.id;

	return nuevoEstado;  //Retorna el nuevo estado creado
}

//Funcion que se encargará de mover al caballo dos casillas arriba y una a la derecha 
Estado arribaDerecha (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado a mover y el id que tendrá el nuevo estado generado
{
	Estado nuevoEstado;
	//Creamos el tablero del nuevo estado
	nuevoEstado.tablero = (int **)malloc(sizeof(int*)*5);
	for (int i = 0; i < 5; i++)
	{
		nuevoEstado.tablero[i] = (int*)malloc(sizeof(int)*5);
	}
	//Copiamos el tablero del estado anterior
	for (int fila = 0; fila < 5; fila++)
	{
		for (int columna = 0; columna < 5; columna++)
		{
			nuevoEstado.tablero[fila][columna] = estadoActual.tablero[fila][columna];
		}
	}

	nuevoEstado.posX = estadoActual.posX + 1;
	nuevoEstado.posY = estadoActual.posY - 2;
	if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 0)  //Si la nueva posicion está vacia
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //El caballo dejará una marca de que ya pasó por esta casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 1)  //Si es que en la nueva posicion hay un peon
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //Se "come" al peon y se deja la marca de que el caballo ya pasó por esa casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 2)
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 3;  //Si el caballo ya pasó por esa casilla, solo se le permitirá pasar una vez más por ella
	}
	nuevoEstado.id = idNuevoEstado;
	nuevoEstado.idAnterior = estadoActual.id;

	return nuevoEstado;  //Retorna el nuevo estado creado
}

//Funcion que se encargará de mover al caballo dos casillas a la izquierda y una hacia arriba 
Estado izquierdaArriba (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado a mover y el id que tendrá el nuevo estado generado
{
	Estado nuevoEstado;
	//Creamos el tablero del nuevo estado
	nuevoEstado.tablero = (int **)malloc(sizeof(int*)*5);
	for (int i = 0; i < 5; i++)
	{
		nuevoEstado.tablero[i] = (int*)malloc(sizeof(int)*5);
	}
	//Copiamos el tablero del estado anterior
	for (int fila = 0; fila < 5; fila++)
	{
		for (int columna = 0; columna < 5; columna++)
		{
			nuevoEstado.tablero[fila][columna] = estadoActual.tablero[fila][columna];
		}
	}

	nuevoEstado.posX = estadoActual.posX - 2;
	nuevoEstado.posY = estadoActual.posY - 1;
	if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 0)  //Si la nueva posicion está vacia
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //El caballo dejará una marca de que ya pasó por esta casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 1)  //Si es que en la nueva posicion hay un peon
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //Se "come" al peon y se deja la marca de que el caballo ya pasó por esa casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 2)
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 3;  //Si el caballo ya pasó por esa casilla, solo se le permitirá pasar una vez más por ella
	}
	nuevoEstado.id = idNuevoEstado;
	nuevoEstado.idAnterior = estadoActual.id;

	return nuevoEstado;  //Retorna el nuevo estado creado
}

//Funcion que se encargará de mover al caballo dos casillas a la derecha y una hacia arriba 
Estado derechaArriba (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado a mover y el id que tendrá el nuevo estado generado
{
	Estado nuevoEstado;
	//Creamos el tablero del nuevo estado
	nuevoEstado.tablero = (int **)malloc(sizeof(int*)*5);
	for (int i = 0; i < 5; i++)
	{
		nuevoEstado.tablero[i] = (int*)malloc(sizeof(int)*5);
	}
	//Copiamos el tablero del estado anterior
	for (int fila = 0; fila < 5; fila++)
	{
		for (int columna = 0; columna < 5; columna++)
		{
			nuevoEstado.tablero[fila][columna] = estadoActual.tablero[fila][columna];
		}
	}

	nuevoEstado.posX = estadoActual.posX + 2;
	nuevoEstado.posY = estadoActual.posY - 1;
	if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 0)  //Si la nueva posicion está vacia
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //El caballo dejará una marca de que ya pasó por esta casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 1)  //Si es que en la nueva posicion hay un peon
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //Se "come" al peon y se deja la marca de que el caballo ya pasó por esa casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 2)
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 3;  //Si el caballo ya pasó por esa casilla, solo se le permitirá pasar una vez más por ella
	}
	nuevoEstado.id = idNuevoEstado;
	nuevoEstado.idAnterior = estadoActual.id;

	return nuevoEstado;  //Retorna el nuevo estado creado
}

//Funcion que se encargará de mover al caballo dos casillas abajo y una a la izquierda 
Estado abajoIzquierda (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado a mover y el id que tendrá el nuevo estado generado
{
	Estado nuevoEstado;
	//Creamos el tablero del nuevo estado
	nuevoEstado.tablero = (int **)malloc(sizeof(int*)*5);
	for (int i = 0; i < 5; i++)
	{
		nuevoEstado.tablero[i] = (int*)malloc(sizeof(int)*5);
	}
	//Copiamos el tablero del estado anterior
	for (int fila = 0; fila < 5; fila++)
	{
		for (int columna = 0; columna < 5; columna++)
		{
			nuevoEstado.tablero[fila][columna] = estadoActual.tablero[fila][columna];
		}
	}
	nuevoEstado.posX = estadoActual.posX - 1;
	nuevoEstado.posY = estadoActual.posY + 2;
	if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 0)  //Si la nueva posicion está vacia
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //El caballo dejará una marca de que ya pasó por esta casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 1)  //Si es que en la nueva posicion hay un peon
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //Se "come" al peon y se deja la marca de que el caballo ya pasó por esa casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 2)
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 3;  //Si el caballo ya pasó por esa casilla, solo se le permitirá pasar una vez más por ella
	}
	nuevoEstado.id = idNuevoEstado;
	nuevoEstado.idAnterior = estadoActual.id;
	return nuevoEstado;  //Retorna el nuevo estado creado
}

//Funcion que se encargará de mover al caballo dos casillas abajo y una hacia la derecha 
Estado abajoDerecha (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado a mover y el id que tendrá el nuevo estado generado
{
	Estado nuevoEstado;
	//Creamos el tablero del nuevo estado
	nuevoEstado.tablero = (int **)malloc(sizeof(int*)*5);
	for (int i = 0; i < 5; i++)
	{
		nuevoEstado.tablero[i] = (int*)malloc(sizeof(int)*5);
	}
	//Copiamos el tablero del estado anterior
	for (int fila = 0; fila < 5; fila++)
	{
		for (int columna = 0; columna < 5; columna++)
		{
			nuevoEstado.tablero[fila][columna] = estadoActual.tablero[fila][columna];
		}
	}

	nuevoEstado.posX = estadoActual.posX + 1;
	nuevoEstado.posY = estadoActual.posY + 2;
	if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 0)  //Si la nueva posicion está vacia
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //El caballo dejará una marca de que ya pasó por esta casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 1)  //Si es que en la nueva posicion hay un peon
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //Se "come" al peon y se deja la marca de que el caballo ya pasó por esa casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 2)
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 3;  //Si el caballo ya pasó por esa casilla, solo se le permitirá pasar una vez más por ella
	}
	nuevoEstado.id = idNuevoEstado;
	nuevoEstado.idAnterior = estadoActual.id;

	return nuevoEstado;  //Retorna el nuevo estado creado
}

//Funcion que se encargará de mover al caballo dos casillas a la izquierda y una hacia abajo 
Estado izquierdaAbajo (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado a mover y el id que tendrá el nuevo estado generado
{
	Estado nuevoEstado;
	//Creamos el tablero del nuevo estado
	nuevoEstado.tablero = (int **)malloc(sizeof(int*)*5);
	for (int i = 0; i < 5; i++)
	{
		nuevoEstado.tablero[i] = (int*)malloc(sizeof(int)*5);
	}
	//Copiamos el tablero del estado anterior
	for (int fila = 0; fila < 5; fila++)
	{
		for (int columna = 0; columna < 5; columna++)
		{
			nuevoEstado.tablero[fila][columna] = estadoActual.tablero[fila][columna];
		}
	}

	nuevoEstado.posX = estadoActual.posX - 2;
	nuevoEstado.posY = estadoActual.posY + 1;
	if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 0)  //Si la nueva posicion está vacia
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //El caballo dejará una marca de que ya pasó por esta casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 1)  //Si es que en la nueva posicion hay un peon
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //Se "come" al peon y se deja la marca de que el caballo ya pasó por esa casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 2)
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 3;  //Si el caballo ya pasó por esa casilla, solo se le permitirá pasar una vez más por ella
	}
	nuevoEstado.id = idNuevoEstado;
	nuevoEstado.idAnterior = estadoActual.id;

	return nuevoEstado;  //Retorna el nuevo estado creado
}

//Funcion que se encargará de mover al caballo dos casillas a la derecha y una hacia abajo
Estado derechaAbajo (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado a mover y el id que tendrá el nuevo estado generado
{
	Estado nuevoEstado;
	//Creamos el tablero del nuevo estado
	nuevoEstado.tablero = (int **)malloc(sizeof(int*)*5);
	for (int i = 0; i < 5; i++)
	{
		nuevoEstado.tablero[i] = (int*)malloc(sizeof(int)*5);
	}
	//Copiamos el tablero del estado anterior
	for (int fila = 0; fila < 5; fila++)
	{
		for (int columna = 0; columna < 5; columna++)
		{
			nuevoEstado.tablero[fila][columna] = estadoActual.tablero[fila][columna];
		}
	}

	nuevoEstado.posX = estadoActual.posX + 2;
	nuevoEstado.posY = estadoActual.posY + 1;
	if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 0)  //Si la nueva posicion está vacia
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //El caballo dejará una marca de que ya pasó por esta casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 1)  //Si es que en la nueva posicion hay un peon
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 2;  //Se "come" al peon y se deja la marca de que el caballo ya pasó por esa casilla
	}

	else if (nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] == 2)
	{
		nuevoEstado.tablero[nuevoEstado.posY][nuevoEstado.posX] = 3;  //Si el caballo ya pasó por esa casilla, solo se le permitirá pasar una vez más por ella
	}
	nuevoEstado.id = idNuevoEstado;
	nuevoEstado.idAnterior = estadoActual.id;

	return nuevoEstado;  //Retorna el nuevo estado creado
}

//Funcion que ejecuta la busqueda de la solucion
int Bee (char ** mapa, int colCaballo, int filaCaballo)  //Recibe como argumentos la matriz de caracteres (tablero leido) y la posicion en X e Y del caballo
{
	int idNuevoEstado = 1;

	int cantidadAbiertos = 0;
	Estado * abiertos = (Estado *)malloc(sizeof(Estado)*cantidadAbiertos);  //Creamos la lista para almacenar los estados abiertos
	int cantidadCerrados = 0;
	Estado * cerrados = (Estado *)malloc(sizeof(Estado)*cantidadCerrados);  //Creamos la lista para alamacenar los estados cerrados
	int cantidadSoluciones = 0;
	Estado * soluciones = (Estado *)malloc(sizeof(Estado)*cantidadSoluciones);  //Creamos una lista para almacenar los estado finales
	
	Estado estadoInicial = tableroInicial(mapa, colCaballo, filaCaballo);
	if (peonesRestantes(estadoInicial) == 0)  //En caso de que el tablero inicial no tenga ningún peon
	{
		return 2;  //Sale de la funcion y retorna 2 para mostrar el error correspondiente 
	}
	abiertos = agregarEstado(abiertos, &cantidadAbiertos, estadoInicial);  //Agreagamos el estado incial a la lista de estados abiertos

	while (cantidadAbiertos != 0)
	{
		Estado estadoActual = extraerEstado(abiertos, &cantidadAbiertos);  //Extraemos el primer estado de la lista de estados abiertos
		cerrados = agregarEstado(cerrados, &cantidadCerrados, estadoActual);  //Agregamos el estado actual a la lista de estados cerrados

		//*************************************** COMENZAMOS A REALIZAR LOS MOVIMIENTOS ******************************************
		if (puedoArribaIzquierda(estadoActual))
		{
			Estado nuevoEstado = arribaIzquierda(estadoActual, idNuevoEstado);

			if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
			{
				idNuevoEstado = idNuevoEstado + 1;
				
				if (peonesRestantes(nuevoEstado) == 0)
				{
					imprimirSolucion(cerrados, cantidadCerrados, nuevoEstado);
					free(abiertos);
					free(cerrados);
					return 0;
				}

				else
				{
					abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
				}
			}
		}
		if (puedoArribaDerecha(estadoActual))
		{
			Estado nuevoEstado = arribaDerecha(estadoActual, idNuevoEstado);
			if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
			{
				idNuevoEstado = idNuevoEstado + 1;
				
				if (peonesRestantes(nuevoEstado) == 0)
				{
					imprimirSolucion(cerrados, cantidadCerrados, nuevoEstado);
					free(abiertos);
					free(cerrados);
					return 0;
				}

				else
				{
					abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
				}	
			}
		}

		if (puedoIzquierdaArriba(estadoActual))
		{
			Estado nuevoEstado = izquierdaArriba(estadoActual, idNuevoEstado);
			if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
			{
				idNuevoEstado = idNuevoEstado + 1;
				
				if (peonesRestantes(nuevoEstado) == 0)
				{
					imprimirSolucion(cerrados, cantidadCerrados, nuevoEstado);
					free(abiertos);
					free(cerrados);
					return 0;
				}

				else
				{
					abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
				}
			}
		}

		if (puedoDerechaArriba(estadoActual))
		{
			Estado nuevoEstado = derechaArriba(estadoActual, idNuevoEstado);
			if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
			{
				idNuevoEstado = idNuevoEstado + 1;
				
				if (peonesRestantes(nuevoEstado) == 0)
				{
					imprimirSolucion(cerrados, cantidadCerrados, nuevoEstado);
					free(abiertos);
					free(cerrados);
					return 0;
				}

				else
				{
					abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
				}
			}
		}

		if (puedoAbajoIzquierda(estadoActual))
		{
			Estado nuevoEstado = abajoIzquierda(estadoActual, idNuevoEstado);
			
			if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
			{
				idNuevoEstado = idNuevoEstado + 1;
				
				if (peonesRestantes(nuevoEstado) == 0)
				{
					imprimirSolucion(cerrados, cantidadCerrados, nuevoEstado);
					free(abiertos);
					free(cerrados);
					return 0;
				}

				else
				{
					abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
				}
			}
		}

		if (puedoAbajoDerecha(estadoActual))
		{
			Estado nuevoEstado = abajoDerecha(estadoActual, idNuevoEstado);
			if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
			{
				idNuevoEstado = idNuevoEstado + 1;
				
				if (peonesRestantes(nuevoEstado) == 0)
				{
					imprimirSolucion(cerrados, cantidadCerrados, nuevoEstado);
					free(abiertos);
					free(cerrados);
					return 0;
				}

				else
				{
					abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
				}
			}
		}

		if (puedoIzquierdaAbajo(estadoActual))
		{
			Estado nuevoEstado = izquierdaAbajo(estadoActual, idNuevoEstado);
			if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
			{
				idNuevoEstado = idNuevoEstado + 1;
				
				if (peonesRestantes(nuevoEstado) == 0)
				{
					imprimirSolucion(cerrados, cantidadCerrados, nuevoEstado);
					free(abiertos);
					free(cerrados);
					return 0;
				}

				else
				{
					abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
				}
			}
		}

		if (puedoDerechaAbajo(estadoActual))
		{
			Estado nuevoEstado = derechaAbajo(estadoActual, idNuevoEstado);
			if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
			{
				idNuevoEstado = idNuevoEstado + 1;
				
				if (peonesRestantes(nuevoEstado) == 0)
				{
					imprimirSolucion(cerrados, cantidadCerrados, nuevoEstado);
					free(abiertos);
					free(cerrados);
					return 0;
				}

				else
				{
					abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
				}
			}
		}
	}
	return 1;  //Si sale del while, significa que termino la busqueda y no encontro una solucion 
}

int main(){
	int filaCaballo,colCaballo;
	
	int catArchivos = 4; //Cantidad de archivos a procesar (Inicia en "Tablero1.txt" luego "Tablero2.txt", "Tablero3.txt", etc. )
	
	int variableGenericaBonita;
	for(variableGenericaBonita=1;variableGenericaBonita<=catArchivos;variableGenericaBonita++){
		
		char numeroStr[1];
		sprintf(numeroStr, "%d", variableGenericaBonita);
		
		char nombre[12];
		strcpy(nombre, "Tablero");
		strcat(nombre, numeroStr);
		strcat(nombre, ".txt");
		printf("\n\n*****************************************\n\n");
		printf("%s\n", nombre);
				
		char ** mapa = leer (nombre,&filaCaballo,&colCaballo);
		mostrar(mapa,filaCaballo,colCaballo);
		printf("\nRespuesta alumno:\n");
		/*********************************************************************/
		/********************* LLAME A SU FUNCIÓN AQUÍ **********************/
		/*********** muestre también su resultado en esta sección ***********/
		/****************** No modifique el resto del main ******************/
		int resultado = Bee(mapa, colCaballo, filaCaballo);

		if (resultado == 1)
		{
			printf("No se encontro una solucion\n");
		}

		else if (resultado == 2)
		{
			printf("No hay peones en el tablero ingresado\n");
		}
		
		/*********************************************************************/
		/*********************************************************************/
		/*********************************************************************/
		/*********************************************************************/
		liberar(mapa);
	}

	return 0;
}