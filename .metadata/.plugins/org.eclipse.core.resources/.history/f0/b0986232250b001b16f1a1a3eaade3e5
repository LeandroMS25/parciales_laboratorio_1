/*
 * Screen.h
 *
 *  Created on: 29 sept. 2020
 *      Author: Leandro
 */

#ifndef NAT_H_
#define NAT_H_

#define LONG_NAME 51
#define DIRECTION 101
typedef struct
{
	int id;
	int isEmpty;
	char name[LONG_NAME];
	int type;
	float price;
	char address[DIRECTION];
}Screen;

int scr_init(Screen* list, int len);
int scr_add(Screen* list, int len);
int scr_remove(Screen* list, int len);
int scr_modify(Screen* list, int len);
int scr_print(Screen* list, int len);
int scr_findById(Screen* list, int len, int id, int* pIndex);
int scr_findFree(Screen* list, int len, int* pIndex);
int scr_findOccupied(Screen* list, int len);
int scr_sortByName(Screen* list, int len, int order);
int scr_altaForzada(Screen* list, int len, char* name, int* type, float* price, char* adress);

#endif /* NAT_H_ */
