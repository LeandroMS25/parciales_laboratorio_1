/*
 * Cliente.c
 *
 *  Created on: 21 nov. 2020
 *      Author: Leandro Sobrino
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validaciones.h"
#include "Cliente.h"
/**
 * \brief Crea un nuevo cliente.
 * \return devuelve un puntero al espacio de memoria del cliente.
 */
Cliente* cliente_new(void)
{
	return (Cliente*)malloc(sizeof(Cliente));
}
/**
 * \brief Crea un nuevo envío.
 * \param char* idCliente, id del cliente.
 * \param char* nombre, recibe el nombre del cliente.
 * \param char* apellido, recibe el apellido del cliente.
 * \param char* cuit, recibe cuit del cliente.
 * \return devuelve un puntero al espacio de memoria del cliente.
 */
Cliente* cliente_newParam(char* idCliente, char* nombre, char* apellido, char* cuit)
{
	Cliente* this = cliente_new();
	if(this != NULL && idCliente != NULL &&	nombre != NULL && apellido != NULL && cuit != NULL
		&& isNumberInt(idCliente, SIZE_STR))
	{
		if(!(cliente_allSets(this, atoi(idCliente), nombre, apellido, cuit)))
		{
			return this;
		}
	}
	return this;
}
/*
 * \brief Borra un cliente (libera el espacio de memoria).
 * \param Cliente* this, Es el puntero al espacio de memoria del cliente.
 */
void cliente_delete(Cliente* this)
{
	if (this != NULL)
	{
		free(this);
	}
}
/**
 * \brief Lee el id del cliente.
 * \param Cliente* this, Es el puntero al array.
 * \param int* idCliente, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int cliente_getIdCliente(Cliente* this, int* idCliente)
{
	int retorno = -1;
	if(this != NULL)
	{
		*idCliente = this->idCliente;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Escribe el id del cliente.
 * \param Cliente* this, Es el puntero al array.
 * \param int idCliente, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */

