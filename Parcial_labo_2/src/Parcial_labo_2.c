/*
 ============================================================================
 Name        : Parcial_labo_2.c
 Author      : Leandro Sobrino
 Description : Segundo parcial de laboratorio 1. UTN
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "Controller.h"
#include "Cliente.h"
#include "Ventas.h"
#include "LinkedList.h"
#include "menu.h"

int main()
{
	setbuf(stdout,NULL);
    int option;
    LinkedList* listaClientes = ll_newLinkedList();
    LinkedList* listaVentas = ll_newLinkedList();
    if( !(controller_clienteLoadFromText("clientes.csv", listaClientes)) &&
		!(controller_ventasLoadFromText("ventas.csv", listaVentas)))
    {
    	do
		{
			option = 0;
			utn_showMenu(&option, listaClientes);
			switch(option)
			{
				case 1:
					if(!(controller_addCliente(listaClientes)) && !(controller_clienteSaveAsText("clientes.csv", listaClientes)))
					{
						printf("El cliente se ingreso correctamente.\n");
					}
					break;
				case 2:
					if(!(controller_addVenta(listaVentas, listaClientes)) && !(controller_ventasSaveAsText("ventas.csv", listaVentas)))
					{
						printf("La venta se realizo correctamente.\n");
					}
					break;
				case 3:
					if(!(controller_modifyVenta(listaVentas, listaClientes)) && !(controller_ventasSaveAsText("ventas.csv", listaVentas)))
					{
						printf("La venta se modifico correctamente.\n");
					}
					break;
				case 4:
					if(!(controller_cobrarVenta(listaVentas, listaClientes)) && !(controller_ventasSaveAsText("ventas.csv", listaVentas)))
					{
						printf("La venta se cobro correctamente.\n");
					}
					break;
				case 5:
					if(!(controller_generarInformeDeCobrosOrDeudas("cobradas.csv", listaClientes, listaVentas, COBRADA)))
					{
						printf("El archivo se genero correctamente.\n");
					}
					break;
				case 6:
					if(!(controller_generarInformeDeCobrosOrDeudas("a_cobrar.csv", listaClientes, listaVentas, SIN_COBRAR)))
					{
						printf("El archivo se genero correctamente.\n");
					}
					break;
				case 7:
					if(!(controller_imprimirVentaConMasAfiches(listaVentas, listaClientes)))
					{
						printf("Las estadisticas se generaron correctamente.\n");
					}
					break;
				case 10:
					if(!(controller_imprimirCliente(listaClientes)))
					{
						printf("Se imprimio esta mierda.\n");
					}
					break;
				case 11:
					if(!(controller_imprimirVentas(listaVentas)))
					{
						printf("Se imprimio esta mierda.\n");
					}
					break;
				case 12:
					printf("Adios");
					break;
			}
		}while(option != OPTIONS);
    }
    return EXIT_SUCCESS;
}
