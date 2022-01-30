#include <stdio.h>
#include <stdlib.h>

//Definimos con constantes la cantidad de monedas y sus valores
//Valor monedas 
#define V1 500
#define V2 100
#define V3 50
#define V4 10
#define V_TOTAL 20000

//Cantidad de monedas
#define C1 10     
#define C2 50     
#define C3 100     
#define C4 500    
#define C_TOTAL 660


//Funcion encargada de crear una solucion
//Recibe como argumentos los 12 valores que compondrán la solución (matriz) y representan la cantidad de monedas que tiene cada nieto
int ** crearSolucion (int m1X, int m2X, int m3X, int m4X, int m1Y, int m2Y, int m3Y, int m4Y, int m1Z, int m2Z, int m3Z, int m4Z)
{
    //Se crea la matriz para almacenar la solucion
    int ** solucion = (int **)malloc(sizeof(int*)*3);  //Se reserva memoria para una solucion de 3 filas

	for (int j = 0; j < 3; ++j)
    {
		solucion[j] = (int *)malloc(sizeof(int)*4);  //Se reserva memoria para que cada fila posea 4 valores	
	}

    //Asignamos los valores en sus correspondientes posiciones
    //Nieto menor
    solucion[0][0] = m1X;
    solucion[0][1] = m2X;
    solucion[0][2] = m3X;
    solucion[0][3] = m4X;
    //Nieto del medio
    solucion[1][0] = m1Y;
    solucion[1][1] = m2Y;
    solucion[1][2] = m3Y;
    solucion[1][3] = m4Y;
    //Nieto mayor
    solucion[2][0] = m1Z;
    solucion[2][1] = m2Z;
    solucion[2][2] = m3Z;
    solucion[2][3] = m4Z;

    return solucion;  //Retorna la solucion creada
}

//Funcion que se encarga de liberar la memoria utilizada por una lista de matrices (matriz 3x4 en este caso)
void liberarLista (int *** lista, int largoLista)  //Recibe como argumento una lista de matrices y la cantidad de matrices que tiene esta lista
{
    //Ciclo que recorre cada arreglo de la lista de arreglos
    for (int i = 0; i < largoLista; i++)
    {
        free(lista[i][0]);  //Liberamos la memoria del arreglo en la posicion 0
        free(lista[i][1]);  //Liberamos la memoria del arreglo en la posicion 1
        free(lista[i][2]);  //Liberamos la memoria del arreglo en la posicion 2
        free(lista[i]);  //Liberamos la memoria del arreglo que contenia los 3 arreglos
    }

    free(lista);  //Se libera la memoria utilizada por la lista de arreglos

    return;
}

//Esta función se encargar de agregar una solución (matriz ) a una lista 
int *** agregarSolucion (int *** lista, int *largoLista, int ** solucion)  //Recibe como argumentos una lista de matrices, la cantidad de elementos que posee esta lista y una matriz a agregar
{
    //Se crea una nueva lista para almacenar las soluciones
    int *** nuevaLista = (int ***)malloc(sizeof(int**)*(*largoLista+1));
    //Se crean las matrices dentro de cada elemento de la lista
    for (int i = 0; i < *largoLista + 1; ++i)  //Ciclo para recorrer todos los elementos de la lista
    {
		nuevaLista[i] = (int **)malloc(sizeof(int *)*3);  //Se crean las 3 filas para la matriz
		for (int j = 0; j < 3; ++j)
        {
			nuevaLista[i][j] = (int *)malloc(sizeof(int)*4);  //Se crean las 4 columnas para la matriz 
		}
	}

    //Se copian las soluciones existentes
	for (int indiceSolucion = 0; indiceSolucion < *largoLista; indiceSolucion++)  //Ciclo para recorrer todos los elementos de la lista
    {
		for(int fila = 0; fila < 3; fila++)  //Ciclo para recorrer las filas 
        {
			for (int columna = 0; columna < 4; columna++)  //Ciclo para recorrer las columnas
            {
				nuevaLista[indiceSolucion][fila][columna] = lista[indiceSolucion][fila][columna];  //Se copian los elementos de la lista antigua a la nueva lista
			}
		}
	}

    //Se agrega la nueva solución a la nueva lista
	for (int filaSolucion = 0; filaSolucion < 3; filaSolucion++)  //Ciclo para recorrer las filas 
    {
		for (int columnaSolucion = 0; columnaSolucion < 4; columnaSolucion++)  //Ciclo para recorrer las columnas
        {
			nuevaLista[*largoLista][filaSolucion][columnaSolucion] = solucion[filaSolucion][columnaSolucion];  //Se copian los elementos de la solucion a agregar al ultimo elemento de la nueva lista
		}
	}

    liberarLista(lista, *largoLista);  //Liberamos la memoria utilizada por la antigua lista de soluciones y sus soluciones 
    *largoLista = *largoLista + 1;//Se actualiza el nuevo largo de la lista de soluciones


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
			nuevaLista[i][j] = (int *)malloc(sizeof(int)*4);  //Se crean 4 columnas en cada fila de los elementode de la nueva lista
		}
	}

    //Se copian las soluciones existentes, excepto aquel que se desea eliminar
	int indiceNuevaLista = 0;  //Esta variable nos sirve para saber el indice de posicion en la nueva lista
	int indiceAntiguaLista = 0;  //Este variable nos sirve para saber el indice de posicion en la antigua lista

	while(indiceAntiguaLista < *cantSoluciones)  //Mientra hayan soluciones por copiar
    {
		if(indiceEliminar != indiceAntiguaLista)  //Comprobamos que la solucion a copiar no sea la solucion a eliminar
        {
			for(int fila = 0; fila < 3; fila ++)  //Ciclo para recorrer las filas
            {
				for (int columna = 0; columna < 4; ++columna)  //Ciclo para recorrer las columnas
                {
					nuevaLista[indiceNuevaLista][fila][columna] = listaSoluciones[indiceAntiguaLista][fila][columna];  //Copiamos el valor
				}
			}

			indiceNuevaLista++;  //Si se agrega una solucion, se aumenta el valor del indice de la nueva lista
		}
		
        //En caso de que no se entre al if, significa que la solucion actual es la que se desea eliminar, por lo que no se copiará y solamanete se incrementará el indice de la antigua lista para copiar el siguiente elemento
		indiceAntiguaLista++;  //Se incrementa el indice de la antigua lista para copiar el siguiente elemento
	}

    liberarLista(listaSoluciones, *cantSoluciones);  //Liberamos la memoria utilizada por la antigua lista de soluciones y sus soluciones
    *cantSoluciones = *cantSoluciones - 1;  //Se actualiza la nueva cantidad de soluciones que existen

    return nuevaLista;  //Se retorna la nueva lista de soluciones
}

