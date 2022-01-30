//Rut: 20.239.786-7
//Seccion: L6
//Fecha de creacion: 08/09/2020, ultima revision 15/09/2020

#include <stdio.h>
#include <stdlib.h>


//****************************************************************************************** CANIBALES Y MISIONEROS ******************************************************************************************
//Definimos la estructura que tendrá cada estado
typedef struct Estado
{
    int* islaB;  //Vector (arreglo) que representa el estado de la isla B
    int id;  //Identificador del estado actual
    int idAnterior;  //Identificador del estado que genero a este

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
    }

    //Ahora copiamos el nuevo estado al final de la lista
    nuevaLista[*largoLista].islaB =  (int*)malloc(sizeof(int)*3);  //Se asigna la memoria para el arreglo que representa el estado de la isla B
    nuevaLista[*largoLista].islaB[0] = estadoAgregar.islaB[0];  //Se copian los elementos del arreglo
    nuevaLista[*largoLista].islaB[1] = estadoAgregar.islaB[1];  //Se copian los elementos del arreglo
    nuevaLista[*largoLista].islaB[2] = estadoAgregar.islaB[2];  //Se copian los elementos del arreglo

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
    pop.islaB = (int*)malloc(sizeof(int)*3);  //Se asigna la memoria para el arreglo que representa el estado de la isla B
    pop.islaB[0] = listaEstados[0].islaB[0];  //Se copian los elementos del arreglo
    pop.islaB[1] = listaEstados[0].islaB[1];  //Se copian los elementos del arreglo
    pop.islaB[2] = listaEstados[0].islaB[2];  //Se copian los elementos del arreglo

    pop.id = listaEstados[0].id;
    pop.idAnterior = listaEstados[0].idAnterior;

    //Actualizamos los elementos de la lista de estados copiando los valores de cada estado en el estado anterior a él
    for (int i = 1; i < *largoLista; ++i)
    {
		listaEstados[i-1].islaB[0] = listaEstados[i].islaB[0];
        listaEstados[i-1].islaB[1] = listaEstados[i].islaB[1];
        listaEstados[i-1].islaB[2] = listaEstados[i].islaB[2];
		
		listaEstados[i-1].id = listaEstados[i].id;
		listaEstados[i-1].idAnterior = listaEstados[i].idAnterior;
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

//Funcion encargada de mostrar los pasos para llegar a cada solucion obtenida
void imprimirSolucionesCanibales (Estado solucion, Estado * listaCerrados, int largoCerrados)  //Recibe como argumentos el estado final (solucion), la lista de estados cerrados y la cantidad de elementos en la lista
{
    int idBuscado = solucion.idAnterior;  //Variable para almacenar el id que buscaremos dentro de la lista de cerrados
    int indiceEstadoAnterior;  //Variable que almacenará el indice dentro de cerrados que tiene el estado con el id buscado
    int largoTransiciones = 1;  //Variable que almacenará la cantidad de elementos que tiene la lista de transiciones

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
		idBuscado = listaCerrados[indiceEstadoAnterior].idAnterior;  //Actualizamos el id buscado, ahora será el id del estado que genero al que buscamos anteriormente
		transiciones = agregarTransicion(transiciones, &largoTransiciones, listaCerrados[indiceEstadoAnterior].islaB);  //Agregamos la transicion a la lista de transiciones
    }

    transiciones = agregarTransicion(transiciones, &largoTransiciones, listaCerrados[0].islaB);  //Agregamos el estado incial a la lista de transiciones

    //Ahora imprimimos las transiciones de la lista de transiciones
    for (int i = largoTransiciones-1; i >= 0; i--)  //Ciclo para recorrer la lista de transiciones desde atras hacia adelante
    {
        printf("<%d|%d|%d>\n", transiciones[i][0], transiciones[i][1], transiciones[i][2]);  //Imprimimos cada estado de la isla B
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
                    return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
                }
                
            }

            else
            {
                return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
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
                    return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
                }
                
            }

            else
            {
                return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
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
                    return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
                }   
           	}

           else
            {
                return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
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
                    return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
                }
            }

            else
            {
                return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
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
                return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
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
                return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
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
                return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
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
                return 0;  //Retorna 0; indicando que no se puede realizar este movimiento
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

    return nuevoEstado;  //Retornamos el nuevo estado generado luego de realizar el movimiento
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

    return nuevoEstado;  //Retornamos el nuevo estado generado luego de realizar el movimiento
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

    return nuevoEstado;  //Retornamos el nuevo estado generado luego de realizar el movimiento
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

    return nuevoEstado;  //Retornamos el nuevo estado generado luego de realizar el movimiento
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

    return nuevoEstado;  //Retornamos el nuevo estado generado luego de realizar el movimiento
}

