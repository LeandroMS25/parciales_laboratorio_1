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
/**
 * \brief Crea una nueva venta.
 * \return devuelve un puntero al espacio de memoria del cliente.
 */
Ventas* ventas_new(void)
{
	return (Ventas*)malloc(sizeof(Ventas));
}
/**
 * \brief Crea una nueva venta.
 * \param char* idVentas, id del producto.
 * \param char* nombreArchivo, recibe el nombre del producto.
 * \param char* idCliente, id del camion.
 * \param char* zona, recibe la zona de destino del producto.
 * \param char* cantAfiches, recibe lo km del envio.
 * \param char* estado, recibe el tipo de entrega del envío.
 * \return devuelve un puntero al espacio de memoria del cliente.
 */
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
/*
 * \brief Borra una venta(libera el espacio de memoria).
 * \param Ventas* this, Es el puntero al espacio de memoria del envio.
 */
void ventas_delete(Ventas* this)
{
	if (this != NULL)
	{
		free(this);
	}
}
/**
 * \brief Lee el id de la venta.
 * \param Ventas* this, Es el puntero al array.
 * \param int* idVentas, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Escribe el id de la venta.
 * \param Ventas* this, Es el puntero al array.
 * \param int idVentas, recibe el id de ventas.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Lee la cantidad de afiches recibida.
 * \param Ventas* this, Es el puntero al array.
 * \param int* cantAfiches, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Escribe la cantidad de afiches.
 * \param Envio* this, Es el puntero al array.
 * \param int cantAfiches, recibe la cantidad de afiches.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Lee el nombre del archivo.
 * \param Ventas* this, Es el puntero al array.
 * \param char* nombreArchivo, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Escribe el nombre del archivo.
 * \param Ventas* this, Es el puntero al array.
 * \param char* nombreArchivo, recibe el nombre del archivo.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Lee la zona donde se publican los afiches.
 * \param Ventas* this, Es el puntero al array.
 * \param int* zona, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Escribe la zona donde se publican los afiches.
 * \param Ventas* this, Es el puntero al array.
 * \param int zona, recibe la zona.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Lee el id del cliente.
 * \param Ventas* this, Es el puntero al array.
 * \param int* idCliente, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Escribe el id del cliente.
 * \param Ventas* this, Es el puntero al array.
 * \param int idCliente, recibe el id del cliente.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Lee el estado de la venta.
 * \param Ventas* this, Es el puntero al array.
 * \param int* estado, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Escribe el estado de la venta.
 * \param Ventas* this, Es el puntero al array.
 * \param int estado, recibe el estado de la venta.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Escribe los datos recibidos.
 * \param Ventas* this, Es el puntero al array.
 * \param int idVentas, recibe el id.
 * \param int idCliente, recibe el id.
 * \param char* nombreArchivo, recibe un nombre.
 * \param int zona, recibe la zona
 * \param int cantAfiches, recibe la cantidad de afiches.
 * \param int estado, recibe el estado de la venta.
 * \return (-1) Error / (0) Ok
 */
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
/**
 * \brief Lee los datos.
 * \param Ventas* this, Es el puntero al array.
 * \param int* idVentas, Puntero al espacio de memoria.
 * \param int* idCliente, Puntero al espacio de memoria.
 * \param char* idCliente, Puntero al espacio de memoria.
 * \param int* zona, Puntero al espacio de memoria.
 * \param int* cantAfiches, Puntero al espacio de memoria.
 * \param int* estado, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
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
 * \brief Función criterio para imprimir solo las ventas sin cobrar.
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
 * \param int estado, recibe el estado de la venta.
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
 * \brief Funcion criterio que devuelve la cantidad de ventas cobradas o adeudadas.
 * \param void* pElement, Es el puntero al espacio de memoria.
 * \param void* arg, Es el puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int ventas_calcularVentasCobradasOrAdeudadas(void* pElement, void* arg)
{
	int retorno = 0;
	Ventas* auxVenta = (Ventas*) pElement;
	//ArgumentosFiltro* pArg = (ArgumentosFiltro*) arg;
	int* pId = (int*) arg;
	int auxId/*, auxEstado*/;

	if(auxVenta != NULL)
	{
		ventas_getIdCliente(auxVenta, &auxId);
		//ventas_getEstado(auxVenta, &auxEstado);
		if(auxId == *pId)
		{
			retorno = 1;
		}
	}
	return retorno;
}
/**
 * \brief Funcion criterio que devuelve la cantidad de afiches vendidos.
 * \param void* pElement, Es el puntero al espacio de memoria.
 * \param id* arg, Es el puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int ventas_calcularCantidadAfiches(void* pElement, void* id)
{
	int retorno = 0;
	Ventas* auxVenta = (Ventas*) pElement;
	int* pId = (int*) id;
	int auxId/*, auxEstado*/, auxCant;

	if(auxVenta != NULL)
	{
		ventas_getIdCliente(auxVenta, &auxId);
		//ventas_getEstado(auxVenta, &auxEstado);
		ventas_getCantAfiches(auxVenta, &auxCant);
		if(/*auxEstado == 1 &&*/ auxId == *pId)
		{
			retorno = auxCant;
		}
	}
	return retorno;
}
/**
 * \brief Funcion criterio que filtra segun el estado de las ventas.
 * \param void* pElement, Es el puntero al espacio de memoria.
 * \param id* estado, Es el puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int ventas_filterByStatus(void* pElement, void* estado)
{
	int retorno = 0;
	Ventas* auxVenta = (Ventas*) pElement;
	int* pEstado = (int*) estado;
	int auxEstado;

	if(auxVenta != NULL)
	{
		ventas_getEstado(auxVenta, &auxEstado);
		if(auxEstado != *pEstado)
		{
			retorno = 1;
		}
	}
	return retorno;
}
