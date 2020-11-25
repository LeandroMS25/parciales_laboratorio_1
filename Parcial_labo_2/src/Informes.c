/*
 * Informes.c
 *
 *  Created on: 25 nov. 2020
 *      Author: Leandro Sobrino
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Cliente.h"
#include "Ventas.h"
#include "LinkedList.h"
#include "parser.h"
#include "validaciones.h"
/** \brief Imprime la venta con mas afiches.
 *
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int informes_imprimirVentaConMasAfiches(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Ventas* auxVenta;
	int cantAfiches, cantMaxima, auxId, idCliente/*, auxEstado*/;

	if(pArrayListVentas != NULL && pArrayListCliente != NULL)
	{
		for (int i = 0; i < ll_len(pArrayListVentas); i++)
		{
			auxVenta = ll_get(pArrayListVentas, i);
			ventas_getCantAfiches(auxVenta, &cantAfiches);
			//ventas_getEstado(auxVenta, &auxEstado);
			if(i == 0 || /*(auxEstado == 1 &&*/ cantAfiches > cantMaxima)
			{
				cantMaxima = cantAfiches;
				ventas_getIdVentas(auxVenta, &auxId);
				ventas_getIdCliente(auxVenta, &idCliente);
			}
		}
		printf("\n3- El ID de la venta con mas afiches es el %d con %d afiches.\n",auxId,cantMaxima);
		printf("El/La cliente que hizo la compra fue: ");
		ll_mapArg(pArrayListCliente, cliente_findIdAndPrint, &idCliente);
		retorno = 0;
	}
	return retorno;
}
/** \brief Imprime el cliente al que se le vendio mas y menos afiches (el parametro limite indica MAXIMO o MINIMO).
 *
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \param int limite, recibe MAXIMO o MINIMO.
 * \return (-1) Error / (0) Ok
 *
 *//*
int informes_imprimirClienteConMasOrMenosAfichesConLimite(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente, int limite)
{
	int retorno = -1;
	Cliente* auxCliente;
	int cantAfiches, cantLimite, idLimite, idCliente;

	if(pArrayListVentas != NULL && pArrayListCliente != NULL && (limite == COBRADA || limite == SIN_COBRAR))
	{
		for (int i = 0; i < ll_len(pArrayListCliente); i++)
		{
			auxCliente = ll_get(pArrayListCliente, i);
			cliente_getIdCliente(auxCliente, &idCliente);
			cantAfiches = ll_reduceInt(pArrayListVentas, ventas_calcularCantidadAfiches, &idCliente);
			if( cantAfiches != 0 &&
				((limite == MAXIMO && (i == 0 || cantAfiches > cantLimite)) ||
				(limite == MINIMO && (i == 0 || cantAfiches < cantLimite))))
			{
				cantLimite = cantAfiches;
				idLimite = idCliente;
			}
		}
		if(limite == MAXIMO)
		{
			printf("\n1- El/La cliente al que se le vendio mas afiches fue: ");
			cliente_findIdAndPrint(pArrayListCliente, idLimite);
		}
		else
		{
			printf("\n2- El/La cliente al que se le vendio menos afiches fue: ");
			cliente_findIdAndPrint(pArrayListCliente, idLimite);
		}
		printf(" con %d afiches.",cantLimite);
		retorno = 0;
	}
	return retorno;
}
*/
/** \brief Imprime el cliente al que se le vendio mas y menos afiches.
 *
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int informes_imprimirClienteConMasOrMenosAfiches(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Cliente* auxCliente;
	int cantAfiches, maximo, minimo, idMaximo, idMinimo, idCliente;

	if(pArrayListVentas != NULL && pArrayListCliente != NULL)
	{
		for (int i = 0; i < ll_len(pArrayListCliente); i++)
		{
			auxCliente = ll_get(pArrayListCliente, i);
			cliente_getIdCliente(auxCliente, &idCliente);
			cantAfiches = ll_reduceInt(pArrayListVentas, ventas_calcularCantidadAfiches, &idCliente);
			if(cantAfiches != 0)
			{
				if(i == 0 || cantAfiches > maximo)
				{
					maximo = cantAfiches;
					idMaximo = idCliente;
				}
				if(i == 0 || cantAfiches < minimo)
				{
					minimo = cantAfiches;
					idMinimo = idCliente;
				}
			}
		}
		printf("\n1- El/La cliente al que se le vendio mas afiches fue: ");
		ll_mapArg(pArrayListCliente, cliente_findIdAndPrint, &idMaximo);
		printf(" con %d afiches.",maximo);
		printf("\n2- El/La cliente al que se le vendio menos afiches fue: ");
		ll_mapArg(pArrayListCliente, cliente_findIdAndPrint, &idMinimo);
		printf(" con %d afiches.",minimo);
		retorno = 0;
	}
	return retorno;
}
