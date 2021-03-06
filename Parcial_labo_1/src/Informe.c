/*
 * Informe.c
 * Author: Leandro Sobrino
 */
#include <stdio.h>
#include <stdlib.h>
#include "validaciones.h"
#include "Informe.h"
#include "Cliente.h"
#include "Aviso.h"

typedef struct
{
	int tipo;
	int isEmpty;
}Rubro;

static void info_init(Rubro* listRubro, int lenRubro);
static void info_generarListaDeRubro(Rubro* listRubro, int lenRubro, Aviso* list, int len);
static int info_estaEnMiListaDeRubro(Rubro* listRubro, int lenRubro, int rubro);
static int info_printRubroConMasAvisos(Aviso* list, int len, Rubro* listRubro, int lenRubro);
/**
 * \brief	Muestra el menu principal.
 * \param	int* pOption, puntero a un espacio de memoria.
 * \return	Retorna 0 (exito)y -1 (error).
 */
int utn_showMainMenu(int* pOption, Aviso* listAviso, int lenAviso, Cliente* listCliente, int lenCliente)
{
	int retorno = -1;
	int option;

	if(pOption != NULL && listAviso != NULL && lenAviso > 0 && listCliente != NULL && lenCliente  > 0)
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
									 "Ingrese la opcion: ", "Opcion ingresada invalida.\n", 1, OPTIONS_MAIN, 2) == 0 &&
		cli_findBusy(listCliente, lenCliente) != 0	&& (option > 1 && option < 9))
		{
			printf("Antes se debe ingresar un cliente.\n");
		}
		else
		{
			if(avi_findBusy(listAviso, lenAviso) != 0 && (option > 4 && option < 9))
			{
				printf("Antes se debe publicar un aviso.\n");
			}
			else
			{
				*pOption = option;
				retorno = 0;
			}
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
									"4- Cliente con mas avisos activos.\n"
									"5- Clientes con mas avisos pausados.\n"
									"6- Salir.\n\n"
									"Ingrese la opcion: ", "Opcion ingresada invalida.\n", 1, OPTIONS_REPORT, 2) == 0)
		{
			*pOption = option;
			retorno = 0;
		}
	}
	return retorno;
}
/**
 * \brief Imprime la lista de clientes.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int info_printClientes(Aviso* list, int len, Cliente* listCliente, int lenCliente)
{
    int retorno = -1;
    int contador;

    if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
    {
    	printf("ID     NOMBRE       APELLIDO        CUIT               AVISOS ACTIVOS\n");
        for(int i=0;i<lenCliente;i++)
        {
            if(listCliente[i].isEmpty == 0 && info_contarAvisosActivosPorId(list, len, listCliente[i].id, &contador) == 0)
            {
            	printf("%-6d %-12s %-15s %-18s %d \n"
            			,listCliente[i].id ,listCliente[i].name ,listCliente[i].lastName ,listCliente[i].cuit ,contador);
                retorno = 0;
            }
        }
    }
    return retorno;
}
/**
 * \brief Cuenta la cantidad de avisos activos segun id.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param int id, recibira el id del cliente.
 * \return (-1) Error / (0) Ok
 */
int info_contarAvisosActivosPorId(Aviso* list, int len, int id, int* pContador)
{
    int retorno = -1;
    int contadorActivos = 0;

    if(list != NULL && len > 0 && id > 0 && pContador != NULL)
    {
        for(int i=0;i<len;i++)
        {
            if(list[i].estado == 1 && list[i].isEmpty == 0 && list[i].idCliente == id)
            {
            	contadorActivos++;
            }
        }
        *pContador = contadorActivos;
        retorno = 0;
    }
    return retorno;
}
/**
 * \brief Cuenta la cantidad de avisos pausados segun id.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param int id, recibira el id del cliente.
 * \return (-1) Error / (0) Ok
 */
int info_contarAvisosPausadosPorId(Aviso* list, int len, int id, int* pContador)
{
    int retorno = -1;
    int contadorPausados = 0;

    if(list != NULL && len > 0 && id > 0 && pContador != NULL)
    {
        for(int i=0;i<len;i++)
        {
            if(list[i].estado == 0 && list[i].isEmpty == 0 && list[i].idCliente == id)
            {
            	contadorPausados++;
            }
        }
        *pContador = contadorPausados;
        retorno = 0;
    }
    return retorno;
}
/**
 * \brief Cuenta la cantidad de avisos segun id.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param int id, recibira el id del cliente.
 * \return (-1) Error / (0) Ok
 */
