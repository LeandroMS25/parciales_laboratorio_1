/*
 * Ventas.h
 *
 *  Created on: 21 nov. 2020
 *      Author: Leandro Sobrino
 */

#ifndef ventas_H_
#define ventas_H_
#define SIZE_STR 128
#define COBRADA 1
#define SIN_COBRAR 0
#define MAXIMO 1
#define MINIMO 0
#include "LinkedList.h"

typedef struct
{
	int idVentas;
	int cantAfiches;
	char nombreArchivo[SIZE_STR];
	int zona;
	int estado;
	int idCliente;
}Ventas;

Ventas* ventas_new(void);
void ventas_delete(Ventas* this);
Ventas* ventas_newParam(char* idVentas, char* cantAfiches, char* nombreArchivo, char* zona,char* estado,char* idCliente);
int ventas_setIdVentas(Ventas* this, int idVentas);
int ventas_getIdVentas(Ventas* this, int* idVentas);
int ventas_setCantAfiches(Ventas* this, int cantAfiches);
int ventas_getCantAfiches(Ventas* this, int* cantAfiches);
int ventas_setNombreArchivo(Ventas* this, char* nombreArchivo);
int ventas_getNombreArchivo(Ventas* this, char* nombreArchivo);
int ventas_setZona(Ventas* this, int zona);
int ventas_getZona(Ventas* this, int* zona);
int ventas_setIdCliente(Ventas* this, int idCliente);
int ventas_getIdCliente(Ventas* this, int* idCliente);
int ventas_setEstado(Ventas* this, int estado);
int ventas_getEstado(Ventas* this, int* estado);
int ventas_allSets(Ventas* this, int idVentas, int cantAfiches, char* nombreArchivo, int zona, int estado, int idCliente);
int ventas_allGets(Ventas* this, int* idVentas, int* cantAfiches, char* nombreArchivo, int* zona, int* estado, int* idCliente);
void ventas_imprimir(void* pElement);
void ventas_imprimirSinCobrar(void* pElement);
int ventas_imprimirSegunIdCliente(void* pElement, void* idCliente);
int ventas_calcularVentasCobradasOrAdeudadas(void* pElement, void* arg);
int ventas_calcularCantidadAfiches(void* pElement, void* id);
int ventas_filterByStatus(void* pElement, void* estado);
int ventas_filterByIdCliente(void* pElement, void* idCliente);
int ventas_findMaxId(LinkedList* pArrayListVentas, int* pMaxId);
int ventas_findIndexByIdAndStatus(LinkedList* pArrayListVentas, int id, int estado, int* pIndex);
int ventas_findIndexById(LinkedList* pArrayListVentas, int id, int* pIndex);

#endif /* ventas_H_ */
