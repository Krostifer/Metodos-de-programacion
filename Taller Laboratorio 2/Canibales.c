#include <stdio.h>
#include <stdlib.h>

typedef struct Estado
{
    int* islaB;
    int id;
    int idAnterior;
    int transicion;

} Estado;

//***************************************** FUNCIONES PRINCIPALES *******************************************

//Funcion que agrega un estado a una lista de estados
Estado * agregarEstado (Estado * listaEstados, int *largoLista, Estado estadoAgregar)  //Recibe como elementos una lista de estados (abiertos o cerrados), la cantidad de elementos que tiene esta lista y el estado a agregar
{
    Estado * nuevaLista = (Estado*)malloc(sizeof(Estado)*((*largoLista)+1));  //Se crea una nueva lista con el tamanio nuevo

    //Copiamos los elementos de la lista antigua a la nueva
    for (int i = 0; i < *largoLista; i++)  //Ciclo para recorrer los elementos de la lista
    {
        nuevaLista[i].islaB =  (int*)malloc(sizeof(int)*3);  //Se asigna la memoria para el arreglo que representa el estado de la isla B
        nuevaLista[i].islaB[0] = listaEstados[i].islaB[0];  //Se copian los elementos del arreglo
        nuevaLista[i].islaB[1] = listaEstados[i].islaB[1];  //Se copian los elementos del arreglo
        nuevaLista[i].islaB[2] = listaEstados[i].islaB[2];  //Se copian los elementos del arreglo

        nuevaLista[i].id = listaEstados[i].id;
        nuevaLista[i].idAnterior = listaEstados[i].idAnterior;
        nuevaLista[i].transicion = listaEstados[i].transicion;
    }

    //Ahora copiamos el nuevo estado al final de la lista
    nuevaLista[*largoLista].islaB =  (int*)malloc(sizeof(int)*3);  //Se asigna la memoria para el arreglo que representa el estado de la isla B
    nuevaLista[*largoLista].islaB[0] = estadoAgregar.islaB[0];  //Se copian los elementos del arreglo
    nuevaLista[*largoLista].islaB[1] = estadoAgregar.islaB[1];  //Se copian los elementos del arreglo
    nuevaLista[*largoLista].islaB[2] = estadoAgregar.islaB[2];  //Se copian los elementos del arreglo

    nuevaLista[*largoLista].id = estadoAgregar.id;
    nuevaLista[*largoLista].idAnterior = estadoAgregar.idAnterior;
    nuevaLista[*largoLista].transicion = estadoAgregar.transicion;

    free(listaEstados);  //Liberamos la memoria utilizada por la antigua lista de estados
    *largoLista = *largoLista + 1;  //Actualizamos el largo de la lista de estados
    return nuevaLista;  //Retornamos la nueva lista con los nuevos estados
}

//Funcion que eliminará el primer elemento de una lista de estados y lo retornará para utilizarlo
Estado extraerEstado (Estado * listaEstados, int *largoLista)  //Recibe como argumentos una lista de estados y la cantidad de elementos que posee esta lista de estados
{
    //Creamos un nuevo estado para almacenar el estado a extraer
    Estado pop;
    pop.islaB = (int*)malloc(sizeof(int)*3);  //Se asigna la memoria para el arreglo que representa el estado de la isla B
    pop.islaB[0] = listaEstados[0].islaB[0];  //Se copian los elementos del arreglo
    pop.islaB[1] = listaEstados[0].islaB[1];  //Se copian los elementos del arreglo
    pop.islaB[2] = listaEstados[0].islaB[2];  //Se copian los elementos del arreglo

    pop.id = listaEstados[0].id;
    pop.idAnterior = listaEstados[0].idAnterior;
    pop.transicion = listaEstados[0].transicion;

    //Actualizamos los elementos de la lista de estados copiando los valores de cada estado en el estado anterior a él
    for (int i = 1; i < *largoLista; ++i)
    {
		listaEstados[i-1].islaB[0] = listaEstados[i].islaB[0];
        listaEstados[i-1].islaB[1] = listaEstados[i].islaB[1];
        listaEstados[i-1].islaB[2] = listaEstados[i].islaB[2];
		
		listaEstados[i-1].id = listaEstados[i].id;
		listaEstados[i-1].idAnterior = listaEstados[i].idAnterior;
		listaEstados[i-1].transicion = listaEstados[i].transicion;
    }

    *largoLista = *largoLista - 1;  //Actualizamos la nueva cantidad de elementos que tiene la lista

    return pop;  //Retornamos el estado extraido de la lista
}