int info_contarAvisosPorId(Aviso* list, int len, int id,int* pContador)
{
    int retorno = -1;
    int contador = 0;

    if(list != NULL && len > 0 && id > 0)
    {
        for(int i=0;i<len;i++)
        {
            if(list[i].isEmpty == 0 && list[i].idCliente == id)
            {
            	contador++;
            }
        }
        *pContador = contador;
        retorno = 0;
    }
    return retorno;
}
/**
 * \brief Imprime el cliente que tenga mas avisos.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int info_printClientWithMoreAds(Aviso* list, int len, Cliente* listCliente, int lenCliente)
{
    int retorno = -1;
    Cliente aux;
    int contadorMaximo;
    int contadorAux;

    if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
    {
        for(int i=0;i<lenCliente;i++)
        {
            if( listCliente[i].isEmpty == 0 &&
				info_contarAvisosPorId(list, len, listCliente[i].id, &contadorAux) == 0 && (i == 0 || contadorAux >= contadorMaximo ))
            {
            	aux = listCliente[i];
            	contadorMaximo = contadorAux;
            }
        }
        printf("El cliente con mas avisos creados (%d) es %s %s - Cuit: %s.\n\n", contadorMaximo, aux.name, aux.lastName, aux.cuit);
        avi_printByIdCliente(list, len, listCliente, lenCliente, aux.id);
        retorno = 0;
    }
    return retorno;
}
/**
 * \brief Cuenta la cantidad de avisos pausados.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \return (-1) Error / (0) Ok
 */
int info_contarAvisosPausados(Aviso* list, int len)
{
    int retorno = -1;
    int contadorPausados = 0;

    if(list != NULL && len > 0)
    {
        for(int i=0;i<len;i++)
        {
            if(list[i].estado == 0 && list[i].isEmpty == 0)
            {
            	contadorPausados++;
            }
        }
        printf("La cantidad de avisos pausados es: %d.\n\n",contadorPausados);
        avi_mostrarAvisosPausadosOActivos(list, len, PAUSADO);
        retorno = 0;
    }
    return retorno;
}
/**
 * \brief Cuenta la cantidad de avisos por rubro.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param int id, recibira el id del cliente.
 * \return (-1) Error / (0) Ok
 */
int info_contarAvisosPorRubro(Aviso* list, int len, int rubro, int* pContador)
{
    int retorno = -1;
    int contador = 0;

    if(list != NULL && len > 0 && rubro > 0 && pContador != NULL)
    {
        for(int i=0;i<len;i++)
        {
            if(list[i].isEmpty == 0 && list[i].rubro == rubro)
            {
            	contador++;
            }
        }
        *pContador = contador;
        retorno = 0;
    }
    return retorno;
}
/**
 * \brief Inicializa el array .
 * \param Rubro* listRubro, Es el puntero al array.
 * \param int lenRubro, es el limite de array.
 */
static void info_init(Rubro* listRubro, int lenRubro)
{
	int i;

	if (listRubro != NULL && lenRubro > 0)
	{
		for (i = 0; i < lenRubro; i++)
		{
			listRubro[i].isEmpty = 1;
		}
	}
}
/**
 * \brief Se chequea si el rubro comparado ya se encuentra en la lista de rubros.
 * \param Rubro* listRubro, Es el puntero al array.
 * \param int lenRubro, es el limite de array.
 * \param int rubro, indica el rubro que se va a comparar
 * \return (-1) Error / (0) Ok
 */
