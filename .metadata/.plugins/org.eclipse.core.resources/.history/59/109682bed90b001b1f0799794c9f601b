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
	int flagPause = 0;

	cli_init(listCliente, QTY_CLI);
	avi_init(listAviso, QTY_AVI);

	cli_altaForzada(listCliente, QTY_CLI,"Juan","Alvaro","20-16597452-9");
	cli_altaForzada(listCliente, QTY_CLI,"Jose","Perez","20-12643526-9");
	cli_altaForzada(listCliente, QTY_CLI,"Noco","Lomo","20-79164125-9");
	cli_altaForzada(listCliente, QTY_CLI,"Leandro","Merino","20-12387456-9");
	cli_altaForzada(listCliente, QTY_CLI,"Claudio","Manzano","20-12347865-9");

	avi_altaForzada(listAviso, QTY_AVI,2,4,"VendoClio2010");
	avi_altaForzada(listAviso, QTY_AVI,1,4,"VendoAutos");
	avi_altaForzada(listAviso, QTY_AVI,2,4,"VendoMotos");
	avi_altaForzada(listAviso, QTY_AVI,3,4,"VendoCarros");

	do
	{
		if(flagPause)
		{
			system("pause");
			system("cls");
		}
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
							avi_contarAvisosPausados(listAviso, QTY_AVI);
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
		flagPause = 1;
	}while(optionMain != OPTIONS_MAIN);
}
