/*
 * menu.c
 * Author: Leandro Sobrino
 */
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "validaciones.h"

/**
 * \brief	Muestra el menu principal.
 * \param	int* pOption, puntero a un espacio de memoria.
 * \return	Retorna 0 (exito)y -1 (error).
 */
int utn_showMainMenu(int* pOption)
{
	int retorno = -1;
	int option;

	if(pOption != NULL)
	{
		if(utn_getNumberInt(&option, "***Menu de opciones***\n\n"
									 "1- Alta del cliente.\n"
									 "2- Modificar datos del cliente.\n"
									 "3- Baja del cliente.\n"
									 "4- Publicar aviso.\n"
									 "5- Pausar aviso.\n"
									 "6- Reanudar aviso.\n"
									 "7- Imprimir listado de clientes.\n"
									 "8- Informar.\n"
									 "9- Salir.\n\n"
									 "Ingrese la opcion: ", "Opcion ingresada invalida.\n", 1, OPTIONS_MAIN, 2) == 0)
		{
			*pOption = option;
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief	Muestra el menu de informes.
 * \param	int* pOption, puntero a un espacio de memoria.
 * \return	Retorna 0 (exito)y -1 (error).
 */
int utn_showReportMenu(int* pOption)
{
	int retorno = -1;
	int option;

	if(pOption != NULL)
	{
		if(utn_getNumberInt(&option,"***Menu de informes***\n\n"
									"1- Cliente con mas avisos.\n"
									"2- Cantidad de avisos pausados.\n"
									"3- Rubro con mas avisos.\n"
									"4- Salir.\n"
									"Ingrese la opcion: ", "Opcion ingresada invalida.\n", 1, OPTIONS_REPORT, 2) == 0)
		{
			*pOption = option;
			retorno = 0;
		}
	}
	return retorno;
}