int canibales ()
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

    if (personas <= 0)  //En caso de que se ingrese un valor invalido
	{
		printf("Valor invalido, favor volver a intentarlo ingresando un valor valido\n");
		return 0;  //Sale de la funcion retornando cero y devolviendo al usuario al menu principal
	}
    //***************************************************************************

    //*********************** CREACION DEL ESTADO INICIAL ***********************
    Estado estadoInicial;
    estadoInicial.islaB = (int*)malloc(sizeof(int)*3);  //Asignamos la memoria para el nuevo vector de la isla B
    estadoInicial.islaB[0] = 0;  //Asiganmos los valores inciales del vector para la isla B
    estadoInicial.islaB[1] = 0;   //Asiganmos los valores inciales del vector para la isla B
    estadoInicial.islaB[2] = 0;  //Asiganmos los valores inciales del vector para la isla B
    
    estadoInicial.id = 0;
    estadoInicial.idAnterior = 0;
    //***************************************************************************

    abiertos = agregarEstado(abiertos, &cantidadAbiertos, estadoInicial);  //Agreagamos el estado incial a la lista de estados abiertos

    while (cantidadAbiertos > 0)  //Mientras queden estados por revisar dentro de la lista de estados abiertos
    {
        Estado estadoActual = extraerEstado(abiertos, &cantidadAbiertos);  //Extraemos el primer estado de la lista de estados abiertos
        cerrados = agregarEstado(cerrados, &cantidadCerrados, estadoActual);  //Agregamos el estado actual a la lista de estados cerrados

        //*************************************** COMENZAMOS A REALIZAR LOS MOVIMIENTOS ******************************************

        if (puedoCanibal(estadoActual, personas))  //Se verifica si se puede hacer el movimiento
        {
            Estado nuevoEstado = moverCanibal(estadoActual, idNuevoEstado);
            
            if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))  //Se verifica que no sea un estado ya creado
            {
                idNuevoEstado = idNuevoEstado + 1;

                if (esFinal(nuevoEstado, personas))  //Si es un estado final (0 peones), se agrega a la lista de soluciones
                {
                    soluciones = agregarEstado(soluciones, &cantidadSoluciones, nuevoEstado);
                }

                else
                {
                    abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);  //Si no es un estado final, se agrega a la lista de estados abiertos
                }
            }
        }

        if (puedoCanibales(estadoActual, personas))  //Se verifica si se puede hacer el movimiento
        {
            Estado nuevoEstado = moverCanibales(estadoActual, idNuevoEstado);
            
            if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))  //Se verifica que no sea un estado ya creado
            {
                idNuevoEstado = idNuevoEstado + 1;

                if (esFinal(nuevoEstado, personas))  //Si es un estado final (0 peones), se agrega a la lista de soluciones
                {
                    soluciones = agregarEstado(soluciones, &cantidadSoluciones, nuevoEstado);
                }

                else
                {
                    abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);  //Si no es un estado final, se agrega a la lista de estados abiertos
                }
            }
        }

        if (puedoMisionero(estadoActual, personas))  //Se verifica si se puede hacer el movimiento
        {
            Estado nuevoEstado = moverMisionero(estadoActual, idNuevoEstado);
            
            if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))  //Se verifica que no sea un estado ya creado
            {
                idNuevoEstado = idNuevoEstado + 1;
                
                if (esFinal(nuevoEstado, personas))  //Si es un estado final (0 peones), se agrega a la lista de soluciones
                {
                    soluciones = agregarEstado(soluciones, &cantidadSoluciones, nuevoEstado);
                }

                else
                {
                    abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);  //Si no es un estado final, se agrega a la lista de estados abiertos
                }
            }
        }

        if (puedoMisioneros(estadoActual, personas))  //Se verifica si se puede hacer el movimiento
        {
            Estado nuevoEstado = moverMisioneros(estadoActual, idNuevoEstado);
            
            if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))  //Se verifica que no sea un estado ya creado
            {
                idNuevoEstado = idNuevoEstado + 1;
                
                if (esFinal(nuevoEstado, personas))  //Si es un estado final (0 peones), se agrega a la lista de soluciones
                {
                    soluciones = agregarEstado(soluciones, &cantidadSoluciones, nuevoEstado);
                }

                else
                {
                    abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);  //Si no es un estado final, se agrega a la lista de estados abiertos
                }
            }
        }

        if (puedoMisioneroCanibal(estadoActual, personas))  //Se verifica si se puede hacer el movimiento
        {
            Estado nuevoEstado = moverMisioneroCanibal(estadoActual, idNuevoEstado);
            
            if (noEsta(abiertos, cantidadAbiertos, nuevoEstado) && noEsta(cerrados, cantidadCerrados, nuevoEstado))  //Se verifica que no sea un estado ya creado
            { 
                idNuevoEstado = idNuevoEstado + 1;
                
                if (esFinal(nuevoEstado, personas))  //Si es un estado final (0 peones), se agrega a la lista de soluciones
                {
                    soluciones = agregarEstado(soluciones, &cantidadSoluciones, nuevoEstado);
                }

                else
                {
                    abiertos = agregarEstado(abiertos, &cantidadAbiertos, nuevoEstado);  //Si no es un estado final, se agrega a la lista de estados abiertos
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
            imprimirSolucionesCanibales(soluciones[i], cerrados, cantidadCerrados);
            printf("\n");
        }
    }

    return 0;
}

