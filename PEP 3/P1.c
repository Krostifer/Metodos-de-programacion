#include <stdio.h>
#include <stdlib.h>

//Esta función se encarga de crear un cuadrado (matríz 3x3) con 9 elementos en él
int ** crearCuadrado (int a, int b, int c, int d, int e, int f, int g, int h, int i)  //Recibe como argumento 9 enteros que serán los números al interior del cuadrado
{
    int ** cuadrado = (int **)malloc(sizeof(int*)*3);  //Se reserva memoria para un cuadrado de 3 filas

	for (int j = 0; j < 3; ++j)
    {
		cuadrado[j] = (int *)malloc(sizeof(int)*3);  //Se reserva memoria para que cada fila posea 3 valores	
	}

    //Se asignan los valores en sus respectivas posiciones
    cuadrado[0][0] = a;
    cuadrado[0][1] = b;
    cuadrado[0][2] = c;

    cuadrado[1][0] = d;
    cuadrado[1][1] = e;
    cuadrado[1][2] = f;

    cuadrado[2][0] = g;
    cuadrado[2][1] = h;
    cuadrado[2][2] = i;

    return cuadrado;
}

//Esta función se encargar de agregar un elemento (Solucion o cuadrado) a una lista 
int *** agregarSolucion (int *** lista, int *largoLista, int ** solucion)  //Recibe como argumentos una lista de matrices, la cantidad de elementos que posee esta lista y una matriz a agregar
{
    //Se crea una nueva lista para almacenar las soluciones
    int *** nuevaLista = (int ***)malloc(sizeof(int**)*(*largoLista+1));
    //Se crean las matrices dentro de cada elemento de la lista
    for (int i = 0; i < *largoLista + 1; ++i)
    {
		nuevaLista[i] = (int **)malloc(sizeof(int *)*3);  //Se crean las 3 filas para la matriz
		for (int j = 0; j < 3; ++j)
        {
			nuevaLista[i][j] = (int *)malloc(sizeof(int)*3);  //Se crean las 3 columnas para la matriz 
		}
	}

    //Se copian las soluciones existentes
	for (int indiceSolucion = 0; indiceSolucion < *largoLista; indiceSolucion++)
    {
		for(int fila = 0; fila < 3; fila++)  //Ciclo para recorrer las filas 
        {
			for (int columna = 0; columna < 3; columna++)  //Ciclo para recorrer las columnas
            {
				nuevaLista[indiceSolucion][fila][columna] = lista[indiceSolucion][fila][columna];  //Se copian los elementos de la lista antigua a la nueva lista
			}
		}
	}

    //Se agrega la nueva solución a la nueva lista
	for (int filaSolucion = 0; filaSolucion < 3; filaSolucion++)  //Ciclo para recorrer las filas 
    {
		for (int columnaSolucion = 0; columnaSolucion < 3; columnaSolucion++)  //Ciclo para recorrer las columnas
        {
			nuevaLista[*largoLista][filaSolucion][columnaSolucion] = solucion[filaSolucion][columnaSolucion];  //Se copian los elementos de la solucion a agregar al ultimo elemento de la nueva lista
		}
	}

    *largoLista = *largoLista + 1;//Se actualiza el nuevo largo de la lista de soluciones
    free(lista);  //Se libera el espacio ocupado por la antigua lista de soluciones 

    return nuevaLista;  //Retorna la nueva lista de soluciones creada
}

