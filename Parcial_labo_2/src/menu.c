/*
 * menu.h
 * Author: Leandro Sobrino
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cliente.h"
#include "validaciones.h"
#include "menu.h"
#include "LinkedList.h"
/**
 * \brief	Muestra el menu principal.
 * \param	int* pOption, puntero a un espacio de memoria.
 * \return	Retorna 0 (exito)y -1 (error).
 */
int utn_showMenu(int* pOption, LinkedList* pArrayListCliente)
{
	int retorno = -1;
	int option;

	if(pOption != NULL)
	{
		if(utn_getNumberInt(&option, "***Menu de opciones***\n\n"
									 "1- Dar de alta a un cliente.\n"
									 "2- Realizar una venta.\n"
									 "3- Modificar una venta.\n"
									 "4- Cobrar una venta.\n"
									 "5- Generar informe de cobros.\n"
									 "6- Generar informe de deudas.\n"
									 "7- Mostrar estadisticas.\n"
									 "8- Mostrar lista de clientes.\n"
									 "9- Mostrar lista de ventas.\n"
									 "10- Salir.\n\n"
									 "Ingrese la opcion: ", "Opcion ingresada invalida.\n", 1, OPTIONS, 2) == 0)
		{
		/*
			&&
		ll_isEmpty(pArrayListCliente) && option > 1 && option < OPTIONS)
		{
			printf("Primero se debe cargar la lista.\n");
		}
		else
		{
			if(ll_isEmpty(pArrayListEnvio) == 0 && option == 1)
			{
				printf("La lista ya fue cargada.\n");
			}
			else
			{
			*/
				*pOption = option;
				retorno = 0;

		}
	}
	return retorno;
}