//Funcion que agregara una transicion a una lista de transiciones, será utilizada para imprimir las transiciones hechas para llegar a la solucion
int** agregarTransicion(int** listaTransiciones, int* largoLista, int* vector)  //Recibe como argumentos una lista de transiciones (lista de arreglos), la cantidad de elementos que tiene la lista y la transicion (arreglo) a agregar
{
	int ** nuevaLista = (int **)malloc(sizeof(int*)*(*largoLista + 1));  //Asigamos memoria para una nueva lista con la transicion nueva

    //Copiamos las transiciones anteriores a la nueva lista
	for (int i = 0; i < *largoLista; ++i)
    {
		nuevaLista[i] = (int*)malloc(sizeof(int)*3);;
        nuevaLista[i][0] = listaTransiciones[i][0];
        nuevaLista[i][1] = listaTransiciones[i][1]; 
        nuevaLista[i][2] = listaTransiciones[i][2];
	}

    //Agregamos la nueva transicion a la nueva lista
	nuevaLista[*largoLista] =  (int*)malloc(sizeof(int)*3);;
    nuevaLista[*largoLista][0] =  vector[0];
    nuevaLista[*largoLista][1] =  vector[1];
    nuevaLista[*largoLista][2] =  vector[2];

	*largoLista = *largoLista + 1;  //Se actualiza la cantidad de elementos que tiene la lista de transiciones
	free(listaTransiciones);  //Se libera la memoria utilizada por la lista anterior
	return nuevaLista;  //Se retorna la nueva lista de transiciones con la transicion agregada
}

void imprimirSoluciones (Estado solucion, Estado * listaCerrados, int largoCerrados)
{
    
    int idBuscado = solucion.idAnterior;
    int indiceEstadoAnterior;
    int largoTransiciones = 1;

    int ** transiciones = (int **)malloc(sizeof(int*)*1);  //Creamos una lista de matrices para almacenar los vectores de la isla B

    transiciones[0] = (int*)malloc(sizeof(int)*3);;  //Creamos un arreglo de 3 elementos en la primera posicion de la lista
    transiciones[0][0] = solucion.islaB[0];
    transiciones[0][1] = solucion.islaB[1];
    transiciones[0][2] = solucion.islaB[2];

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
		transiciones = agregarTransicion(transiciones, &largoTransiciones, listaCerrados[indiceEstadoAnterior].islaB);
    }

    transiciones = agregarTransicion(transiciones, &largoTransiciones, listaCerrados[0].islaB);  //Agregamos el estado incial a la lista de transiciones

    //Ahora imprimimos las transiciones de la lista de transiciones
    for (int i = largoTransiciones-1; i >= 0; i--)  //Ciclo para recorrer la lista de transiciones desde atras hacia adelante
    {
        printf("<%d|%d|%d>\n", transiciones[i][0], transiciones[i][1], transiciones[i][2]);
    }
}

//***************************************** VERIFICACIONES DE ESTADOS *******************************************

//Funcion que se encargar de revisar si es que el estado entregado se encuentra dentro de la lista de estados entregada
int noEsta (Estado * listaEstados, int largoLista, Estado estadoActual)
{
    for (int i = 0; i < largoLista; i++)  //Ciclo para recorrer todos los elementos de la lista de estados
    {
        //Comparamos los vectores que representan la isla B para ver si es que ya existe un estado igual
        if (listaEstados[i].islaB[0] == estadoActual.islaB[0] && listaEstados[i].islaB[1] == estadoActual.islaB[1] && listaEstados[i].islaB[2] == estadoActual.islaB[2])
        {
            return 0;  //Retorna 0, indicando que existe un estado con igual distribucion de canibales y misioneros
        }
    }

    return 1;  //Retorna 1, indicando que no existe un estado con igual distribucion de canibales y misioneros
}

