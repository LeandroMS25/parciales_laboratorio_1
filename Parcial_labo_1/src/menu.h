/*
 * menu.h
 * Author: Leandro Sobrino
 */

#ifndef MENU_H_
#define MENU_H_

#include "Cliente.h"
#include "Aviso.h"
#define OPTIONS_MAIN 9
#define OPTIONS_REPORT 4

int utn_showMainMenu(int* pOption, Aviso* list, int len, Cliente* listCliente, int lenCliente);
int utn_showReportMenu(int* pOption);

#endif /* MENU_H_ */