static int info_estaEnMiListaDeRubro(Rubro* listRubro, int lenRubro, int rubro)
{
	int i;
	int retorno=0;

	if (listRubro != NULL && lenRubro > 0 && rubro > 0)
	{
		for(i=0; i<lenRubro; i++)
		{
			if(listRubro[i].isEmpty == 0 && listRubro[i].tipo == rubro)
			{
				retorno=1;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Genera la lista de rubros
 * \param Rubro* listRubro, Es el puntero al array.
 * \param int lenRubro, es el limite de array.
 * \param int rubro, indica el rubro que se va a comparar
 * \return (-1) Error / (0) Ok
 */
static void info_generarListaDeRubro(Rubro* listRubro, int lenRubro, Aviso* list, int len)
{
	int i;
	int indexRubro = 0;

	if (listRubro != NULL && lenRubro > 0 && list != NULL && len )
	{
		info_init(listRubro,lenRubro);
		for(i=0;i<len; i++)
		{
			if(info_estaEnMiListaDeRubro(listRubro, lenRubro, list[i].rubro) == 0 && list[i].isEmpty == 0)
			{
				listRubro[indexRubro].tipo = list[i].rubro;
				listRubro[indexRubro].isEmpty = 0;
				indexRubro++;
			}
		}
	}
}
/**
 * \brief Imprime el rubro que tenga mas avisos.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param int state, indica el estado de los avisos.
 * \return (-1) Error / (0) Ok
 */
static int info_printRubroConMasAvisos(Aviso* list, int len, Rubro* listRubro, int lenRubro)
{
    int retorno = -1;
    Rubro aux;
    int contadorMaximo;
    int contadorAux;

    if(list != NULL && len > 0 && listRubro != NULL && lenRubro > 0)
    {
        for(int i=0;i<lenRubro;i++)
        {
            if( listRubro[i].isEmpty == 0 &&
				info_contarAvisosPorRubro(list, len, listRubro[i].tipo, &contadorAux) == 0 && (i == 0 || contadorAux >= contadorMaximo))
            {
            	aux = listRubro[i];
            	contadorMaximo = contadorAux;
            }
        }
        printf("El rubro con mas avisos creados (%d) es el %d.\n", contadorMaximo, aux.tipo);
        retorno = 0;
    }
    return retorno;
}
/**
 * \brief Genera el informe sobre el rubro con mas avisos.
 * \param Rubro* listRubro, Es el puntero al array.
 * \param int lenRubro, es el limite de array.
 * \param int rubro, indica el rubro que se va a comparar
 * \return (-1) Error / (0) Ok
 */
int info_generarInformeDeRubro(Aviso* list)
{
	int retorno = -1;
	Rubro listRubro[QTY_AVI];

	if (list != NULL)
	{
		info_generarListaDeRubro(listRubro, QTY_AVI, list, QTY_AVI);
		info_printRubroConMasAvisos(list, QTY_AVI, listRubro, QTY_AVI);
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Imprime el cliente que tenga mas avisos activos.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int info_printClientWithMoreActivesAds(Aviso* list, int len, Cliente* listCliente, int lenCliente)
{
    int retorno = -1;
    Cliente aux;
    int contadorMaximo;
    int contadorAux;

    if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
    {
        for(int i=0;i<lenCliente;i++)
        {
            if( listCliente[i].isEmpty == 0 &&
				info_contarAvisosActivosPorId(list, len, listCliente[i].id, &contadorAux) == 0 && (i == 0 || contadorAux > contadorMaximo ))
            {
            	aux = listCliente[i];
            	contadorMaximo = contadorAux;
            }
        }
        if(contadorMaximo > 0)
		{
			printf("El cliente con mas avisos activos (%d) es %s %s - Cuit: %s - ID cliente: %d.\n\n",
					contadorMaximo, aux.name, aux.lastName, aux.cuit, aux.id);
			avi_mostrarAvisosPausadosOActivosPorId(list, len, ACTIVO, aux.id);
			retorno = 0;
		}
    }
    return retorno;
}
/**
 * \brief Imprime el cliente que tenga mas avisos pausados.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int info_printClientWithMoreInactivesAds(Aviso* list, int len, Cliente* listCliente, int lenCliente)
{
    int retorno = -1;
    Cliente aux;
    int contadorMaximo;
    int contadorAux;

    if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
    {
        for(int i=0;i<lenCliente;i++)
        {
            if( listCliente[i].isEmpty == 0 &&
				info_contarAvisosPausadosPorId(list, len, listCliente[i].id, &contadorAux) == 0 && (i == 0 || contadorAux > contadorMaximo ))
            {
            	aux = listCliente[i];
            	contadorMaximo = contadorAux;
            }
        }
        if(contadorMaximo > 0)
		{
			printf("El cliente con mas avisos pausados (%d) es %s %s - Cuit: %s - ID cliente: %d.\n\n"
					, contadorMaximo, aux.name, aux.lastName, aux.cuit, aux.id);
			avi_mostrarAvisosPausadosOActivosPorId(list, len, PAUSADO, aux.id);
			retorno = 0;
		}
    }
    return retorno;
}