//Esta funcion se encarga de imprimir una matriz en especifico, será utilizado para imprimir las solucion (matrices) de la lista de soluciones
void imprimirMatriz (int ** cuadrado)  //Recibe como argumento una solución (matriz) a imprimir
{
    printf("El nieto menor tiene: %d de 500, %d de 100, %d de 50, %d de 10, con un total de: %d monedas y %d de dinero\n", cuadrado[0][0],cuadrado[0][1],cuadrado[0][2],cuadrado[0][3], (cuadrado[0][0]+cuadrado[0][1]+cuadrado[0][2]+cuadrado[0][3]), (cuadrado[0][0]*V1+cuadrado[0][1]*V2+cuadrado[0][2]*V3+cuadrado[0][3]*V4));
    printf("El nieto del medio tiene: %d de 500, %d de 100, %d de 50, %d de 10, con un total de: %d monedas y %d de dinero\n", cuadrado[1][0],cuadrado[1][1],cuadrado[1][2],cuadrado[1][3], (cuadrado[1][0]+cuadrado[1][1]+cuadrado[1][2]+cuadrado[1][3]), (cuadrado[1][0]*V1+cuadrado[1][1]*V2+cuadrado[1][2]*V3+cuadrado[1][3]*V4));
    printf("El nieto mayor tiene: %d de 500, %d de 100, %d de 50, %d de 10, con un total de: %d monedas y %d de dinero\n", cuadrado[2][0],cuadrado[2][1],cuadrado[2][2],cuadrado[2][3], (cuadrado[2][0]+cuadrado[2][1]+cuadrado[2][2]+cuadrado[2][3]), (cuadrado[2][0]*V1+cuadrado[2][1]*V2+cuadrado[2][2]*V3+cuadrado[2][3]*V4));
	
	return;
}

//Funcion que se encargará de imprimir cada matriz dentro de la lista de soluciones 
void imprimirSoluciones (int *** listaSoluciones, int cantSoluciones)  //Recibe como argumentos la lista de soluciones (lista de matrices) y la cantidad de elementos que posee
{
    for(int indiceSolucion = 0; indiceSolucion < cantSoluciones; indiceSolucion ++)  //Ciclo para recorrer todos los elementos (soluciones) de la lista
    {
		printf("Solucion %d\n", indiceSolucion+1);  //Mostramos el numero de solucion que estamos imprimiendo
        imprimirMatriz(listaSoluciones[indiceSolucion]);  //Mostramos la solución
        printf("\n");
    }

	return;
}

///Funcion que verifica que el nieto menor tenga la mayor cantidad de monedas entre los 3 nietos
//Recibe como argumento los 12 valores que compondrán la solución (matriz) que representan la cantidad de monedas de cada nieto
int verificarNietoMenor (int m1X,int m2X,int m3X,int m4X,int m1Y,int m2Y,int m3Y,int m4Y,int m1Z,int m2Z,int m3Z,int m4Z)  
{
    //Verificamos que la cantidad de monedas del nieto menor sea mayor a la del nieto del medio y el mayor respectivamente
    if (m1X+m2X+m3X+m4X > m1Y+m2Y+m3Y+m4Y && m1X+m2X+m3X+m4X > m1Z+m2Z+m3Z+m4Z)
    {
        return 1;  //Retorna 1, indicando que la solucion cumple la restriccion
    }

    else
    {
        return 0;  //Retorna 0, indicando que la solucion no cumple con la restriccion
    }
}

