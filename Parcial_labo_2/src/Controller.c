#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Cliente.h"
#include "Ventas.h"
#include "LinkedList.h"
#include "parser.h"
#include "validaciones.h"
#include "Controller.h"
#include "Informes.h"
#define LEN_TEXT 4096

/** \brief Carga los datos de los clientes desde el archivo (modo texto).
 *
 * \param Char* path, archivo que va a ser leído.
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_clienteLoadFromText(char* path , LinkedList* pArrayListCliente)
{
	int retorno = -1;

	FILE* pFile;
	if(path != NULL && pArrayListCliente != NULL)
	{
		pFile = fopen(path,"r");
		if(pFile != NULL && !(parser_clienteFromText(pFile, pArrayListCliente)))
		{
			retorno = 0;
			fclose(pFile);
		}
		else
		{
			printf("No se pudo abrir el archivo.\n");
		}
	}
    return retorno;
}
/** \brief Carga los datos de las ventas desde el archivo (modo texto).
 *
 * \param Char* path, archivo que va a ser leído.
 * \param LinkedList* pArrayListVenta, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_ventasLoadFromText(char* path , LinkedList* pArrayListVenta)
{
	int retorno = -1;

	FILE* pFile;
	if(path != NULL && pArrayListVenta != NULL)
	{
		pFile = fopen(path,"r");
		if(pFile != NULL && !(parser_ventasFromText(pFile, pArrayListVenta)))
		{
			retorno = 0;
			fclose(pFile);
		}
		else
		{
			printf("No se pudo abrir el archivo.\n");
		}
	}
    return retorno;
}
/** \brief Guarda los datos de los cliente en el archivo (modo texto).
 *
 * \param Char* path, archivo que va a ser escrito.
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_clienteSaveAsText(char* path , LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Cliente* auxEnvio;
	int len = ll_len(pArrayListCliente);
	int auxIdCliente;
	char auxNombre[SIZE_STR];
	char auxApellido[SIZE_STR];
	char auxCuit[SIZE_STR];
	FILE* pFile;

	if(path != NULL && pArrayListCliente != NULL && len > 0)
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
			fprintf(pFile, "%s,%s,%s,%s\n","idCliente","nombre","apellido","cuit");
			for (int i = 0; i < len; i++)
			{
				auxEnvio = ll_get(pArrayListCliente, i);
				if(!(cliente_allGets(auxEnvio, &auxIdCliente, auxNombre, auxApellido,auxCuit)))
				{
					fprintf(pFile, "%d,%s,%s,%s\n",auxIdCliente,auxNombre,auxApellido,auxCuit);
					retorno = 0;
				}
			}
		}
		else
		{
			printf("No se pudo abrir el archivo.\n");
		}
	}
	fclose(pFile);
	return retorno;
}
/** \brief Guarda los datos de las ventas en el archivo(modo texto).
 *
 * \param Char* path, archivo que va a ser escrito.
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_ventasSaveAsText(char* path , LinkedList* pArrayListVentas)
{
	int retorno = -1;
	Ventas* auxVenta;
	int len = ll_len(pArrayListVentas);
	int auxIdVentas;
	int auxCantAfiches;
	char auxNombreArchivo[SIZE_STR];
	int auxZona;
	int auxEstado;
	int idCliente;
	FILE* pFile;

	if(path != NULL && pArrayListVentas != NULL && len > 0)
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
			fprintf(pFile, "%s,%s,%s,%s,%s,%s\n","idVentas","cantAfiches","nombreArchivo","zona","estado","idCliente");
			for (int i = 0; i < len; i++)
			{
				auxVenta = ll_get(pArrayListVentas, i);
				if(!(ventas_allGets(auxVenta, &auxIdVentas, &auxCantAfiches, auxNombreArchivo,&auxZona,&auxEstado,&idCliente)))
				{
					fprintf(pFile, "%d,%d,%s,%d,%d,%d\n",auxIdVentas,auxCantAfiches,auxNombreArchivo,auxZona,auxEstado,idCliente);
					retorno = 0;
				}
			}
		}
		else
		{
			printf("No se pudo abrir el archivo.\n");
		}
	}
	fclose(pFile);
	return retorno;
}
/** \brief Agrega un cliente a la lista.
 *
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_addCliente(LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Cliente* auxCliente = cliente_new();
	char auxNombre[SIZE_STR];
	char auxApellido[SIZE_STR];
	char auxCuit[SIZE_STR];
	int auxId;

	if(pArrayListCliente != NULL && auxCliente != NULL)
	{
		if( utn_getName(auxNombre, "Ingrese el nombre del cliente: ", "Nombre invalido.\n", 2, SIZE_STR - 1) == 0 &&
			utn_getName(auxApellido, "Ingrese el apellido del cliente: ", "Apellido invalido.\n", 2, SIZE_STR - 1) == 0 &&
			utn_getCuit(auxCuit, "Ingrese el cuit del cliente: ", "Cuit invalido.\n", 2, SIZE_STR - 1) == 0 &&
			ll_mapArg(pArrayListCliente, cliente_findCuitRepetido, auxCuit) != 0 &&
			!(cliente_findMaxId(pArrayListCliente, &auxId)) &&
			!(cliente_allSets(auxCliente, auxId, auxNombre, auxApellido, auxCuit)))
		{
			printf("ID cliente: %d.\n",auxId);
			ll_add(pArrayListCliente, auxCliente);
			retorno = 0;
		}
		else
		{
			printf("El cuit ingresado ya se encuentra en la lista.\n");
			cliente_delete(auxCliente);
		}
	}
	return retorno;
}
/** \brief Agrega una venta a la lista.
 *
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_addVenta(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Ventas* auxVenta = ventas_new();
	int auxId;
	int auxCantAfiches;
	char auxNombreArchivo[SIZE_STR];
	int auxZona;
	int idCliente;

	if(pArrayListCliente != NULL && pArrayListVentas != NULL && auxVenta != NULL)
	{
		controller_imprimirCliente(pArrayListCliente);
		if( utn_getNumberInt(&idCliente, "Seleccione el ID del cliente: ", "ID incorrecto.\n", 0, INT_MAX, 2) == 0 &&
			ll_mapArg(pArrayListCliente, cliente_findClient, &idCliente) == 0 &&
			utn_getNumberInt(&auxCantAfiches, "Ingrese la cantidad de afiches: ", "Cantidad incorrecta.\n", 0, INT_MAX, 2) == 0 &&
			utn_getName(auxNombreArchivo, "Ingrese el nombre del archivo: ", "Nombre invalido.\n", 2, SIZE_STR - 1) == 0 &&
			utn_getNumberInt(&auxZona, "Ingrese la zona donde se pegaran los afiches (0- CABA | 1- ZONA SUR | 2- ZONA OESTE): ",
					"Cantidad incorrecta.\n", 0, INT_MAX, 2) == 0 &&
			!(ventas_findMaxId(pArrayListVentas, &auxId)) &&
			!(ventas_allSets(auxVenta, auxId, auxCantAfiches, auxNombreArchivo, auxZona, 0,idCliente)))
		{
			printf("ID venta: %d.\n",auxId);
			ll_add(pArrayListVentas, auxVenta);
			retorno = 0;
		}
		else
		{
			printf("El ID del cliente seleccionado es incorrecto.\n");
			ventas_delete(auxVenta);
		}
	}
	return retorno;
}
/** \brief Se encarga de cobrar una venta (Cambia de estado SIN_COBRAR a COBRADA).
 *
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_cobrarVenta(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Ventas* auxVenta;
	int auxId, indexModify, option, idCliente;

	if(pArrayListCliente != NULL && pArrayListVentas != NULL)
	{
		ll_map(pArrayListVentas, ventas_imprimirSinCobrar);
		if( utn_getNumberInt(&auxId, "Seleccione el ID de la venta que desea cobrar: ", "ID incorrecto.\n", 0, INT_MAX, 2) == 0 &&
			ventas_findIndexByIdAndStatus(pArrayListVentas, auxId, SIN_COBRAR, &indexModify) == 0 &&
			!(ventas_getIdCliente(ll_get(pArrayListVentas, indexModify), &idCliente)) && ll_mapArg(pArrayListCliente, cliente_findIdAndPrint, &idCliente) == 0)
		{
			auxVenta = ll_get(pArrayListVentas, indexModify);
			if(utn_getNumberInt(&option, "¿Desea seguir con el cobro de la venta? (1- SI | 2- NO): ", "Respuesta incorrecta.\n", 1, 2, 2) == 0
				&& option == 1 && !(ventas_setEstado(auxVenta, 1)))
			{
				printf("ID venta: %d.\n",auxId);
				retorno = 0;
			}
			else
			{
				printf("Se cancelo el cambio de estado.\n");
			}
		}
		else
		{
			printf("El ID de la venta seleccionada es incorrecto.\n");
		}
	}
	return retorno;
}
/** \brief Elimina una venta de la lista.
 *
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_removeVenta(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente)
{
	int retorno = -1;
	int auxId, indexRemove, idCliente, option;

	if(pArrayListCliente != NULL && pArrayListVentas != NULL)
	{
		ll_map(pArrayListVentas, ventas_imprimirSinCobrar);
		if( utn_getNumberInt(&auxId, "Seleccione el ID de la venta que quiere modificar: ", "ID incorrecto.\n", 0, INT_MAX, 2) == 0 &&
			!(ventas_findIndexByIdAndStatus(pArrayListVentas, auxId, SIN_COBRAR, &indexRemove)) &&
			!(ventas_getIdCliente(ll_get(pArrayListVentas, indexRemove), &idCliente)) && ll_mapArg(pArrayListCliente, cliente_findIdAndPrint, &idCliente) == 0 &&
			utn_getNumberInt(&option, "¿Desea continuar con la eliminacion de la venta? (1- SI | 2- NO): ", "Respuesta incorrecta.\n", 1, 2, 2) == 0)
		{
			if(option == 1)
			{
				ll_pop(pArrayListVentas, indexRemove);
				printf("ID venta: %d.\n",auxId);
				retorno = 0;
			}
			else
			{
				printf("Se cancelo a la eliminacion.\n");
			}
		}
		else
		{
			printf("El ID de la venta seleccionada es incorrecta.\n");
		}
	}
	return retorno;
}
/** \brief Elimina un cliente y sus ventas de la lista.
 *
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_removeCliente(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente)
{
	int retorno = -1;
	int auxId, indexRemove, option;

	if(pArrayListCliente != NULL && pArrayListVentas != NULL)
	{
		ll_map(pArrayListCliente, cliente_imprimir);
		if( utn_getNumberInt(&auxId, "Seleccione el ID de la cliente que se quiere eliminar: ", "ID incorrecto.\n", 0, INT_MAX, 2) == 0 &&
			cliente_findIndexById(pArrayListCliente, auxId, &indexRemove) && ll_mapArg(pArrayListCliente, cliente_findIdAndPrint, &auxId) == 0 &&
			utn_getNumberInt(&option, "¿Desea continuar con la eliminacion de la cliente? (1- SI | 2- NO): ", "Respuesta incorrecta.\n", 1, 2, 2) == 0)
		{
			if(option == 1)
			{
				printf("Ventas elimininadas del cliente: \n");
				ll_mapArg(pArrayListVentas, ventas_imprimirSegunIdCliente, &auxId);
				ventas_deleteByIdCliente(pArrayListVentas, auxId);
				cliente_delete(ll_pop(pArrayListCliente, indexRemove));
				printf("ID cliente: %d.\n",auxId);
				retorno = 0;
			}
			else
			{
				printf("Se cancelo a la eliminacion.\n");
			}
		}
		else
		{
			printf("El ID del cliente seleccionado es incorrecto.\n");
		}
	}
	return retorno;
}
/** \brief Se encarga de cambiar los datos del cliente (permite seleccionar el campo a modificar).
 *
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_modifyClient(LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Cliente* auxCliente;
	int auxId, option, indexModify;
	char auxNombre[SIZE_STR];
	char auxCuit[SIZE_STR];
	char auxApellido[SIZE_STR];

	if(pArrayListCliente != NULL)
	{
		ll_map(pArrayListCliente, cliente_imprimir);
		if( utn_getNumberInt(&auxId, "Seleccione el ID del cliente que quiere eliminar: ", "ID incorrecto.\n", 0, INT_MAX, 2) == 0 &&
			cliente_findIndexById(pArrayListCliente, auxId, &indexModify) &&
			utn_getNumberInt(&option, "Ingrese el campo a cambiar(0- Nombre | 1- Apellido | 2- Cuit): "
									, "Opcion incorrecta.\n", 0, INT_MAX, 2) == 0)
		{
			auxCliente = ll_get(pArrayListCliente, indexModify);
			switch (option)
			{
				case 0:
					utn_getName(auxNombre, "Ingrese el nombre del cliente: ", "Nombre invalido.\n", 2, SIZE_STR - 1);
					cliente_setNombre(auxCliente, auxNombre);
					break;
				case 1:
					utn_getName(auxApellido, "Ingrese el apellido del cliente: ", "Apellido invalido.\n", 2, SIZE_STR - 1);
					cliente_setApellido(auxCliente, auxApellido);
					break;
				case 2:
					utn_getCuit(auxCuit, "Ingrese el cuit del cliente: ", "Cuit invalido.\n", 2, SIZE_STR - 1);
					cliente_setCuit(auxCliente, auxCuit);
					break;
			}
			ll_mapArg(pArrayListCliente, cliente_findIdAndPrint, &auxId);
			retorno = 0;
		}
		else
		{
			printf("El ID del cliente seleccionado es incorrecto.\n");
		}
	}
	return retorno;
}
/** \brief Se encarga de cambiar los datos de la venta (permite seleccionar el campo a modificar).
 *
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_modifyVenta(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Ventas* auxVenta;
	int auxId, option, auxZona, indexModify, auxCantAfiches, idCliente;
	char auxNombreArchivo[SIZE_STR];

	if(pArrayListCliente != NULL && pArrayListVentas != NULL)
	{
		ll_map(pArrayListVentas, ventas_imprimir);
		if( utn_getNumberInt(&auxId, "Seleccione el ID de la venta que quiere modificar: ", "ID incorrecto.\n", 0, INT_MAX, 2) == 0 &&
			ventas_findIndexByIdAndStatus(pArrayListVentas, auxId, SIN_COBRAR, &indexModify) == 0 &&
			!(ventas_getIdCliente(ll_get(pArrayListVentas, indexModify), &idCliente)) && ll_mapArg(pArrayListCliente, cliente_findIdAndPrint, &idCliente) == 0 &&
			utn_getNumberInt(&option, "Ingrese el campo a cambiar(0- Cantidad de afiches | 1- Nombre del archivo | 2- Zona): "
					, "Opcion incorrecta.\n", 0, INT_MAX, 2) == 0)
		{
			auxVenta = ll_get(pArrayListVentas, indexModify);
			switch (option)
			{
				case 0:
					utn_getNumberInt(&auxCantAfiches, "Ingrese la cantidad de afiches: ", "Cantidad incorrecta.\n", 0, INT_MAX, 2);
					ventas_setCantAfiches(auxVenta, auxCantAfiches);
					break;
				case 1:
					utn_getName(auxNombreArchivo, "Ingrese el nombre del archivo: ", "Nombre invalido.\n", 2, SIZE_STR - 1);
					ventas_setNombreArchivo(auxVenta, auxNombreArchivo);
					break;
				case 2:
					utn_getNumberInt(&auxZona, "Ingrese la zona donde se pegaran los afiches (0- CABA | 1- ZONA SUR | 2- ZONA OESTE): ",
										"Cantidad incorrecta.\n", 0, INT_MAX, 2);
					ventas_setZona(auxVenta, auxZona);
					break;
			}
			printf("ID venta: %d.\n",auxId);
			retorno = 0;
		}
		else
		{
			printf("El ID de la venta seleccionada es incorrecto.\n");
		}
	}
	return retorno;
}
/** \brief Guarda los datos de los cliente con cantidad de ventas cobradas o adeudadas en el archivo (modo texto).
 *	Usa estructura de argumentos para filtrar.
 * \param Char* path, archivo que va a ser escrito.
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \param int estado, recibe el estado de las ventas.
 * \return (-1) Error / (0) Ok
 *
 *//*
int controller_generarInformeDeCobrosOrDeudas(char* path , LinkedList* pArrayListCliente, LinkedList* pArrayListVentas, int estado)
{
	int retorno = -1;
	Cliente* auxEnvio;
	ArgumentosFiltro auxArg;
	int len = ll_len(pArrayListCliente);
	int auxIdCliente, cantVentas;
	char auxNombre[SIZE_STR];
	char auxApellido[SIZE_STR];
	char auxCuit[SIZE_STR];
	auxArg.estado = estado;
	FILE* pFile;

	if(path != NULL && pArrayListCliente != NULL && pArrayListVentas != NULL && len > 0 &&
		(estado == COBRADA || estado == SIN_COBRAR))
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
			if(estado == COBRADA)
			{
				fprintf(pFile, "%s,%s,%s,%s,%s\n","idCliente","nombre","apellido","cuit","cantidadVentasCobradas");
			}
			else
			{
				fprintf(pFile, "%s,%s,%s,%s,%s\n","idCliente","nombre","apellido","cuit","cantidadVentasSinCobrar");
			}
			for (int i = 0; i < len; i++)
			{
				auxEnvio = ll_get(pArrayListCliente, i);
				if(!(cliente_allGets(auxEnvio, &auxIdCliente, auxNombre, auxApellido,auxCuit)))
				{
					auxArg.id = auxIdCliente;
					cantVentas = ll_reduceInt(pArrayListVentas, ventas_calcularVentasCobradasOrAdeudadas, &auxArg);
					fprintf(pFile, "%d,%s,%s,%s,%d\n",auxIdCliente,auxNombre,auxApellido,auxCuit,cantVentas);
					retorno = 0;
				}
			}
		}
		else
		{
			printf("No se pudo abrir el archivo.\n");
		}
	}
	fclose(pFile);
	return retorno;
}*/
/** \brief Guarda los datos de los cliente con cantidad de ventas cobradas o adeudadas en el archivo (modo texto).
 *	Usa filter
 * \param Char* path, archivo que va a ser escrito.
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \param int estado, recibe el estado de las ventas.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_generarInformeDeCobrosOrDeudas(char* path , LinkedList* pArrayListCliente, LinkedList* pArrayListVentas, int estado)
{
	int retorno = -1;
	Cliente* auxEnvio;
	LinkedList* listaFiltrada;
	int len = ll_len(pArrayListCliente);
	int auxIdCliente, cantVentas;
	char auxNombre[SIZE_STR];
	char auxApellido[SIZE_STR];
	char auxCuit[SIZE_STR];
	FILE* pFile;

	if(path != NULL && pArrayListCliente != NULL && pArrayListVentas != NULL && len > 0 &&
		(estado == COBRADA || estado == SIN_COBRAR))
	{
		pFile = fopen(path,"w");
		if(pFile != NULL)
		{
			if(estado == COBRADA)
			{
				fprintf(pFile, "%s,%s,%s,%s,%s\n","idCliente","nombre","apellido","cuit","cantidadVentasCobradas");
			}
			else
			{
				fprintf(pFile, "%s,%s,%s,%s,%s\n","idCliente","nombre","apellido","cuit","cantidadVentasSinCobrar");
			}
			listaFiltrada = controller_filtrarVentasPorEstado(pArrayListVentas, estado);
			for (int i = 0; i < len; i++)
			{
				auxEnvio = ll_get(pArrayListCliente, i);
				if(!(cliente_allGets(auxEnvio, &auxIdCliente, auxNombre, auxApellido,auxCuit)))
				{
					cantVentas = ll_reduceInt(listaFiltrada, ventas_calcularVentasCobradasOrAdeudadas, &auxIdCliente);
					fprintf(pFile, "%d,%s,%s,%s,%d\n",auxIdCliente,auxNombre,auxApellido,auxCuit,cantVentas);
					retorno = 0;
				}
			}
		}
		else
		{
			printf("No se pudo abrir el archivo.\n");
		}
	}
	fclose(pFile);
	return retorno;
}
/** \brief Imprime los informes.
 *
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_generarInformes(LinkedList* pArrayListCliente, LinkedList* pArrayListVentas)
{
	int retorno = -1;

	if(pArrayListCliente != NULL && pArrayListVentas != NULL)
	{
		if(!(informes_imprimirClienteConMasOrMenosAfiches(pArrayListVentas, pArrayListCliente)) &&
		   !(informes_imprimirVentaConMasAfiches(pArrayListVentas, pArrayListCliente)))
		{
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief Imprime la lista de clientes.
 *
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_imprimirCliente(LinkedList* pArrayListCliente)
{
	int retorno = -1;

	if(pArrayListCliente != NULL)
	{
		ll_map(pArrayListCliente, cliente_imprimir);
		retorno = 0;
	}
	return retorno;
}
/** \brief Imprime la lista de las ventas.
 *
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_imprimirVentas(LinkedList* pArrayListVentas)
{
	int retorno = -1;

	if(pArrayListVentas != NULL)
	{
		ll_map(pArrayListVentas, ventas_imprimir);
		retorno = 0;
	}
	return retorno;
}
/** \brief Imprime la lista de las ventas.
 *
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
LinkedList* controller_filtrarVentasPorEstado(LinkedList* pArrayListVentas, int estado)
{
	LinkedList* retorno;

	if(pArrayListVentas != NULL && (estado == COBRADA || estado == SIN_COBRAR))
	{
		retorno = ll_filter(pArrayListVentas, ventas_filterByStatus, &estado);
	}
	return retorno;
}