//Funcion que se encarga de comprobar si es que el estado entregado es el estado final del problema
int esFinal (Estado estadoActual, int personas)  //Recibe como argumentos un estado a revisar y la cantidad de misiones-canibales totales del problema
{
    if (estadoActual.islaB[0] == personas && estadoActual.islaB[1] == personas)
    {
        return 1;  //Retorna 1, inidicando que el estado revisado es el estado final del problema
    }

    else
    {
        return 0;  //Retorna 0, indicando que el estado revisado no es un estado final del problema
    }
    
}

//***************************************** VERIFICACIONES DE MOVIMIENTOS *******************************************

//Funcion que verifica si es que se puede mover un canibal al lado contrario de donde se encuentra el bote 
int puedoCanibal (Estado estadoActual, int personas)  //Recibe como argumentos el estado al cual se le quiere aplicar un movimiento y la cantidad de misioneros-canibales totales
{
    if (estadoActual.islaB[2] == 0)  //Si el barco se encuentra en la isla A, el canibal será movido a la isla B
    {
        if (estadoActual.islaB[0]+1 <= personas)
        {
            if (estadoActual.islaB[1] == 0 || estadoActual.islaB[0]+1 <= estadoActual.islaB[1] )
            {
                if ((personas - estadoActual.islaB[1]) == 0 || (personas - (estadoActual.islaB[0]+1)) <= (personas - estadoActual.islaB[1]))
                {
                    return 1;  //Retorna 1, indicando que se puede realizar este movimiento
                }

                else
                {
                    return 0;
                }
                
            }

            else
            {
                return 0;
            }
            
        }

        else
        {
            return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
        }
    }

    else  //Si el barco se encuentra en la isla B, el canibal será movido a la isla A
    {
        if (estadoActual.islaB[0]-1 >= 0)
        {
            if (estadoActual.islaB[1] == 0 || estadoActual.islaB[0]-1 <= estadoActual.islaB[1])
            {
                if ((personas - estadoActual.islaB[1]) == 0 || (personas - (estadoActual.islaB[0]-1)) <= (personas - estadoActual.islaB[1]))
                {
                    return 1;  //Retorna 1, indicando que se puede realizar este movimiento
                }

                else
                {
                    return 0;
                }
                
            }

            else
            {
                return 0;
            }  
        }

        else
        {
            return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
        }
    }
}

//Funcion que verifica si es que se puede mover dos canibales al lado contrario de donde se encuentra el bote 
int puedoCanibales (Estado estadoActual, int personas)  //Recibe como argumentos el estado al cual se le quiere aplicar un movimiento y la cantidad de misioneros-canibales totales
{
    if (estadoActual.islaB[2] == 0)  //Si el barco se encuentra en la isla A, los canibales serán movidos a la isla B
    {
        if (estadoActual.islaB[0]+2 <= personas)
        {
            if (estadoActual.islaB[1] == 0 || estadoActual.islaB[0]+2 <= estadoActual.islaB[1])
           {
               if ((personas - estadoActual.islaB[1]) == 0 || (personas - (estadoActual.islaB[0]+2)) <= (personas - estadoActual.islaB[1]))
                {
                    return 1;  //Retorna 1, indicando que se puede realizar este movimiento
                }

                else
                {
                    return 0;
                }
                
           }

           else
            {
                return 0;
            }
            
        }

        else
        {
            return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
        }
    }

    else  //Si el barco se encuentra en la isla B, los canibales serán movidos a la isla A
    {
        if (estadoActual.islaB[0]-2 >= 0)
        {
            if (estadoActual.islaB[1] == 0 || estadoActual.islaB[0]-2 <= estadoActual.islaB[1])
            {
                if ((personas - estadoActual.islaB[1]) == 0 || (personas - (estadoActual.islaB[0]-2)) <= (personas - estadoActual.islaB[1]))
                {
                    return 1;  //Retorna 1, indicando que se puede realizar este movimiento
                }

                else
                {
                    return 0;
                }
                
            }

            else
            {
                return 0;
            }
            
        }

        else
        {
            return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
        }
    }
}

