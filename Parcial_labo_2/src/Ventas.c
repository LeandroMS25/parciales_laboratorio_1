/*
 * Ventas.c
 *
 *  Created on: 21 nov. 2020
 *      Author: Leandro Sobrino
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validaciones.h"
#include "Ventas.h"
#include "LinkedList.h"
#include "Controller.h"

Ventas* ventas_new(void)
{
	return (Ventas*)malloc(sizeof(Ventas));
}

Ventas* ventas_newParam(char* idVentas, char* cantAfiches, char* nombreArchivo, char* zona,char* estado,char* idCliente)
{
	Ventas* this = ventas_new();
	if(this != NULL && idVentas != NULL && cantAfiches != NULL && nombreArchivo != NULL && zona != NULL && idCliente != NULL &&
		estado != NULL && isNumberInt(idVentas, SIZE_STR) && isNumberInt(cantAfiches, SIZE_STR) && isNumberInt(zona, SIZE_STR) &&
		isNumberInt(estado, SIZE_STR) && isNumberInt(idCliente, SIZE_STR))
	{
		if(!(ventas_allSets(this, atoi(idVentas), atoi(cantAfiches), nombreArchivo, atoi(zona), atoi(estado), atoi(idCliente))))
		{
			return this;
		}
	}
	return this;
}

void ventas_delete(Ventas* this)
{
	if (this != NULL)
	{
		free(this);
	}
}

int ventas_getIdVentas(Ventas* this, int* idVentas)
{
	int retorno = -1;
	if(this != NULL)
	{
		*idVentas = this->idVentas;
		retorno = 0;
	}
	return retorno;
}


int ventas_setIdVentas(Ventas* this, int idVentas)
{
	int retorno = -1;
	if(this != NULL && idVentas > 0)
	{
		this->idVentas = idVentas;
		retorno = 0;
	}
	return retorno;
}

int ventas_getCantAfiches(Ventas* this, int* cantAfiches)
{
	int retorno = -1;
	if(this != NULL)
	{
		*cantAfiches = this->cantAfiches;
		retorno = 0;
	}
	return retorno;
}

int ventas_setCantAfiches(Ventas* this, int cantAfiches)
{
	int retorno = -1;
	if(this != NULL && cantAfiches > 0)
	{
		this->cantAfiches = cantAfiches;
		retorno = 0;
	}
	return retorno;
}

int ventas_getNombreArchivo(Ventas* this, char* nombreArchivo)
{
	int retorno = -1;
	if(this != NULL)
	{
		strncpy(nombreArchivo,this->nombreArchivo,(int)sizeof(this->nombreArchivo));
		retorno = 0;
	}
	return retorno;
}

int ventas_setNombreArchivo(Ventas* this, char* nombreArchivo)
{
	int retorno = -1;
	if(this != NULL && isName(nombreArchivo, SIZE_STR))
	{
		strncpy(this->nombreArchivo,nombreArchivo,(int)sizeof(this->nombreArchivo));
		retorno = 0;
	}
	return retorno;
}

int ventas_getZona(Ventas* this, int* zona)
{
	int retorno = -1;
	if(this != NULL)
	{
		*zona = this->zona;
		retorno = 0;
	}
	return retorno;
}

int ventas_setZona(Ventas* this, int zona)
{
	int retorno = -1;
	if(this != NULL && zona >= 0)
	{
		this->zona = zona;
		retorno = 0;
	}
	return retorno;
}

int ventas_getIdCliente(Ventas* this, int* idCliente)
{
	int retorno = -1;
	if(this != NULL)
	{
		*idCliente = this->idCliente;
		retorno = 0;
	}
	return retorno;
}

int ventas_setIdCliente(Ventas* this, int idCliente)
{
	int retorno = -1;
	if(this != NULL && idCliente > 0)
	{
		this->idCliente = idCliente;
		retorno = 0;
	}
	return retorno;
}

int ventas_getEstado(Ventas* this, int* estado)
{
	int retorno = -1;
	if(this != NULL)
	{
		*estado = this->estado;
		retorno = 0;
	}
	return retorno;
}

int ventas_setEstado(Ventas* this, int estado)
{
	int retorno = -1;
	if(this != NULL && estado >= 0)
	{
		this->estado = estado;
		retorno = 0;
	}
	return retorno;
}

int ventas_allSets(Ventas* this, int idVentas, int cantAfiches, char* nombreArchivo, int zona, int estado, int idCliente)
{
	int retorno = -1;

	if(this != NULL)
	{
		ventas_setIdVentas(this, idVentas);
		ventas_setCantAfiches(this, cantAfiches);
		ventas_setNombreArchivo(this, nombreArchivo);
		ventas_setZona(this, zona);
		ventas_setEstado(this, estado);
		ventas_setIdCliente(this, idCliente);
		retorno = 0;
	}
	return retorno;
}

int ventas_allGets(Ventas* this, int* idVentas, int* cantAfiches, char* nombreArchivo, int* zona, int* estado, int* idCliente)
{
	int retorno = -1;

	if(this != NULL)
	{
		ventas_getIdVentas(this, idVentas);
		ventas_getCantAfiches(this, cantAfiches);
		ventas_getNombreArchivo(this, nombreArchivo);
		ventas_getZona(this, zona);
		ventas_getEstado(this, estado);
		ventas_getIdCliente(this, idCliente);
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Función criterio para imprimir cada elemento de la lista.
 * \param void* pElement, Es el puntero al elemento.
 * \return (-1) Error / (0) Ok
 */
