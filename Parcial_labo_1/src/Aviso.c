/*
 * Aviso.c
 * Author: Leandro Sobrino
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include "Aviso.h"
#include "Cliente.h"
#include "validaciones.h"

static int generateNewId(void);
/**
 * \brief Inicializa el array .
 * \param Aviso list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int avi_init(Aviso* list, int len)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			list[i].isEmpty = 1;
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Realiza el alta solo si el indice corresponde a un espacio vacio (isEmpty == 0)
 * \param Aviso* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \param int id, indica el id del elemento.
 * \return (-1) Error / (0) Ok
 */
int avi_add(Aviso* list, int len, Cliente* listCliente, int lenCliente)
{
	int retorno = -1;
	int index;
	int idCliente;
	int indexCliente;
	Aviso buffer;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
	{
		cli_print(listCliente, lenCliente);
		if( utn_getNumberInt(&idCliente, "Ingrese el id del cliente que publicara el aviso: ", "\nError.", 1, INT_MAX, 2) == 0 &&
			cli_findById(listCliente, lenCliente, idCliente, &indexCliente) == 0 &&
			avi_findFree(list, len, &index) == 0 && index < len &&
			utn_getNumberInt(&buffer.rubro, "Ingrese el rubro del aviso: ", "\nError.", 1, QTY_AVI, 2) == 0 &&
			utn_getName(buffer.text, "Ingrese el texto que desea publicar: ", "\nError.", 2, LONG_TEXTO) == 0)
		{
			buffer.isEmpty = 0;
			buffer.estado = ACTIVO;
			buffer.idAviso = generateNewId();
			list[index] = buffer;
			list[index].idCliente = listCliente[indexCliente].id;
			avi_show(list, index);
			retorno = 0;
		}
		else
		{
			printf("El id seleccionado no existe.\n");
		}
	}
	return retorno;
}
/**
 * \brief Modifica datos si el indice no est� vacio.
 * \param Aviso* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int avi_modify(Aviso* list, int len, Cliente* listCliente, int lenCliente)
{
	int retorno = -1;
	// Aviso buffer;
	int idModify;
	int indexModify;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
	{
		if( utn_getNumberInt(&idModify, "Ingrese el id de la publicidad que quiere modificar: ", "\nError.", 1, INT_MAX, 2) == 0 &&
			avi_findById(list, len, idModify, &indexModify) == 0)
		{
			retorno = 0;
		}
		else
		{
			printf("El id ingresado no pertenece a una Aviso.\n");
		}
	}
	return retorno;
}
/**
 * \brief Busca el elemento por id y se guarda su indice en un puntero.
 * \param Aviso list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int id, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return Retorna el indice
 */
