/*
 ============================================================================
 Name        : Parcial_labo_1.c
 Author      : Leandro Sobrino
 Description : Primer parcial - Laboratorio 1.
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Aviso.h"
#include "Cliente.h"
#include "validaciones.h"
#include "menu.h"

int main(void)
{
	setbuf(stdout,NULL);
	Cliente listCliente[QTY_CLI];
	Aviso listAviso[QTY_AVI];
	int optionMain;
	int optionReport;

	cli_init(listCliente, QTY_CLI);
	avi_init(listAviso, QTY_AVI);
	do
	{
		utn_showMainMenu(&optionMain);
		switch (optionMain)
		{
			case 1:
				if(cli_add(listCliente, QTY_CLI) == 0)
				{
					printf("El cliente se cargo correctamente.\n");
				}
				break;
			case 2:
				if(cli_modify(listCliente, QTY_CLI) == 0)
				{
					printf("El cliente se modifico correctamente.\n");
				}
				break;
			case 3:
				if(cli_remove(listCliente, QTY_CLI) == 0)
				{
					printf("El cliente se borro correctamente.\n");
				}
				break;
			case 4:
				if(avi_add(listAviso, QTY_AVI, listCliente, QTY_CLI) == 0)
				{
					printf("El aviso se publico correctamente.\n");
				}
				break;
			case 5:
				if(avi_changeState(listAviso, QTY_AVI, listCliente, QTY_CLI, PAUSADO) == 0)
				{
					printf("El aviso se pauso correctamente.\n");
				}
				break;
			case 6:
				if(avi_changeState(listAviso, QTY_AVI, listCliente, QTY_CLI, ACTIVO) == 0)
				{
					printf("El aviso se reanudo correctamente.\n");
				}
				break;
			case 7:
				break;
			case 8:
				if(utn_showReportMenu(&optionReport) == 0)
				{
					switch (optionReport)
					{
						case 1:
							printf("Opcion 1.\n");
							break;
						case 2:
							printf("Opcion 2.\n");
							break;
						case 3:
							printf("Opcion 3.\n");
							break;
						default:
							break;
					}
				}
				break;
		}
	}while(optionMain != OPTIONS_MAIN);
}