//Funcion que verifica si es que se puede mover un misionero al lado contrario de donde se encuentra el bote 
int puedoMisionero (Estado estadoActual, int personas)  //Recibe como argumentos el estado al cual se le quiere aplicar un movimiento y la cantidad de misioneros-canibales totales
{
    if (estadoActual.islaB[2] == 0)  //Si el barco se encuentra en la isla A, el misionero será movido a la isla B
    {
        if (estadoActual.islaB[1]+1 <= personas && estadoActual.islaB[1]+1 >= estadoActual.islaB[0])
        {
            if ((personas - (estadoActual.islaB[1]+1)) == 0 || (personas - (estadoActual.islaB[1]+1)) >= (personas - estadoActual.islaB[0]))
            {
                return 1;  //Retorna 1, indicando que se puede realizar este movimiento
            }

            else
            {
                return 0;
            }
            
        }

        else
        {
            return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
        }
    }

    else
    {
        if (estadoActual.islaB[1]-1 >= 0 && estadoActual.islaB[1]-1 >= estadoActual.islaB[0])
        {
            if ((personas - (estadoActual.islaB[1]-1)) == 0 || (personas - (estadoActual.islaB[1]-1)) >= (personas - estadoActual.islaB[0]))
            {
                return 1;  //Retorna 1, indicando que se puede realizar este movimiento
            }

            else
            {
                return 0;
            }
            
        }

        else
        {
            return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
        }
    }
}

//Funcion que verifica si es que se puede mover dos misioneros al lado contrario de donde se encuentra el bote 
int puedoMisioneros (Estado estadoActual, int personas)  //Recibe como argumentos el estado al cual se le quiere aplicar un movimiento y la cantidad de misioneros-canibales totales
{
    if (estadoActual.islaB[2] == 0)  //Si el barco se encuentra en la isla A, los misioneros serán movidos a la isla B
    {
        if (estadoActual.islaB[1]+2 <= personas && estadoActual.islaB[1]+2 >= estadoActual.islaB[0])
        {
            if ((personas - (estadoActual.islaB[1]+2)) == 0 || (personas - (estadoActual.islaB[1]+2)) >= (personas - estadoActual.islaB[0]))
            {
                return 1;  //Retorna 1, indicando que se puede realizar este movimiento
            }

            else
            {
                return 0;
            }
            
        }

        else
        {
            return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
        }
    }

    else  //Si el barco se encuentra en la isla B, los misioneros serán movidos a la isla A
    {
        if (estadoActual.islaB[1]-2 <= 0 && estadoActual.islaB[1]-2 >= estadoActual.islaB[0])
        {
            if ((personas - (estadoActual.islaB[1]-2) == 0 || (personas - (estadoActual.islaB[1]-2)) >= (personas - estadoActual.islaB[0])))
            {
                return 1;  //Retorna 1, indicando que se puede realizar este movimiento
            }

            else
            {
                return 0;
            }
            
        }

        else
        {
            return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
        }
    }
}

//Funcion que verifica si es que se puede mover un misionero y un canibal al lado contrario de donde se encuentra el bote 
int puedoMisioneroCanibal (Estado estadoActual, int personas)  //Recibe como argumentos el estado al cual se le quiere aplicar un movimiento y la cantidad de misioneros-canibales totales
{
    if (estadoActual.islaB[2] == 0)  //Si el barco se encuentra en la isla A, el misionero y el canibal serán movidos a la isla B
    {
        if (estadoActual.islaB[0]+1 <= personas && estadoActual.islaB[1]+1 <= personas && estadoActual.islaB[1]+1 >= estadoActual.islaB[0]+1 && (personas - (estadoActual.islaB[1]+1)) >= (personas - (estadoActual.islaB[0]+1)))
        {
            return 1;  //Retorna 1, indicando que se puede realizar este movimiento
        }

        else
        {
            return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
        }
    }

    else  //Si el barco se encuentra en la isla B, el misionero y el canibal serán movidos a la isla A
    {
        if (estadoActual.islaB[0]-1 <= personas && estadoActual.islaB[1]-1 <= personas && estadoActual.islaB[1]-1 >= estadoActual.islaB[0]-1 && (personas - (estadoActual.islaB[1]-1)) >= (personas - (estadoActual.islaB[0]-1)))
        {
            return 1;  //Retorna 1, indicando que se puede realizar este movimiento
        }

        else
        {
            return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
        }
    }
}

