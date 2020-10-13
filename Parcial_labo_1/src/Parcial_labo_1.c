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

	cli_altaForzada(listCliente, QTY_CLI,"Leandro","Sobrino","20-39107331-9");
	cli_altaForzada(listCliente, QTY_CLI,"Jorge","Suarez","20-31388898-4");
	cli_altaForzada(listCliente, QTY_CLI,"Nicolas","Ramos","23-38165869-3");
	cli_altaForzada(listCliente, QTY_CLI,"Laura","Ochoa","27-35098981-7");
	cli_altaForzada(listCliente, QTY_CLI,"Florencia","Ayala","27-40189698-8");

	avi_altaForzada(listAviso, QTY_AVI,2,7,"VendoMuebles");
	avi_altaForzada(listAviso, QTY_AVI,1,1,"VendoAutos");
	avi_altaForzada(listAviso, QTY_AVI,2,5,"VendoMotos");
	avi_altaForzada(listAviso, QTY_AVI,3,4,"VendoAviones");
	avi_altaForzada(listAviso, QTY_AVI,4,2,"VendoAviones");
	avi_altaForzada(listAviso, QTY_AVI,4,1,"VendoAviones");
	avi_altaForzada(listAviso, QTY_AVI,4,9,"VendoAviones");
	avi_altaForzada(listAviso, QTY_AVI,4,5,"VendoAviones");
	avi_altaForzada(listAviso, QTY_AVI,4,1,"VendoAviones");

	do
	{
		optionMain = 0;
		utn_showMainMenu(&optionMain, listAviso, QTY_AVI, listCliente, QTY_CLI);
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
				if(avi_remove(listAviso, QTY_AVI, listCliente, QTY_CLI) == 0)
				{
					printf("El cliente y sus avisos se borraron correctamente.\n");
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
				if(avi_printClientes(listAviso, QTY_AVI, listCliente, QTY_CLI) == 0)
				{
					printf("La lista se mostro correctamente.\n");
				}
				break;
			case 8:
				if(utn_showReportMenu(&optionReport) == 0)
				{
					switch (optionReport)
					{
						case 1:
							avi_printClientWithMoreAdvices(listAviso, QTY_AVI, listCliente, QTY_CLI);
							break;
						case 2:
							avi_contarAvisosPausados(listAviso, QTY_AVI);
							break;
						case 3:
							rub_generarInformeDeRubro(listAviso);
							break;
						default:
							break;
					}
				}
				break;
			case 9:
				printf("Adios");
				break;
		}

	}while(optionMain != OPTIONS_MAIN);
}
