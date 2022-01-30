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
			nuevaLista[i][j] = (int *)malloc(sizeof(int)*3);  //Se crean 3 columnas en cada fila de los elementode de la nueva lista
		}
	}

    //Se copian las soluciones existentes, excepto aquel que se desea eliminar
	int indiceNuevaLista = 0;  //Esta variable nos sirve para saber el indice de posicion en la nueva lista
	int indiceAntiguaLista = 0;  //Este variable nos sirve para saber el indice de posicion en la antigua lista

	while(indiceAntiguaLista < *cantSoluciones)
    {
		if(indiceEliminar != indiceAntiguaLista)  //Comprobamos que la solucion a copiar no sea la solucion a eliminar
        {
			for(int fila = 0; fila < 3; fila ++)
            {
				for (int columna = 0; columna < 3; ++columna)
                {
					nuevaLista[indiceNuevaLista][fila][columna] = listaSoluciones[indiceAntiguaLista][fila][columna];
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

//Esta funcion se encarga de imprimir un cuadrado en especifico, será utilizado para imprimir los cuadrados de la lista de soluciones
void imprimirCuadrado (int ** cuadrado)  //Recibe como argumento un cuadrado (matriz) a imprimir
{
    for (int i = 0; i < 3; ++i)  //Ciclo para recorrer las filas del cuadrado
    {
		for (int j = 0; j < 3; ++j)  //Ciclo para recorrer las columnas del cuadrado
        {
			printf("%d ", cuadrado[i][j]);
		}
		printf("\n");
	}
	return;
}

//Funcion que se encargará de imprimir cada cuadrado dentro de la lista de soluciones 
void imprimirSoluciones (int *** listaSoluciones, int cantSoluciones)  //Recibe como argumentos la lista de soluciones (lista de matrices) y la cantidad de elementos que posee
{
    for(int indiceSolucion = 0; indiceSolucion < cantSoluciones; indiceSolucion ++)
    {
		printf("Solucion %d\n", indiceSolucion+1);
        imprimirCuadrado(listaSoluciones[indiceSolucion]);
        printf("\n");

        printf("Suma: %d\n", (listaSoluciones[indiceSolucion][0][0] + listaSoluciones[indiceSolucion][0][1] + listaSoluciones[indiceSolucion][0][2]));
        printf("\n");
    }

	return;
}


//Funcion que comprobará que la suma de cada elemento de una fila del cuadrado sea igual en todas las filas
int verificarFilas (int a, int b, int c, int d, int e, int f, int g, int h, int i)  //Recibe como argumentos los 9 elementos de un cuadrado (Fila 0: a,b,c; Fila 1: d,e,f; Fila 2: g,h,i)
{
    if ((a+b+c) == (d+e+f) && (a+b+c) == (g+h+i))  //Comprueba la suma de los elementos de las filas sea igual
    {
        return 1;  //Retorna 1, indicando que si cumple la condicion de la suma de elementos en las filas
    }

    else
    {
        return 0;  //Retorna 0, indicando que no cumple la condicion
    }
}

//Funcion que comprobará que la suma de cada elemento de una columna del cuadrado sea igual en todas las columnas
int verificarColumnas (int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
    if ((a+d+g) == (b+e+h) && (a+d+g) == (c+f+i) && (a+d+g) == (a+b+c))  //Comprueba la suma de los elementos de las columnas sea igual
    {
        return 1;  //Retorna 1, indicando que si cumple la condicion de la suma de elementos en las columnas
    }

    else
    {
        return 0;  //Retorna 0, indicando que no cumple la condicion
    }
}

//Función que comprobará que la suma de los elementos de las verticales del cuadrado sea la misma 
int verificarDiagonales (int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
    if ((a+e+i) == (c+e+g) && (a+e+i) == (a+b+c))  //Comprueba la suma de los elementos de las diagonales sea igual
    {
        return 1;  //Retorna 1, indicando que si cumple la condicion de la suma de elementos en las columnas
    }

    else
    {
        return 0;  //Retorna 0, indicando que no cumple la condicion
    }
}

//Esta funcion se encargará de verificar de que las soluciones finales no sean una version traspuesta de otra solución
//Recibe como argumentos un cuadrado (matriz) a revisar, una lista de soluciones (lista de matrices), la cantidad de elementos que tiene esta lista y el indice que tiene la matriz a revisar dentro de la lista
int verificarTraspuesta (int **cuadrado, int *** listaSoluciones, int cantSoluciones, int indiceSolucion)
{
    //********************************** Creamos un arreglo con los numero del cuadrado a revisar **************************************
    int* cuadradoActual = (int *)malloc(sizeof(int*)*9);
    int indiceArreglo = 0;  //Indice para recorrer el arreglo
    for (int i = 0; i < 3; i++)  //Indice para recorrer las filas del cuadrado
    {
        for (int j = 0; j < 3; j++)  //Indice para recorrer las columanas del cuadrado
        {
            cuadradoActual[indiceArreglo] = cuadrado[i][j];  //Se copian los elementos del cuadrado dentro del arreglo
            indiceArreglo++;  //Se hace avanzar el indice para el arreglo
        }
    }
    //Ordenamos de menor a mayor el arreglo para hacer más facil la comparación
    for (int i = 0; i < 9; i++)  //Indice para el pivote del arreglo
    {
        for (int j = i+1; j < 9; j++)  //Ciclo para comparar el pivote con el resto del arreglo
        {
           if (cuadradoActual[i] < cuadradoActual[j])  //Si el elemento a comparar es menor al pivote, cambiaran sus posiciones
           {
               int aux = cuadradoActual[i];
               cuadradoActual[i] = cuadradoActual[j];
               cuadradoActual[j] = aux;
           } 
        }
    }

    //Comprobación de solución trivial
    if (cuadradoActual[0] == cuadradoActual[8])  //Si el primer y el ultimo elemento del arreglo son iguales, significa que los elementos entre ellos también lo son
    {
        free(cuadradoActual);  //Se libera la memoria utilizada por el arreglo
        return 0;  //Retorna 0, indicando que hay una solución con los mismos elementos que él
    }

    //******************************************** Comparación *****************************************************************
    int* comparar = (int *)malloc(sizeof(int*)*9);  //Arreglo para almacenar los elementos de la solución con la que se comparará la solución entregada
    int iguales;  //Variable para almacenar la cantidad de elementos iguales que tiene las matrices 

    for (int k = 0; k < cantSoluciones; k++)  //Ciclo para recorrer todos los elementos de la lista de soluciones
    {
        if (k != indiceSolucion)  //Si k y el indiceSolucion son iguales, significa que se esta intentando comparar una solución con ella misma, por eso solamente se compararán cuando no sean iguales
        {
            int indiceComparar = 0;  //Indice para recorrer las posiciones del arreglo a comparar
            iguales = 0;  //Se establece en 0 la cantidad de elementos iguales al inicio de cada ciclo

            for (int i = 0; i < 3; i++)  //Cilco para recorrer las filas de la solución
            {
                for (int j = 0; j < 3; j++)  //Ciclo para recorres las columnas de la solución
                {
                    comparar[indiceComparar] = listaSoluciones[k][i][j];  //Se copian los elementos de la solución en el nuevo arreglo
                    indiceComparar++;  //Se hace avanzar el indice del arreglo
                }
            }

            //Ordenamos de menor a mayor el arreglo para hacer más facil la comparación
            for (int i = 0; i < 9; i++)  //Ciclo para el pivote del arreglo
            {
                for (int j = i+1; j < 9; j++)  //Ciclo para comparar al pivote con el resto del arreglo
                {
                    if (comparar[i] < comparar[j])  //Si el elemento a comparar es menor al pivote, se intercambiaran sus posiciones
                    {
                    int aux = comparar[i];
                    comparar[i] = comparar[j];
                    comparar[j] = aux;
                    } 
                }
            }

            for (int i = 0; i < 9; i++)  //Ciclo para comparar los elementos en la misma posición de los arreglos que contienen los elemntos de las soluciones 
            {
                if (cuadradoActual[i] == comparar[i])  //Si ambos elementos son iguales, se sumará 1 a la cantidad de elementos iguales
                {
                    iguales++;
                }
            }
            
            if (iguales == 9)  //Si la variable "iguales" es igual a 9, significa que todos los elementos de amabas soluciones son iguales, por lo que se sale de la funcion indicando falso
            {
                free(cuadradoActual);  //Se libera la memoria utilizada por el arreglo
                free(comparar);  //Se libera la memoria utilizada por el arreglo
                return 0;  //Retorna 0, indicando que hay una solución con los mismos elementos que él
            }
        }
    }
    //Si sale del for significa que comparó la solución entregada con todas las otras soluciones y no hay una que sea la traspuesta de este 
    free(cuadradoActual);  //Se libera la memoria utilizada por el arreglo
    free(comparar);  //Se libera la memoria utilizada por el arreglo
    return 1;  //Retorna 1, indicando que no hay una solución con los mismos elementos que él
}

int main ()
{
    int cantidadSoluciones = 0;  //Variable para almacenar la cantidad de soluciones al problema
    int *** listaSoluciones = (int ***)malloc(sizeof(int**)*cantidadSoluciones);  //Se crea la lista de soluciones y se asigna la memoria para ella

    int valorMaximo;  //Variable para almacenar el valor maximo que podrán tener los elementos del cuadrado
    printf("Ingrese el numero maximo que pueden tener los elementos del cuadrado: ");
    scanf("%d", &valorMaximo);
    printf("\n");

    //Generacion de todos las posibles soluciones 
    for (int a = 1; a <= valorMaximo; a++)  //Ciclo para cambiar el valor de la posición (0,0)
    {
        for (int b = 1; b <= valorMaximo; b++)  //Ciclo para cambiar el valor de la posición (0,1)
        {
            for (int c = 1; c <= valorMaximo; c++)  //Ciclo para cambiar el valor de la posición (0,2)
            {
                for (int d = 1; d <= valorMaximo; d++)  //Ciclo para cambiar el valor de la posición (1,0)
                {
                    for (int e = 1; e <= valorMaximo; e++)  //Ciclo para cambiar el valor de la posición (1,1)
                    {
                        for (int f = 1; f <= valorMaximo; f++)  //Ciclo para cambiar el valor de la posición (1,2)
                        {
                            for (int g = 1; g <= valorMaximo; g++)  //Ciclo para cambiar el valor de la posición (2,0)
                            {
                                for (int h = 1; h <= valorMaximo; h++)  //Ciclo para cambiar el valor de la posición (2,1)
                                {
                                    for (int i = 1; i <= valorMaximo; i++)  //Ciclo para cambiar el valor de la posición (2,2)
                                    {
                                        //Verificamos que con los "indices" que tenemos podemos formar un cuadrado magico antes de crear su representacion, de esta manera no utilizamos tanta memoria
                                        if (verificarColumnas(a, b, c, d, e, f, g, h, i) && verificarFilas(a, b, c, d, e, f, g, h, i) && verificarDiagonales (a, b, c, d, e, f, g, h, i))
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
    }

    //Verificación de la condición de trasposicion
    for (int i = 0; i < cantidadSoluciones; i++)
    {
        if (verificarTraspuesta(listaSoluciones[i], listaSoluciones, cantidadSoluciones, i) == 0)  //Si es que no cumple la condicion de la trasposición (0), se eliminará esta solucion de la lista de soluciones
        {
            listaSoluciones = eliminarSolucion(listaSoluciones, &cantidadSoluciones, i);  //Se crea una nueva lista de soluciones sin la solucion que no cumple la condicion
            i--;  //Se disminuye i para recorrer correctamente la nueva lista de soluciones con una nueva cantidad de soluciones
        }
    }
    //**************************************** Mostrar soluciones finales ****************************************
    if (cantidadSoluciones == 0)
    {
        printf("No existen soluciones");
        free(listaSoluciones);  //Se libera la memoria utilizada por la lista de soluciones
        return 0;  //Se sale de la función retornando cero
    }
    
    else
    {
        imprimirSoluciones(listaSoluciones, cantidadSoluciones);  //Se imprimen las soluciones restantes luego de filtrarlas
        free(listaSoluciones);  //Se libera la memoria utilizada por la lista de soluciones
        return 0;  //Se sale de la función retornando cero
    } 
}