//***************************************** MOVIMIENTOS *******************************************
//Funcion que moverá un canibal al lado contrario donde se encuentra el bote
Estado moverCanibal (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado al que se le aplicará el movimiento y el id para el nuevo estado a generar
{
    Estado nuevoEstado;  //Creamos un nuevo estado
    nuevoEstado.islaB = (int*)malloc(sizeof(int)*3);  //Asignamos la memoria para el nuevo vector de la isla B

    if (estadoActual.islaB[2] == 0)  //Si el barco se encontraba en la isla A, el canibal se sumará a la isla B
    {
        nuevoEstado.islaB[0] = estadoActual.islaB[0] + 1;  //Sumamos 1 a la cantidad de canibales en la isla B
        nuevoEstado.islaB[2] = 1;  //Indica que el barco se encuentra ahora en la isla B
    }
    
    else  //En caso de que el barco se encontraba en la isla B, el canibal se sumara a la isla A
    {
        nuevoEstado.islaB[0] = estadoActual.islaB[0] - 1;  //Se resta 1 a la cantidad de canibales en la isla B
        nuevoEstado.islaB[2] = 0;  //Indica que el barco se encuentra ahora en la isla A
    }

    nuevoEstado.islaB[1] = estadoActual.islaB[1];  //La cantidad de misioneros no cambia
    
    nuevoEstado.id = idNuevoEstado;
    nuevoEstado.idAnterior = estadoActual.id;
    nuevoEstado.transicion = 1;

    return nuevoEstado;
}

//Funcion que moverá dos canibales al lado contrario donde se encuentra el bote
Estado moverCanibales (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado al que se le aplicará el movimiento y el id para el nuevo estado a generar
{
    Estado nuevoEstado;  //Creamos un nuevo estado
    nuevoEstado.islaB = (int*)malloc(sizeof(int)*3);  //Asignamos la memoria para el nuevo vector de la isla B

    if (estadoActual.islaB[2] == 0)  //Si el barco se encontraba en la isla A, los canibales se sumaran a la isla B
    {
        nuevoEstado.islaB[0] = estadoActual.islaB[0] + 2;  //Sumamos 2 a la cantidad de canibales en la isla B
        nuevoEstado.islaB[2] = 1;  //Indica que el barco se encuentra ahora en la isla B
    }
    
    else  //En caso de que el barco se encontraba en la isla B, los canibales se sumaran a la isla A
    {
        nuevoEstado.islaB[0] = estadoActual.islaB[0] - 2;  //Se resta 2 a la cantidad de canibales en la isla B
        nuevoEstado.islaB[2] = 0;  //Indica que el barco se encuentra ahora en la isla A
    }

    nuevoEstado.islaB[1] = estadoActual.islaB[1];  //La cantidad de misioneros no cambia
    
    nuevoEstado.id = idNuevoEstado;
    nuevoEstado.idAnterior = estadoActual.id;
    nuevoEstado.transicion = 2;

    return nuevoEstado;
}

//Funcion que moverá un misionero al lado contrario donde se encuentra el bote
Estado moverMisionero (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado al que se le aplicará el movimiento y el id para el nuevo estado a generar
{
    Estado nuevoEstado;  //Creamos un nuevo estado
    nuevoEstado.islaB = (int*)malloc(sizeof(int)*3);  //Asignamos la memoria para el nuevo vector de la isla B

    if (estadoActual.islaB[2] == 0)  //Si el barco se encontraba en la isla A, el misionero se sumará a la isla B
    {
        nuevoEstado.islaB[1] = estadoActual.islaB[1] + 1;  //Sumamos 1 a la cantidad de misioneros en la isla B
        nuevoEstado.islaB[2] = 1;  //Indica que el barco se encuentra ahora en la isla B
    }
    
    else  //En caso de que el barco se encontraba en la isla B, el misionero se sumara a la isla A
    {
        nuevoEstado.islaB[1] = estadoActual.islaB[1] - 1;  //Se resta 1 a la cantidad de misioneros en la isla B
        nuevoEstado.islaB[2] = 0;  //Indica que el barco se encuentra ahora en la isla A
    }

    nuevoEstado.islaB[0] = estadoActual.islaB[0];  //La cantidad de canibales no cambia
    
    nuevoEstado.id = idNuevoEstado;
    nuevoEstado.idAnterior = estadoActual.id;
    nuevoEstado.transicion = 3;

    return nuevoEstado;
}

//Funcion que moverá dos misioneros al lado contrario donde se encuentra el bote
Estado moverMisioneros (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado al que se le aplicará el movimiento y el id para el nuevo estado a generar
{
    Estado nuevoEstado;  //Creamos un nuevo estado
    nuevoEstado.islaB = (int*)malloc(sizeof(int)*3);  //Asignamos la memoria para el nuevo vector de la isla B

    if (estadoActual.islaB[2] == 0)  //Si el barco se encontraba en la isla A, los misioneros se sumarán a la isla B
    {
        nuevoEstado.islaB[1] = estadoActual.islaB[1] + 2;  //Sumamos 2 a la cantidad de misioneros en la isla B
        nuevoEstado.islaB[2] = 1;  //Indica que el barco se encuentra ahora en la isla B
    }
    
    else  //En caso de que el barco se encontraba en la isla B, los misioneros se sumara a la isla A
    {
        nuevoEstado.islaB[1] = estadoActual.islaB[1] - 2;  //Se resta 2 a la cantidad de misioneros en la isla B
        nuevoEstado.islaB[2] = 0;  //Indica que el barco se encuentra ahora en la isla A
    }

    nuevoEstado.islaB[0] = estadoActual.islaB[0];  //La cantidad de canibales no cambia
    
    nuevoEstado.id = idNuevoEstado;
    nuevoEstado.idAnterior = estadoActual.id;
    nuevoEstado.transicion = 4;

    return nuevoEstado;
}

//Funcion que moverá un misionero y un canibal al lado contrario donde se encuentra el bote
Estado moverMisioneroCanibal (Estado estadoActual, int idNuevoEstado)  //Recibe como argumentos el estado al que se le aplicará el movimiento y el id para el nuevo estado a generar
{
    Estado nuevoEstado;  //Creamos un nuevo estado
    nuevoEstado.islaB = (int*)malloc(sizeof(int)*3);  //Asignamos la memoria para el nuevo vector de la isla B

    if (estadoActual.islaB[2] == 0)  //Si el barco se encontraba en la isla A, el canibal y el misionero se sumaran a la isla B
    {
        nuevoEstado.islaB[0] = estadoActual.islaB[0] + 1;  //Sumamos 1 a la cantidad de canibales en la isla B
        nuevoEstado.islaB[1] = estadoActual.islaB[1] + 1;  //Sumamos 1 a la cantidad de misioneros en la isla B
        nuevoEstado.islaB[2] = 1;  //Indica que el barco se encuentra ahora en la isla B
    }
    
    else  //En caso de que el barco se encontraba en la isla B, el canibal y el misionero se sumaran a la isla A
    {
        nuevoEstado.islaB[0] = estadoActual.islaB[0] - 1;  //Se resta 1 a la cantidad de canibales en la isla B
        nuevoEstado.islaB[1] = estadoActual.islaB[1] - 1;  //Se resta 1 a la cantidad de misioneros en la isla B
        nuevoEstado.islaB[2] = 0;  //Indica que el barco se encuentra ahora en la isla A
    }  
    
    nuevoEstado.id = idNuevoEstado;
    nuevoEstado.idAnterior = estadoActual.id;
    nuevoEstado.transicion = 5;

    return nuevoEstado;
}

int main()
{
    int idNuevoEstado = 1;

    int cantidadAbiertos = 0;
    Estado * abiertos = (Estado *)malloc(sizeof(Estado)*cantidadAbiertos);  //Creamos la lista para almacenar los estados abiertos
	int cantidadCerrados = 0;
	Estado * cerrados = (Estado *)malloc(sizeof(Estado)*cantidadCerrados);  //Creamos la lista para alamacenar los estados cerrados
    int cantidadSoluciones = 0;
    Estado * soluciones = (Estado *)malloc(sizeof(Estado)*cantidadSoluciones);  //Creamos una lista para almacenar los estado finales

    //*********************** INGRESO DE LA CANTIDAD DE MISIONEROS-CANIBALES POR PARTE DEL USUARIO ***********************
    int personas;
    printf("Ingrese numero de misioneros y canibales: ");
    scanf("%d", &personas);
    printf("\n");
    //***************************************************************************

    //*********************** CREACION DEL ESTADO INICIAL ***********************
    Estado estadoInicial;
    estadoInicial.islaB = (int*)malloc(sizeof(int)*3);  //Asignamos la memoria para el nuevo vector de la isla B
    estadoInicial.islaB[0] = 0;  //Asiganmos los valores inciales del vector para la isla B
    estadoInicial.islaB[1] = 0;   //Asiganmos los valores inciales del vector para la isla B
    estadoInicial.islaB[2] = 0;  //Asiganmos los valores inciales del vector para la isla B
    
    estadoInicial.id = 0;
    estadoInicial.idAnterior = 0;
    estadoInicial.transicion = 0;
    //***************************************************************************

    abiertos = agregarEstado(abiertos, &cantidadAbiertos, estadoInicial);  //Agreagamos el estado incial a la lista de estados abiertos

    while (cantidadAbiertos > 0)  //Mientras queden estados por revisar dentro de la lista de estados abiertos
    {
        Estado estadoActual = extraerEstado(abiertos, &cantidadAbiertos);  //Extraemos el primer estado de la lista de estados abiertos
        cerrados = agregarEstado(cerrados, &cantidadCerrados, estadoActual);  //Agregamos el estado actual a la lista de estados cerrados

        //*************************************** COMENZAMOS A REALIZAR LOS MOVIMIENTOS ******************************************

        if (puedoCanibal(estadoActual, personas))
        {
            Estado nuevoEstado = moverCanibal(estadoActual, idNuevoEstado);
            
            if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
            {
                idNuevoEstado = idNuevoEstado + 1;

                if (esFinal(nuevoEstado, personas))
                {
                    soluciones = agregarEstado(soluciones, &cantidadSoluciones, nuevoEstado);
                }

                else
                {
                    abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
                }
            }
        }

        if (puedoCanibales(estadoActual, personas))
        {
            Estado nuevoEstado = moverCanibales(estadoActual, idNuevoEstado);
            
            if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
            {
                idNuevoEstado = idNuevoEstado + 1;

                if (esFinal(nuevoEstado, personas))
                {
                    soluciones = agregarEstado(soluciones, &cantidadSoluciones, nuevoEstado);
                }

                else
                {
                    abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
                }
            }
        }

        if (puedoMisionero(estadoActual, personas))
        {
            Estado nuevoEstado = moverMisionero(estadoActual, idNuevoEstado);
            
            if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
            {
                idNuevoEstado = idNuevoEstado + 1;
                
                if (esFinal(nuevoEstado, personas))
                {
                    soluciones = agregarEstado(soluciones, &cantidadSoluciones, nuevoEstado);
                }

                else
                {
                    abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
                }
            }
        }

        if (puedoMisioneros(estadoActual, personas))
        {
            Estado nuevoEstado = moverMisioneros(estadoActual, idNuevoEstado);
            
            if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
            {
                idNuevoEstado = idNuevoEstado + 1;
                
                if (esFinal(nuevoEstado, personas))
                {
                    soluciones = agregarEstado(soluciones, &cantidadSoluciones, nuevoEstado);
                }

                else
                {
                    abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
                }
            }
        }

        if (puedoMisioneroCanibal(estadoActual, personas))
        {
            Estado nuevoEstado = moverMisioneroCanibal(estadoActual, idNuevoEstado);
            
            if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))
            {
                idNuevoEstado = idNuevoEstado + 1;
                
                if (esFinal(nuevoEstado, personas))
                {
                    soluciones = agregarEstado(soluciones, &cantidadSoluciones, nuevoEstado);
                }

                else
                {
                    abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);
                }
            }
        }
    }

    //*************************************** COMENZAMOS IMPRIMIR LAS SOLUCIONES ******************************************

    if (cantidadSoluciones == 0)
    {
        printf("No se encontro una solucion\n");
        return 0;
    }

    else
    {
        for (int i = 0; i < cantidadSoluciones; i++)
        {
            printf ("Solucion %d\n", i+1);
            imprimirSoluciones(soluciones[i], cerrados, cantidadCerrados);
            printf("\n");
        }
    }

    return 0;
}