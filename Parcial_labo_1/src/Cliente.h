/*
 * Cliente.h
 * Author: Leandro Sobrino
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#define LONG_NAME 51
#define LONG_CUIT 20
#define QTY_CLI 100
typedef struct
{
	int id;
	int isEmpty;
	char name[LONG_NAME];
	char lastName[LONG_NAME];
	char cuit[LONG_CUIT];
}Cliente;

int cli_init(Cliente* list, int len);
int cli_add(Cliente* list, int len);
int cli_remove(Cliente* list, int len, int index);
int cli_modify(Cliente* list, int len);
int cli_print(Cliente* list, int len);
int cli_show(Cliente* list,int index);
int cli_findById(Cliente* list, int len, int id, int* pIndex);
int cli_findFree(Cliente* list, int len, int* pIndex);
int cli_findOccupied(Cliente* list, int len, int* pIndex);
int cli_sortByName(Cliente* list, int len, int order);
int cli_altaForzada(Cliente* list, int len, char* name, char* lastName, char* cuit);

#endif /* CLIENTE_H_ */