//****************************************************************************************** CUADRADO MAGICO ******************************************************************************************

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
void imprimirSolucionesCuadrado (int *** listaSoluciones, int cantSoluciones)  //Recibe como argumentos la lista de soluciones (lista de matrices) y la cantidad de elementos que posee
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
int verificarColumnas (int a, int b, int c, int d, int e, int f, int g, int h, int i)  //Recibe como argumentos los 9 números que irán dentro del cuadrado magico
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
int verificarDiagonales (int a, int b, int c, int d, int e, int f, int g, int h, int i)  //Recibe como argumentos los 9 números que irán dentro del cuadrado magico
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

//Función que comprobará que no se repitan números dentro del cuadrado magico
int repetidos (int a, int b, int c, int d, int e, int f, int g, int h, int i)  //Recibe como argumentos los 9 números que irán dentro del cuadrado magico
{
    //Mediante multiples sentecias if anidadas se comprobará que no se repita ningun número dentro del cuadrado magico
    if (a != b && a != c && a != d && a != e && a != f  && a != g && a != h && a != i)
    {
        if (b != c && b != d && b != e && b != f && b != g && b != h && b != i)
        {
            if (c != d && c != e && c != f && c != g && c != h && c != i)
            {
                if (d != e && d != f && d != g && d != h && d != i)
                {
                    if (e != f && e != g && e != h && e != i)
                    {
                        if (f != g && f != h && f != i)
                        {
                            if (g != h && g != i)
                            {
                                if (h != i)
                                {
                                    return 1;  //Retorna 1 indicando que no se repite ningun número dentro del cuadrado magico
                                }

                                else
                                {
                                    return 0;  //Retorna 0 indicando que se repite algun número dentro del cuadrado magico
                                } 
                            }

                            else
                            {
                                return 0;  //Retorna 0 indicando que se repite algun número dentro del cuadrado magico
                            } 
                        }

                        else
                        {
                            return 0;  //Retorna 0 indicando que se repite algun número dentro del cuadrado magico
                        } 
                        
                    }

                    else
                    {
                        return 0;  //Retorna 0 indicando que se repite algun número dentro del cuadrado magico
                    } 
                }

                else
                {
                    return 0;  //Retorna 0 indicando que se repite algun número dentro del cuadrado magico
                } 
                
            }

            else
            {
                return 0;  //Retorna 0 indicando que se repite algun número dentro del cuadrado magico
            } 
        }

        else
        {
            return 0;  //Retorna 0 indicando que se repite algun número dentro del cuadrado magico
        } 
    }

    else
    {
        return 0;  //Retorna 0 indicando que se repite algun número dentro del cuadrado magico
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

int cuadradoMagico ()
{
	int cantidadSoluciones = 0;  //Variable para almacenar la cantidad de soluciones al problema
    int *** listaSoluciones = (int ***)malloc(sizeof(int**)*cantidadSoluciones);  //Se crea la lista de soluciones y se asigna la memoria para ella

    //*********************** INGRESO DEL VALOR MAXIMO POR PARTE DEL USUARIO ***********************
    int valorMaximo;  //Variable para almacenar el valor maximo que podrán tener los elementos del cuadrado
    printf("Ingrese el numero maximo que pueden tener los elementos del cuadrado: ");
    scanf("%d", &valorMaximo);
    printf("\n");

	if (valorMaximo <= 0)  //En caso de que se ingrese un valor invalido
	{
		printf("Valor invalido, favor volver a intentarlo ingresando un valor valido\n");
		return 0;  //Sale de la funcion retornando cero y devolviendo al usuario al menu principal
	}
    //**********************************************************************************************

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
                                        if (repetidos(a, b, c, d, e, f, g, h, i))
                                        {
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
        printf("No existen soluciones\n");
        free(listaSoluciones);  //Se libera la memoria utilizada por la lista de soluciones
        return 0;  //Se sale de la función retornando cero
    }
    
    else
    {
        imprimirSolucionesCuadrado(listaSoluciones, cantidadSoluciones);  //Se imprimen las soluciones restantes luego de filtrarlas
        free(listaSoluciones);  //Se libera la memoria utilizada por la lista de soluciones
        return 0;  //Se sale de la función retornando cero
    } 
}

//********************************************** MENU PRINCIPAL *****************************************************************
//Funcion encargada de mostrar el menu del programa y ejecutar las distintas opciones de este, no recibe argumentos al momento de ser llamada.
int menu()
{
	int eleccion;  //Variable para almacenar la opcion ingresada por el usuario

	while(1)  //Se crea una tautologia para que el menu sea mostrado mientras no se salga de la funcion al ingresar la opcion 3
	{
		// Se muestran las opciones la usuario
		printf("\n");
		printf("1) Canibales y misioneros\n2) Cuadrado Magico\n3) Salir\n");
		printf("Ingrese una opcion: ");
		scanf("%d", &eleccion);  //Se lee la opcion ingresada por el usuario y se almacena en la variable previamente creada
		printf("\n");

		if (eleccion == 1)
		{
			canibales();  //Se llama a la funcion que ejecuta el problema de los canibales y los misioneros
		}
		else if (eleccion == 2)
		{
			cuadradoMagico();  //Se llama a la funcion que ejecuta el problema del cuadrado magico
		}
		else if (eleccion == 3)
		{
			return 0;  //Se sale de la funcion terminando el probrama
		}
		else
		{
			printf("Opccion invalida\n");  //En caso de que el usuario ingrese una opcion invalida
		}
	}
}

//********************************************** EJECUCIÓN DEL PROGRAMA *****************************************************************
int main()
{
	menu();

	return 0;
}