//Esta funcion se encarga de eliminar una solucion de la lista de soluciones y retornar una lista nueva sin dicha solucion
int *** eliminarSolucion(int *** listaSoluciones, int * cantSoluciones, int indiceEliminar)  //Recibe como argumentos una lista de soluciones (lista de matrices), la cantidad de elementos que posee esta lista y el indice del elemento a eliminar
{
    //Se crea una nueva lista para almacenar las soluciones restantes
    int *** nuevaLista = (int ***)malloc(sizeof(int**)*(*cantSoluciones - 1));
    for (int i = 0; i < *cantSoluciones - 1; ++i)  //Ciclo para recorrer los elementos de la nueva lista de soluciones
    {
		nuevaLista[i] = (int **)malloc(sizeof(int *)*3);  //Se crean 3 filas en cada elemento de la nueva lista

		for (int j = 0; j < 3; ++j)  //Ciclo para recorrer las filas de cada elemento de la nueva lista
        {
			nuevaLista[i][j] = (int *)malloc(sizeof(int)*3);  //Se crean una columna en cada fila de los elementos de de la nueva lista
		}
	}

    //Se copian las soluciones existentes, excepto aquella que se desea eliminar
	int indiceNuevaLista = 0;  //Esta variable nos sirve para saber el indice de posicion en la nueva lista
	int indiceAntiguaLista = 0;  //Este variable nos sirve para saber el indice de posicion en la antigua lista

	while(indiceAntiguaLista < *cantSoluciones)  //Ciclo para recorrer toda la lista de soluciones
    {
		if(indiceEliminar != indiceAntiguaLista)  //Comprobamos que la solucion a copiar no sea la solucion a eliminar
        {
			for(int fila = 0; fila < 3; fila ++)  //Ciclo para recorrer las filas
            {
				for (int columna = 0; columna < 3; ++columna)  //Ciclo para recorrer las columnas
                {
					nuevaLista[indiceNuevaLista][fila][columna] = listaSoluciones[indiceAntiguaLista][fila][columna];  //Se copian los elementos de la lisya antigua a la nueva
				}
			}

			indiceNuevaLista++;  //Si se agrega una solucion, se aumenta el valor del indice de la nueva lista
		}
		
        //En caso de que no se entre al if, significa que la solucion actual es la que se desea eliminar, por lo que no se copiará y solamanete se incrementará el indice de la antigua lista para copiar el siguiente elemento
		indiceAntiguaLista++;  //Se incrementa el indice de la antigua lista para copiar el siguiente elemento
	}

    *cantSoluciones = *cantSoluciones - 1;  //Se actualiza la nueva cantidad de soluciones que existen
    free(listaSoluciones);  //Se libera la memoria utilizada por la antigua lista de soluciones

    return nuevaLista;  //Se retorna la nueva lista de soluciones
}

//Funcion que verifica si es que cumple la condicion de tener la cantidad de casillas negras en sus filas
int verificarFilas (int** solucion, int * tripleta )  //Recibe como argumentos una solucion (matriz) y la tripleta (arreglo) que contiene la cantidad de casillas negras en cada fila
{
    if (solucion[0][0] + solucion[0][1] + solucion[0][2] == tripleta[0] && solucion[1][0] + solucion[1][1] + solucion[1][2] == tripleta[1] && solucion[2][0] + solucion[2][1] + solucion[2][2] == tripleta[2]) 
    {
        return 1;  //Retorna 1, indicando que cumple tiene la misma cantidad de casillas negras en sus filas que la tripleta  
    }

    else
    {
        return 0;  //Retorna 0, indicando que no cumple con la condicion de la cantidad de casillas negras en sus filas
    }
}

//Funcion que verifica si es que cumple la condicion de tener la cantidad de casillas negras en sus columnas
int verificarColumnas (int** solucion, int * tripleta )  //Recibe como argumentos una solucion (matriz) y la tripleta (arreglo) que contiene la cantidad de casillas negras en cada columnas
{
    if (solucion[0][0] + solucion[1][0] + solucion[2][0] == tripleta[0] && solucion[0][1] + solucion[1][1] + solucion[2][1] == tripleta[1] && solucion[0][2] + solucion[1][2] + solucion[2][2] == tripleta[2]) 
    {
        return 1;  //Retorna 1, indicando que cumple tiene la misma cantidad de casillas negras en sus columnas que la tripleta  
    }

    else
    {
        return 0;  //Retorna 0, indicando que no cumple con la condicion de la cantidad de casillas negras en sus columnas
    }
}

