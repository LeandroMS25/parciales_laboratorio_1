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
			!(cliente_findCuitRepetido(pArrayListCliente, auxCuit)) &&
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
			cliente_findById(pArrayListCliente, idCliente) &&
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
			ventas_findIndexById(pArrayListVentas, auxId, SIN_COBRAR, &indexModify) == 0 &&
			!(ventas_getIdCliente(ll_get(pArrayListVentas, indexModify), &idCliente)) && cliente_findIdAndPrint(pArrayListCliente, idCliente))
		{
			auxVenta = ll_get(pArrayListVentas, indexModify);
			if(utn_getNumberInt(&option, "¿Desea seguir con el cobro de la venta? (1- SI | 2- NO): ", "ID incorrecto.\n", 1, 2, 2) == 0
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
		ll_map(pArrayListVentas, ventas_imprimirSinCobrar);
		if( utn_getNumberInt(&auxId, "Seleccione el ID de la venta que quiere modificar: ", "ID incorrecto.\n", 0, INT_MAX, 2) == 0 &&
			ventas_findIndexById(pArrayListVentas, auxId, SIN_COBRAR, &indexModify) == 0 &&
			!(ventas_getIdCliente(ll_get(pArrayListVentas, indexModify), &idCliente)) && cliente_findIdAndPrint(pArrayListCliente, idCliente) &&
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
}
*/
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
/** \brief Imprime la venta con mas afiches.
 *
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_imprimirVentaConMasAfiches(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Ventas* auxVenta;
	int cantAfiches, cantMaxima, auxId, idCliente/*, auxEstado*/;

	if(pArrayListVentas != NULL && pArrayListCliente != NULL)
	{
		for (int i = 0; i < ll_len(pArrayListVentas); i++)
		{
			auxVenta = ll_get(pArrayListVentas, i);
			ventas_getCantAfiches(auxVenta, &cantAfiches);
			//ventas_getEstado(auxVenta, &auxEstado);
			if(i == 0 || /*(auxEstado == 1 &&*/ cantAfiches > cantMaxima)
			{
				cantMaxima = cantAfiches;
				ventas_getIdVentas(auxVenta, &auxId);
				ventas_getIdCliente(auxVenta, &idCliente);
			}
		}
		printf("\n3- El ID de la venta con mas afiches es el %d con %d afiches.\n",auxId,cantMaxima);
		printf("El/La cliente que hizo la compra fue: ");
		cliente_findIdAndPrint(pArrayListCliente, idCliente);
		retorno = 0;
	}
	return retorno;
}
/** \brief Imprime el cliente al que se le vendio mas y menos afiches (el parametro limite indica MAXIMO o MINIMO).
 *
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \param int limite, recibe MAXIMO o MINIMO.
 * \return (-1) Error / (0) Ok
 *
 *//*
int controller_imprimirClienteConMasOrMenosAfichesConLimite(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente, int limite)
{
	int retorno = -1;
	Cliente* auxCliente;
	int cantAfiches, cantLimite, idLimite, idCliente;

	if(pArrayListVentas != NULL && pArrayListCliente != NULL && (limite == COBRADA || limite == SIN_COBRAR))
	{
		for (int i = 0; i < ll_len(pArrayListCliente); i++)
		{
			auxCliente = ll_get(pArrayListCliente, i);
			cliente_getIdCliente(auxCliente, &idCliente);
			cantAfiches = ll_reduceInt(pArrayListVentas, ventas_calcularCantidadAfiches, &idCliente);
			if( cantAfiches != 0 &&
				((limite == MAXIMO && (i == 0 || cantAfiches > cantLimite)) ||
				(limite == MINIMO && (i == 0 || cantAfiches < cantLimite))))
			{
				cantLimite = cantAfiches;
				idLimite = idCliente;
			}
		}
		if(limite == MAXIMO)
		{
			printf("\n1- El/La cliente al que se le vendio mas afiches fue: ");
			cliente_findIdAndPrint(pArrayListCliente, idLimite);
		}
		else
		{
			printf("\n2- El/La cliente al que se le vendio menos afiches fue: ");
			cliente_findIdAndPrint(pArrayListCliente, idLimite);
		}
		printf(" con %d afiches.",cantLimite);
		retorno = 0;
	}
	return retorno;
}
*/
/** \brief Imprime el cliente al que se le vendio mas y menos afiches.
 *
 * \param LinkedList* pArrayListCliente, recibe el array.
 * \param LinkedList* pArrayListVentas, recibe el array.
 * \return (-1) Error / (0) Ok
 *
 */
int controller_imprimirClienteConMasOrMenosAfiches(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Cliente* auxCliente;
	int cantAfiches, maximo, minimo, idMaximo, idMinimo, idCliente;

	if(pArrayListVentas != NULL && pArrayListCliente != NULL)
	{
		for (int i = 0; i < ll_len(pArrayListCliente); i++)
		{
			auxCliente = ll_get(pArrayListCliente, i);
			cliente_getIdCliente(auxCliente, &idCliente);
			cantAfiches = ll_reduceInt(pArrayListVentas, ventas_calcularCantidadAfiches, &idCliente);
			if(cantAfiches != 0)
			{
				if(i == 0 || cantAfiches > maximo)
				{
					maximo = cantAfiches;
					idMaximo = idCliente;
				}
				if(i == 0 || cantAfiches < minimo)
				{
					minimo = cantAfiches;
					idMinimo = idCliente;
				}
			}
		}
		printf("\n1- El/La cliente al que se le vendio mas afiches fue: ");
		cliente_findIdAndPrint(pArrayListCliente, idMaximo);
		printf(" con %d afiches.",maximo);
		printf("\n2- El/La cliente al que se le vendio menos afiches fue: ");
		cliente_findIdAndPrint(pArrayListCliente, idMinimo);
		printf(" con %d afiches.",minimo);
		retorno = 0;
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
