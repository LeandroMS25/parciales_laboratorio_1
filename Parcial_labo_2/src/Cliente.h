/*
 * Cliente.h
 *
 *  Created on: 21 nov. 2020
 *      Author: Leandro Sobrino
 */

#ifndef cliente_H_
#define cliente_H_
#define SIZE_STR 128
#include "LinkedList.h"

typedef struct
{
	int idCliente;
	char nombre[SIZE_STR];
	char apellido[SIZE_STR];
	char cuit[SIZE_STR];
}Cliente;

Cliente* cliente_new(void);
void cliente_delete(Cliente* this);
Cliente* cliente_newParam(char* idCliente, char* nombre, char* apellido, char* cuit);
int cliente_setIdCliente(Cliente* this, int idCliente);
int cliente_getIdCliente(Cliente* this, int* idCliente);
int cliente_setNombre(Cliente* this, char* nombre);
int cliente_getNombre(Cliente* this, char* nombre);
int cliente_setApellido(Cliente* this, char* apellido);
int cliente_getApellido(Cliente* this, char* apellido);
int cliente_setCuit(Cliente* this, char* cuit);
int cliente_getCuit(Cliente* this, char* cuit);
int cliente_allSets(Cliente* this, int idCliente, char* nombre, char* apellido, char* cuit);
int cliente_allGets(Cliente* this, int* idCliente, char* nombre, char* apellido, char* cuit);
int cliente_findMaxId(LinkedList* pArrayListCliente, int* pMaxId);
int cliente_findCuitRepetido(LinkedList* pArrayListCliente, char* cuit);
int cliente_findClient(LinkedList* pArrayListCliente, int id);
int cliente_findIdAndPrint(LinkedList* pArrayListCliente, int id);
int cliente_findIndexById(LinkedList* pArrayListCliente, int id, int* pIndex);
void cliente_imprimir(void* pElement);

#endif /* cliente_H_ */
