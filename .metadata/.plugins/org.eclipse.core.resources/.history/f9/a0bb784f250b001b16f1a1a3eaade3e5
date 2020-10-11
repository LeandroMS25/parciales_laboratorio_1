/*
 * Contratacion.h
 *
 *  Created on: 1 oct. 2020
 *      Author: Leandro
 */

#ifndef CONTRATACIONES_H_
#define CONTRATACIONES_H_

#include "Screen.h"
#define LONG_NAME 51
#define LONG_CUIT 51
#define DIRECTION 101
#define QTY_DAYS 365
typedef struct
{
	int idContratacion;
	int isEmpty;
	char nombreVideo[LONG_NAME];
	int cantDias;
	char cuitCliente[LONG_CUIT];
	int idScreen;
}Contratacion;

int con_init(Contratacion* list, int len);
int con_add(Contratacion* list, int len, Screen* listScreen, int lenScreen);
int con_remove(Contratacion* list, int len, Screen* listScreen, int lenScreen);
int con_modify(Contratacion* list, int len, Screen* listScreen, int lenScreen);
int con_print(Contratacion* list, int len, Screen* listScreen, int lenScreen);
int con_findById(Contratacion* list, int len, int id, int* pIndex);
int con_findFree(Contratacion* list, int len, int* pIndex);
int con_findOccupied(Contratacion* list, int len);
int con_sortByName(Contratacion* list, int len, int order);
int con_printByCuit(Contratacion* list, int len, char* cuit);
int con_checkAmountToPay(Contratacion* list, int len, Screen* listScreen, int lenScreen);

#endif /* CONTRATACIONES_H_ */