int cliente_setIdCliente(Cliente* this, int idCliente)
{
	int retorno = -1;
	if(this != NULL && idCliente > 0)
	{
		this->idCliente = idCliente;
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Lee un nombre de cliente.
 * \param Cliente* this, Es el puntero al array.
 * \param char* nombre, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int cliente_getNombre(Cliente* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL)
	{
		strncpy(nombre,this->nombre,(int)sizeof(this->nombre));
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Escribe un nombre de cliente.
 * \param Cliente* this, Es el puntero al array.
 * \param char* nombre, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int cliente_setNombre(Cliente* this, char* nombre)
{
	int retorno = -1;
	if(this != NULL && isName(nombre, SIZE_STR))
	{
		strncpy(this->nombre,nombre,(int)sizeof(this->nombre));
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Lee un apellido de cliente.
 * \param Cliente* this, Es el puntero al array.
 * \param char* apellido, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int cliente_getApellido(Cliente* this, char* apellido)
{
	int retorno = -1;
	if(this != NULL)
	{
		strncpy(apellido,this->apellido,(int)sizeof(this->apellido));
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Escribe un apellido de cliente.
 * \param Cliente* this, Es el puntero al array.
 * \param char* apellido, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int cliente_setApellido(Cliente* this, char* apellido)
{
	int retorno = -1;
	if(this != NULL && isName(apellido, SIZE_STR))
	{
		strncpy(this->apellido,apellido,(int)sizeof(this->apellido));
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Lee un cuit de cliente.
 * \param Cliente* this, Es el puntero al array.
 * \param char* cuit, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int cliente_getCuit(Cliente* this, char* cuit)
{
	int retorno = -1;
	if(this != NULL)
	{
		strncpy(cuit,this->cuit,(int)sizeof(this->cuit));
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Escribe un cuit de cliente.
 * \param Cliente* this, Es el puntero al array.
 * \param char* cuit, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int cliente_setCuit(Cliente* this, char* cuit)
{
	int retorno = -1;
	if(this != NULL && isCuit(cuit, SIZE_STR))
	{
		strncpy(this->cuit,cuit,(int)sizeof(this->cuit));
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Escribe los datos recibidos.
 * \param Cliente* this, Es el puntero al array.
 * \param int idCliente, recibe el id.
 * \param char* nombre, recibe un nombre.
 * \param char* apellido, recibe la zona de destino.
 * \param char* cuit, recibe un cuit.
 * \return (-1) Error / (0) Ok
 */
int cliente_allSets(Cliente* this, int idCliente, char* nombre, char* apellido, char* cuit)
{
	int retorno = -1;

	if(this != NULL)
	{
		cliente_setIdCliente(this, idCliente);
		cliente_setNombre(this, nombre);
		cliente_setApellido(this, apellido);
		cliente_setCuit(this, cuit);
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Lee los datos.
 * \param Cliente* this, Es el puntero al array.
 * \param int* idCliente, Puntero al espacio de memoria.
 * \param char* nombre, Puntero al espacio de memoria.
 * \param char* apellido, Puntero al espacio de memoria.
 * \param char* cuit, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int cliente_allGets(Cliente* this, int* idCliente, char* nombre, char* apellido, char* cuit)
{
	int retorno = -1;

	if(this != NULL)
	{
		cliente_getIdCliente(this, idCliente);
		cliente_getNombre(this, nombre);
		cliente_getApellido(this, apellido);
		cliente_getCuit(this, cuit);
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Función criterio para imprimir cada elemento de la lista.
 * \param void* pElement, Es el puntero al elemento.
 * \return (-1) Error / (0) Ok
 */
void cliente_imprimir(void* pElement)
{
	int auxIdCliente;
	char auxNombre[SIZE_STR];
	char auxApellido[SIZE_STR];
	char auxCuit[SIZE_STR];
	Cliente* auxCliente = (Cliente*)pElement;
	if(!(cliente_allGets(auxCliente, &auxIdCliente, auxNombre, auxApellido, auxCuit)))
	{
		printf("ID Cliente: %03d | Nombre: %-10s | Apellido: %-11s | Cuit: %-10s\n",
				auxIdCliente,auxNombre,auxApellido,auxCuit);
	}
}
/**
 * \brief Encuentra el id maximo de la linkedlist.
 * \param LinkedList* pArrayListCliente, Es el puntero al array.
 * \param int* pMaxId, puntero al espacio de memmoria donde se encuentra el id maximo.
 * \return (-1) Error / (0) Ok
 */
int cliente_findMaxId(LinkedList* pArrayListCliente, int* pMaxId)
{
	int retorno = -1;
	Cliente* auxCliente = cliente_new();
	int len = ll_len(pArrayListCliente);
	int bufferId;
	int i;

	if(pArrayListCliente != NULL && pMaxId != NULL && auxCliente != NULL)
	{
		for (i = 0; i < len; i++)
		{
			auxCliente = ll_get(pArrayListCliente, i);
			cliente_getIdCliente(auxCliente, &bufferId);
			if(i == 0 || bufferId >= *pMaxId)
			{
				*pMaxId = bufferId+1;
			}
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Recibe un cuit y chequea si ya existe un cliente con el mismo cuit en la lista.
 * \param LinkedList* pArrayListCliente, Es el puntero al array.
 * \param char* cuit, cuit recibido para comparar.
 * \return (-1) Error / (0) Ok
 */
int cliente_findCuitRepetido(LinkedList* pArrayListCliente, char* cuit)
{
	int retorno = 0;
	Cliente* auxCliente;
	int len = ll_len(pArrayListCliente);
	char auxCuit[SIZE_STR];

	if(pArrayListCliente != NULL && cuit != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			auxCliente = ll_get(pArrayListCliente, i);
			cliente_getCuit(auxCliente, auxCuit);
			if(strncmp(auxCuit,cuit,SIZE_STR) == 0)
			{
				retorno = 1;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Recibe un id y chequea si el cliente se encuentra en la lista.
 * \param LinkedList* pArrayListCliente, Es el puntero al array.
 * \param int id, id recibido para comparar.
 * \return (-1) Error / (0) Ok
 */
int cliente_findClient(LinkedList* pArrayListCliente, int id)
{
	int retorno = 0;
	Cliente* auxCliente;
	int len = ll_len(pArrayListCliente);
	int auxId;

	if(pArrayListCliente != NULL && id > 0)
	{
		for (int i = 0; i < len; i++)
		{
			auxCliente = ll_get(pArrayListCliente, i);
			cliente_getIdCliente(auxCliente, &auxId);
			if(auxId == id)
			{
				retorno = 1;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Recibe un id, chequea si el cliente se encuentra en la lista y devuelve el indice.
 * \param LinkedList* pArrayListCliente, Es el puntero al array.
 * \param int id, id recibido para comparar.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int cliente_findIndexById(LinkedList* pArrayListCliente, int id, int* pIndex)
{
	int retorno = 0;
	Cliente* auxCliente;
	int len = ll_len(pArrayListCliente);
	int auxId;

	if(pArrayListCliente != NULL && id > 0)
	{
		for (int i = 0; i < len; i++)
		{
			auxCliente = ll_get(pArrayListCliente, i);
			cliente_getIdCliente(auxCliente, &auxId);
			if(auxId == id)
			{
				*pIndex = i;
				retorno = 1;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Recibe un id, chequea si se encuentra en la lista e imprime el cliente.
 * \param LinkedList* pArrayListCliente, Es el puntero al array.
 * \param int id, id recibido para comparar.
 * \return (-1) Error / (0) Ok
 */
int cliente_findIdAndPrint(LinkedList* pArrayListCliente, int id)
{
	int retorno = 0;
	Cliente* auxCliente;
	int len = ll_len(pArrayListCliente);
	int auxId;
	char auxNombre[SIZE_STR];
	char auxApellido[SIZE_STR];
	char auxCuit[SIZE_STR];

	if(pArrayListCliente != NULL && id > 0)
	{
		for (int i = 0; i < len; i++)
		{
			auxCliente = ll_get(pArrayListCliente, i);
			if(!(cliente_allGets(auxCliente, &auxId, auxNombre, auxApellido, auxCuit)) && auxId == id)
			{
				printf("Nombre: %-10s | Apellido: %-11s | Cuit: %-10s\n", auxNombre, auxApellido, auxCuit);
				retorno = 1;
				break;
			}
		}
	}
	return retorno;
}