int main()
{
    int cantidadSoluciones = 0;  //Variable para almacenar la cantidad de soluciones al problema
    int *** listaSoluciones = (int ***)malloc(sizeof(int**)*cantidadSoluciones);  //Se crea la lista de soluciones y se asigna la memoria para ella

    //Ciclos para repartir monedas al nieto del medio
    for (int m1Y = 0; m1Y <= C1; m1Y++)
    {
        for (int m2Y = 0; m2Y <= C2; m2Y++)
        {
            for (int m3Y = 0; m3Y <= C3; m3Y++)
            {
                //El siguiente for tiene la restriccion "m4Y >= ((V_TOTAL/5)-m1Y*V1-m2Y*V2-m3Y*V3)/V4", obtenida del despeje de la restricción de que el nieto del medio debe tener al menos el 20% del dinero
                //Con esta restriccion podemos limitar los ciclos y solo considerar aquellos donde se cumpla esta condición
                for (int m4Y = 0; m4Y >= ((V_TOTAL/5)-m1Y*V1-m2Y*V2-m3Y*V3)/V4 && m4Y <= C4; m4Y++)
                {
                    //Ciclo para repartir monedas al nieto del medio
                    //Todos los ciclos de este nieto tienen la restricción por ejemplo: "m1Z <= C1 - m1Y", con esto se busca descartar los casos donde se entreguen más monedas de las totales
                    //Con estas restricciones nos aseguramos de solamente entregar una cantidad menor o igual a las disponibles después de entregarle monedas al nieto del medio
                    for (int m1Z = 0; m1Z <= C1 && m1Z <= C1 - m1Y; m1Z++)
                    {
                        for (int m2Z = 0; m2Z <= C2 && m2Z <= C2 - m2Y; m2Z++)
                        {
                            for (int m3Z = 0; m3Z <= C3 && m3Z <= C3 - m3Y; m3Z++)
                            {
                                //El siguiente for tiene la restriccion "m4Z >= ((V_TOTAL/2)-m1Z*V1-m2Z*V2-m3Z*V3)/V4", obtenida del despeje de la restricción de que el nieto mayor debe tener al menos el 50% del dinero
                                //Con esta restriccion podemos limitar los ciclos y solo considerar aquellos donde se cumpla esta condición
                                for (int m4Z = 0; m4Z <= C4 && m4Z >= ((V_TOTAL/2)-m1Z*V1-m2Z*V2-m3Z*V3)/V4 &&  m4Z <= C4 - m4Y; m4Z++) 
                                {
                                    //Aquí utilizamos la restricción de que solamente se deben considerar las soluciones donde se entreguen todas las monedas
                                    //Le entregamos al nieto menor la totalidad de las monedas restantes luego de repartir al nieto del medio y el mayor
                                    int m1X = C1 - m1Z - m1Y;
                                    int m2X = C2 - m2Z - m2Y;
                                    int m3X = C3 - m3Z - m3Y;
                                    int m4X = C4 - m4Z - m4Y;
                                    
                                    //Antes de agregar la posible solucion verificamos que cumpla la restricción de que el nieto menor debe ser el nieto con más monedas
                                    if (verificarNietoMenor(m1X,m2X,m3X,m4X,m1Y,m2Y,m3Y,m4Y,m1Z,m2Z,m3Z,m4Z))
                                    {
                                        int ** solucion = crearSolucion (m1X,m2X,m3X,m4X,m1Y,m2Y,m3Y,m4Y,m1Z,m2Z,m3Z,m4Z);  //Creamos una solución (matriz) que representa la solución encontrada
                                        //imprimirMatriz(solucion);//Descomentar en caso de querer todas las soluciones que se van agregando
                                        listaSoluciones = agregarSolucion(listaSoluciones, &cantidadSoluciones, solucion);  //Agregamos la solución encontrada a la lista de soluciones 
                                        //printf("Soluciones actuales: %d\n", cantidadSoluciones);//Descomentar en caso de querer la cantidad de soluciones encontradas
                                    }

                                    //Ya que el código debe mostrar al menos una solución, se mostrará la primera solución encontrada por el programa y luego este seguirá buscando más soluciones
                                    if (cantidadSoluciones == 1)
                                    {
                                        printf("La primera solucion encontrada es: \n");
                                        imprimirMatriz(listaSoluciones[0]);  //Mostramos al usuario la primera solución encontrada
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    //Luego de muchooooooooo tiempo calculando todas las soluciones al problema, procedemos a mostrar todas las soluciones finales encontradas
    imprimirSoluciones(listaSoluciones, cantidadSoluciones);
    liberarLista(listaSoluciones, cantidadSoluciones);  //Liberamos la memoria utilizada por la lista de soluciones y las soluciones

    return 0;
}