int main()
{
    int cantidadSoluciones = 0;  //Variable para almacenar la cantidad de soluciones al problema
    int *** listaSoluciones = (int ***)malloc(sizeof(int**)*cantidadSoluciones);  //Se crea la lista de soluciones y se asigna la memoria para ella

    int* tripletaF = (int *)malloc(sizeof(int)*3);  //Se crea un arreglo de 3 elementos (enteros) para almacenar las primera tripleta (filas)
    int* tripletaC = (int *)malloc(sizeof(int)*3);  //Se crea un arreglo de 3 elementos (enteros) para almacenar las primera tripleta (columnas)

    //Ingreso de tripletas por parte del usuario
    printf("Ingrese la primera tripleta separando sus elementos con una coma (,): ");
    scanf("%d,%d,%d", &tripletaF[0], &tripletaF[1], &tripletaF[2]);
    printf("\n");

    printf("Ingrese la segunda tripleta separando sus elementos con una coma (,): ");
    scanf("%d,%d,%d", &tripletaC[0], &tripletaC[1], &tripletaC[2]);
    printf("\n");

    //Generacion de todos las posibles soluciones 
    for (int a = 0; a <= 1; a++)  //Ciclo para cambiar el valor de la posición (0,0)
    {
        for (int b = 0; b <= 1; b++)  //Ciclo para cambiar el valor de la posición (0,1)
        {
            for (int c = 0; c <= 1; c++)  //Ciclo para cambiar el valor de la posición (0,2)
            {
                for (int d = 0; d <= 1; d++)  //Ciclo para cambiar el valor de la posición (1,0)
                {
                    for (int e = 0; e <= 1; e++)  //Ciclo para cambiar el valor de la posición (1,1)
                    {
                        for (int f = 0; f <= 1; f++)  //Ciclo para cambiar el valor de la posición (1,2)
                        {
                            for (int g = 0; g <= 1; g++)  //Ciclo para cambiar el valor de la posición (2,0)
                            {
                                for (int h = 0; h <= 1; h++)  //Ciclo para cambiar el valor de la posición (2,1)
                                {
                                    for (int i = 0; i <= 1; i++)  //Ciclo para cambiar el valor de la posición (2,2)
                                    {
                                        int ** cuadrado = crearCuadrado(a, b, c, d, e, f, g, h, i);  //Se crea un cuadrado con los 9 valores actuales
                                        listaSoluciones = agregarSolucion(listaSoluciones, &cantidadSoluciones, cuadrado);  //Se agrega el cuadrado creado a la lista de soluciones
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //************************************* VERIFICAMOS LAS SOLUCIONES *********************************************
    //Verificamos las filas con la primera tripleta
    for (int i = 0; i < cantidadSoluciones; i++)  //Ciclo para recorrer todas las posibles soluciones
    {
        if (verificarFilas(listaSoluciones[i], tripletaF) == 0)  //Si retorna 0, significa que no cumple con la cantidad de casillas negras en sus filas, por lo que se eliminara
        {
            listaSoluciones = eliminarSolucion(listaSoluciones, &cantidadSoluciones, i);  //Se crea una nueva lista de soluciones sin la solucion que no cumple la condicion
            i--;  //Se disminuye i para recorrer correctamente la nueva lista de soluciones con una nueva cantidad de soluciones
        }
    }
   
    //Verificamos las columnas con la segunda tripleta
    for (int i = 0; i < cantidadSoluciones; i++)  //Ciclo para recorrer todas las posibles soluciones
    {
        if (verificarColumnas(listaSoluciones[i], tripletaC) == 0)  //Si retorna 0, significa que no cumple con la cantidad de casillas negras en sus columnas, por lo que se eliminara
        {
            listaSoluciones = eliminarSolucion(listaSoluciones, &cantidadSoluciones, i);  //Se crea una nueva lista de soluciones sin la solucion que no cumple la condicion
            i--;  //Se disminuye i para recorrer correctamente la nueva lista de soluciones con una nueva cantidad de soluciones
        }
    }

    //Salida
    if (cantidadSoluciones == 0)  //En caso de que las tripletas ingresadas no se puedan representar
    {
        free(listaSoluciones);  //Se libera la memoria utilizada por las lista de soluciones
        printf("Las tripletas entregadas no se pueden representar");
        return 0;
    }

    else if (cantidadSoluciones == 1)  //En caso de que solo exista una representacion de las tripletas entregadas
    {
        free(listaSoluciones);  //Se libera la memoria utilizada por las lista de soluciones
        printf("Solo existe una representacion para las tripletas entregadas");
        return 0;
    }

    else  //En caso de que las tripletas de puedan representar de más de una manera
    {
        free(listaSoluciones);  //Se libera la memoria utilizada por las lista de soluciones
        printf("Existe mas de una representacion para las tripletas entregadas");
        return 0;
    }
}