int avi_findById(Aviso* list, int len, int id, int* pIndex)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0 && pIndex != NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idAviso == id)
			{
				*pIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Elimina el elemento que de encuentra en el indice recibido.
 * \param Aviso* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int avi_remove(Aviso* list, int len, Cliente* listCliente, int lenCliente)
{
	int retorno = -1;
	// Aviso buffer;
	int idRemove;
	int indexRemove;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
	{
		if( utn_getNumberInt(&idRemove, "Ingrese el id de la publicidad que quiere modificar: ", "\nError.", 1, INT_MAX, 2) == 0 &&
			avi_findById(list, len, idRemove, &indexRemove) == 0 )
		{
			list[indexRemove].isEmpty = 1;
			retorno = 0;
		}
	}
	return retorno;
}
/*
 * \ brief - Ordena el array por nombre.
 * \ param - Aviso* list, recibe el array a utilizar.
 * \ param - int len, indica la longitud del array.
 * \ param - int order, indica el orden de los elementos. 1 en caso de ascendente y 0 en caso de descendente.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int avi_sortByRubro(Aviso* list, int len, int order)
{
	int retorno = -1;
	int i;
	Aviso aux;
	int flagSwap = 1;
	if(list != NULL && len > 0)
	{
		while(flagSwap)
		{
			flagSwap = 0;
			for (i = 0; i < (len - 1); i++)
			{
				if(1)

				{
					aux = list[i];
					list[i] = list[i+1];
					list[i+1] = aux;
					flagSwap = 1;
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Imprime los datos cargados.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int avi_print(Aviso* list, int len, Cliente* listCliente, int lenCliente)
{
	int retorno = -1;
	int auxIndex;
	int i;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && cli_findById(listCliente, lenCliente, list[i].idCliente, &auxIndex) == 0)
			{
				printf("ID del cliente: %d - Nombre y apellido del cliente: %s %s - ID del aviso: %d  - Texto: %s - Rubro: %d.\n",
						list[i].idCliente, listCliente[auxIndex].name, listCliente[auxIndex].lastName, list[i].idAviso, list[i].text, list[i].rubro);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Muestra un elemento del array por el indice recibido.
 * \param Cliente* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int index, recibe un indice del array.
 * \return (-1) Error / (0) Ok
 */
int avi_show(Aviso* list,int index)
{
	int retorno = -1;

	if(list != NULL && index >= 0 )
	{
		if(list[index].isEmpty==0)
		{
			printf("ID del cliente: %d - ID del aviso: %d  - Texto: %s - Rubro: %d.\n",
					list[index].idCliente, list[index].idAviso, list[index].text, list[index].rubro);
			retorno = 0;
		}
		else
		{
			printf("El aviso no existe.");
		}
	}
	return retorno;
}
/**
 * \brief Busca un espacio libre en el array.
 * \param Aviso* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int avi_findFree(Aviso* list, int len, int* pIndex)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0 && pIndex!= NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 1)
			{
				*pIndex = i;
				retorno = 0;
				break;
			}
			else
			{
				printf("No hay espacios libres para dar de alta.");
			}
		}
	}
	return retorno;
}
/**
 * \brief Busca un espacio ocupado en el array.
 * \param Aviso* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int avi_findOccupied(Aviso* list, int len)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Imprime los avisos activos o pausados.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \param int state, indica el estado de los avisos.
 * \return (-1) Error / (0) Ok
 */
int avi_mostrarAvisosPausadosOActivos(Aviso* list, int len, Cliente* listCliente, int lenCliente, int state)
{
    int retorno = -1;

    if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0 && (state >= 0 || state <= 1))
    {
        for(int i=0;i<len;i++)
        {
            if(list[i].isEmpty == 0 && list[i].estado == state)
            {
            	avi_show(list, i);
                retorno = 0;
            }
        }
    }
    return retorno;
}
/**
 * \brief Cambia el estado del aviso a pausado o activo segun corresponda.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \param int state, indica el estado de los avisos.
 * \return (-1) Error / (0) Ok
 */
int avi_changeState(Aviso* list, int len, Cliente* listCliente, int lenCliente, int state)
{
	int retorno = -1;
	int idChange;
	int indexChange;
	int indexCliente;
	int respuesta;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0 && (state >= 0 || state <= 1))
	{
		avi_mostrarAvisosPausadosOActivos(list, len, listCliente, lenCliente, !state);
		if( ((state == 1 && utn_getNumberInt(&idChange, "Ingrese el id del aviso que quiere reanudar: ", "\nError.", 1, INT_MAX, 2) == 0 &&
			avi_findById(list, len, idChange, &indexChange) == 0 && cli_findById(listCliente, lenCliente, list[indexChange].idCliente, &indexCliente) == 0 &&
			cli_show(listCliente, indexCliente) == 0) ||
			(state == 0 && utn_getNumberInt(&idChange, "Ingrese el id del aviso que quiere pausar: ", "\nError.", 1, INT_MAX, 2) == 0 &&
			avi_findById(list, len, idChange, &indexChange) == 0 && cli_findById(listCliente, lenCliente, list[indexChange].idCliente, &indexCliente) == 0 &&
			cli_show(listCliente, indexCliente) == 0)) &&
			utn_getNumberInt(&respuesta, "�Desea cambiar el estado del aviso? (1- Si. / 2- No.)", "\nError.", SI, NO, 2) == 0)
		{
			if(respuesta == 1)
			{
				list[indexChange].estado = state;
				retorno = 0;
			}
			else
			{
				printf("Se cancelo el cambio de estado del aviso.\n");
			}
		}
	}
	return retorno;
}
/**
 * \brief Incrementa el id y lo retorna.
 * \return Retorna el id
 */
static int generateNewId(void)
{
	static int id = 0;

	id++;
	return id;
}
