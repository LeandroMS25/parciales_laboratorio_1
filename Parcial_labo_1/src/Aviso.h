/*
 * Aviso.h
 * Author: Leandro Sobrino
 */
#ifndef AVISO_H_
#define AVISO_H_

#include "Cliente.h"
#define LONG_NAME 51
#define LONG_TEXTO 65
#define ACTIVO 1
#define PAUSADO 0
#define SI 1
#define NO 2
#define QTY_AVI 1000
typedef struct
{
	int idAviso;
	int isEmpty;
	int rubro;
	char text[LONG_TEXTO];
	int idCliente;
	int estado;
}Aviso;

int avi_init(Aviso* list, int len);
int avi_add(Aviso* list, int len, Cliente* listCliente, int lenCliente);
int avi_remove(Aviso* list, int len, Cliente* listCliente, int lenCliente);
int avi_modify(Aviso* list, int len, Cliente* listCliente, int lenCliente);
int avi_print(Aviso* list, int len, Cliente* listCliente, int lenCliente);
int avi_show(Aviso* list,int index);
int avi_findById(Aviso* list, int len, int id, int* pIndex);
int avi_findFree(Aviso* list, int len, int* pIndex);
int avi_findOccupied(Aviso* list, int len);
int avi_sortByName(Aviso* list, int len, int order);
int avi_changeState(Aviso* list, int len, Cliente* listCliente, int lenCliente, int state);

#endif /* AVISO_H_ */