void ventas_imprimir(void* pElement)
{
	int auxIdVentas;
	int auxCantAfiches;
	char auxNombreArchivo[SIZE_STR];
	int auxZona;
	int	auxEstado;
	int auxIdCliente;
	Ventas* auxVenta = (Ventas*)pElement;
	if(!(ventas_allGets(auxVenta, &auxIdVentas, &auxCantAfiches, auxNombreArchivo, &auxZona, &auxEstado,&auxIdCliente)))
	{
		printf("ID Venta: %03d | Afiches: %-10d | Nombre Archivo: %-11s | Zona: %-2d | Estado: %-2d | ID Cliente: %-2d\n",
						auxIdVentas,auxCantAfiches,auxNombreArchivo,auxZona,auxEstado,auxIdCliente);
	}
}
/**
 * \brief Función criterio para imprimir cada elemento de la lista.
 * \param void* pElement, Es el puntero al elemento.
 * \return (-1) Error / (0) Ok
 */
void ventas_imprimirSinCobrar(void* pElement)
{
	int auxIdVentas;
	int auxCantAfiches;
	char auxNombreArchivo[SIZE_STR];
	int auxZona;
	int	auxEstado;
	int auxIdCliente;
	Ventas* auxVenta = (Ventas*)pElement;
	if(!(ventas_allGets(auxVenta, &auxIdVentas, &auxCantAfiches, auxNombreArchivo, &auxZona, &auxEstado,&auxIdCliente)))
	{
		if(auxEstado == 0)
		{
			printf("ID Venta: %03d | Afiches: %-10d | Nombre Archivo: %-11s | Zona: %-2d | Estado: %-2d | ID Cliente: %-2d\n",
									auxIdVentas,auxCantAfiches,auxNombreArchivo,auxZona,auxEstado,auxIdCliente);
		}
	}
}
/**
 * \brief Encuentra el id maximo de la linkedlist.
 * \param LinkedList* pArrayListVentas, Es el puntero al array.
 * \param int* pMaxId, puntero al espacio de memmoria donde se encuentra el id maximo.
 * \return (-1) Error / (0) Ok
 */
int ventas_findMaxId(LinkedList* pArrayListVentas, int* pMaxId)
{
	int retorno = -1;
	Ventas* auxVenta = ventas_new();
	int len = ll_len(pArrayListVentas);
	int bufferId;

	if(pArrayListVentas != NULL && pMaxId != NULL && auxVenta != NULL && len >= 0)
	{
		for (int i = 0; i < len; i++)
		{
			auxVenta = ll_get(pArrayListVentas, i);
			ventas_getIdVentas(auxVenta, &bufferId);
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
 * \brief Recibe un id y chequea si se encuentra en la lista y si la venta esta sin cobrar.
 * \param LinkedList* pArrayListVentas, Es el puntero al array.
 * \param int id, id recibido para comparar.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int ventas_findIndexById(LinkedList* pArrayListVentas, int id, int estado, int* pIndex)
{
	int retorno = -1;
	Ventas* auxVenta;
	int len = ll_len(pArrayListVentas);
	int auxId;
	int auxEstado;

	if(pArrayListVentas != NULL && id > 0)
	{
		for (int i = 0; i < len; i++)
		{
			auxVenta = ll_get(pArrayListVentas, i);
			ventas_getIdVentas(auxVenta, &auxId);
			ventas_getEstado(auxVenta, &auxEstado);
			if(auxEstado == estado && auxId == id)
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
 * \brief Recibe un id y chequea si se encuentra en la lista.
 * \param LinkedList* pArrayListCliente, Es el puntero al array.
 * \param int id, id recibido para comparar.
 * \return (-1) Error / (0) Ok
 */
int ventas_calcularVentasCobradasOrAdeudadas(void* pElement, void* arg)
{
	int retorno = 0;
	Ventas* auxVenta = (Ventas*) pElement;
	ArgumentosFiltro* pArg = (ArgumentosFiltro*) arg;
	int auxId, auxEstado;

	if(auxVenta != NULL)
	{
		ventas_getIdCliente(auxVenta, &auxId);
		ventas_getEstado(auxVenta, &auxEstado);
		if(auxEstado == pArg->estado && auxId == pArg->id)
		{
			retorno = 1;
		}
	}
	return retorno;
}
/**
 * \brief Recibe un id y chequea si se encuentra en la lista.
 * \param LinkedList* pArrayListCliente, Es el puntero al array.
 * \param int id, id recibido para comparar.
 * \return (-1) Error / (0) Ok
 */
int ventas_calcularCantidadAfiches(void* pElement, void* id)
{
	int retorno = 0;
	Ventas* auxVenta = (Ventas*) pElement;
	int* pId = (int*) id;
	int auxId, auxEstado, auxCant;

	if(auxVenta != NULL)
	{
		ventas_getIdCliente(auxVenta, &auxId);
		ventas_getEstado(auxVenta, &auxEstado);
		ventas_getCantAfiches(auxVenta, &auxCant);
		if(auxEstado == 1 && auxId == *pId)
		{
			retorno = auxCant;
		}
	}
	return retorno;
}
