/*
 * Aviso.c
 * Author: Leandro Sobrino
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include "Aviso.h"
#include "Cliente.h"
#include "validaciones.h"

typedef struct
{
	int tipo;
	int isEmpty;
}Rubro;

static int generateNewId(void);
static void rub_init(Rubro* listRubro, int lenRubro);
static void rub_generarListaDeRubro(Rubro* listRubro, int lenRubro, Aviso* list);
static int rub_estaEnMiListaDeRubro(Rubro* listRubro, int lenRubro, int rubro);
static int rub_printRubroConMasAvisos(Aviso* list, int len, Rubro* listRubro);
/**
 * \brief Inicializa el array .
 * \param Aviso list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int avi_init(Aviso* list, int len)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			list[i].isEmpty = 1;
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Realiza el alta solo si el indice corresponde a un espacio vacio (isEmpty == 0)
 * \param Aviso* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \param int id, indica el id del elemento.
 * \return (-1) Error / (0) Ok
 */
int avi_add(Aviso* list, int len, Cliente* listCliente, int lenCliente)
{
	int retorno = -1;
	int index;
	int idCliente;
	int indexCliente;
	Aviso buffer;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
	{
		cli_print(listCliente, lenCliente);
		if( utn_getNumberInt(&idCliente, "Ingrese el id del cliente que publicara el aviso: ", "Error.\n", 1, INT_MAX, 2) == 0 &&
			cli_findById(listCliente, lenCliente, idCliente, &indexCliente) == 0 &&
			avi_findFree(list, len, &index) == 0 && index < len &&
			utn_getNumberInt(&buffer.rubro, "Ingrese el rubro del aviso: ", "Rubro invalido.\n", 1, QTY_AVI, 2) == 0 &&
			utn_getText(buffer.text, "Ingrese el texto que desea publicar: ", "Texto invalido.\n", 2, LONG_TEXTO) == 0)
		{
			buffer.isEmpty = 0;
			buffer.estado = ACTIVO;
			buffer.idAviso = generateNewId();
			list[index] = buffer;
			list[index].idCliente = listCliente[indexCliente].id;
			avi_show(list, index);
			retorno = 0;
		}
		else
		{
			printf("El id seleccionado no existe.\n");
		}
	}
	return retorno;
}
/**
 * \brief Busca el elemento por id y se guarda su indice en un puntero.
 * \param Aviso list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int id, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return Retorna el indice
 */
int avi_findById(Aviso* list, int len, int id, int* pIndex)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0 && pIndex != NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idAviso == id)
			{
				*pIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Elimina el elemento que de encuentra en el indice recibido.
 * \param Aviso* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \return (-1) Error / (0) Ok
 */
int avi_remove(Aviso* list, int len, Cliente* listCliente, int lenCliente)
{
	int retorno = -1;
	int idClienteRemove;
	int indexClienteRemove;
	int respuesta;
	int i;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
	{
		cli_print(listCliente, lenCliente);
		if( utn_getNumberInt(&idClienteRemove, "Ingrese el id del cliente que se quiere eliminar: ", "ID invalido.\n", 1, INT_MAX, 2) == 0 &&
			cli_findById(listCliente, lenCliente, idClienteRemove, &indexClienteRemove) == 0 && listCliente[indexClienteRemove].isEmpty == 0 &&
			avi_printByIdCliente(list, len, listCliente, lenCliente, idClienteRemove) == 0 &&
			utn_getNumberInt(&respuesta, "El cliente y sus avisos se borraran ¿Desea continuar? (1- Si/2- No): ", "Error.\n", SI, NO, 2) == 0)
 		{
			if(respuesta == 1)
			{
				for (i = 0; i < len; i++)
				{
					if(list[i].idCliente == idClienteRemove)
					{
						list[i].isEmpty = 1;
					}
				}
				cli_remove(listCliente, lenCliente, idClienteRemove);
				retorno = 0;
			}
			else
			{
				printf("Se cancelo la eliminación del cliente.\n");
			}
		}
		else
		{
			printf("No se puede borrar el cliente seleccionado.\n");
		}
	}
	return retorno;
}
/*
 * \ brief - Ordena el array por rubro.
 * \ param - Aviso* list, recibe el array a utilizar.
 * \ param - int len, indica la longitud del array.
 * \ param - int order, indica el orden de los elementos. 1 en caso de ascendente y 0 en caso de descendente.
 * \ return - (-1) en caso de error / (0) en caso de funcionar.
 */
int avi_sortByRubro(Aviso* list, int len, int order)
{
	int retorno = -1;
	int i;
	Aviso aux;
	int flagSwap = 1;
	if(list != NULL && len > 0)
	{
		while(flagSwap)
		{
			flagSwap = 0;
			for (i = 0; i < (len - 1); i++)
			{
				if(	(order == 1 &&
					list[i].rubro < list[i+1].rubro) ||
					(order == 0 &&
					list[i].rubro > list[i+1].rubro))
				{
					aux = list[i];
					list[i] = list[i+1];
					list[i+1] = aux;
					flagSwap = 1;
				}
			}
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Imprime los datos cargados.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \param int id, recibira el id del cliente.
 * \return (-1) Error / (0) Ok
 */
int avi_printByIdCliente(Aviso* list, int len, Cliente* listCliente, int lenCliente, int id)
{
	int retorno = -1;
	int i;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0 && id > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && list[i].idCliente == id)
			{
				printf("ID del cliente: %d- ID del aviso: %d  - Texto: %s - Rubro: %d.\n",
						list[i].idCliente, list[i].idAviso, list[i].text, list[i].rubro);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/**
 * \brief Muestra un elemento del array por el indice recibido.
 * \param Cliente* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int index, recibe un indice del array.
 * \return (-1) Error / (0) Ok
 */
int avi_show(Aviso* list,int index)
{
	int retorno = -1;

	if(list != NULL && index >= 0 )
	{
		if(list[index].isEmpty==0)
		{
			printf("ID del aviso: %d  - Texto: %s - Rubro: %d.\n",
					list[index].idAviso, list[index].text, list[index].rubro);
			retorno = 0;
		}
		else
		{
			printf("El aviso no existe.");
		}
	}
	return retorno;
}
/**
 * \brief Busca un espacio libre en el array.
 * \param Aviso* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int avi_findFree(Aviso* list, int len, int* pIndex)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0 && pIndex!= NULL)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 1)
			{
				*pIndex = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Busca un espacio ocupado en el array.
 * \param Aviso* list, Es el puntero al array.
 * \param int len, es el limite de array.
 * \param int* pIndex, puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int avi_findOccupied(Aviso* list, int len)
{
	int retorno = -1;
	int i;

	if (list != NULL && len > 0)
	{
		for (i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief Imprime los avisos activos o pausados.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param int state, indica el estado de los avisos.
 * \return (-1) Error / (0) Ok
 */
int avi_mostrarAvisosPausadosOActivos(Aviso* list, int len, int state)
{
    int retorno = -1;

    if(list != NULL && len > 0 && (state >= 0 || state <= 1))
    {
        for(int i=0;i<len;i++)
        {
            if(list[i].estado == state && list[i].isEmpty == 0)
            {
            	avi_show(list, i);
                retorno = 0;
            }
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
int avi_printClientes(Aviso* list, int len, Cliente* listCliente, int lenCliente)
{
    int retorno = -1;
    int contador;

    if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
    {
    	printf("ID     NOMBRE       APELLIDO        CUIT               AVISOS ACTIVOS\n");
        for(int i=0;i<lenCliente;i++)
        {
            if(listCliente[i].isEmpty == 0 && avi_contarAvisosActivosPorId(list, len, listCliente[i].id, &contador) == 0)
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
 * \brief Cambia el estado del aviso a pausado o activo segun corresponda.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param Cliente* listCliente, Es el puntero al array.
 * \param int lenCliente, es el limite de array.
 * \param int state, indica el estado de los avisos.
 * \return (-1) Error / (0) Ok
 */
int avi_changeState(Aviso* list, int len, Cliente* listCliente, int lenCliente, int state)
{
	int retorno = -1;
	int idChange;
	int indexChange;
	int indexCliente;
	int respuesta;

	if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0 && (state >= 0 || state <= 1))
	{
		avi_mostrarAvisosPausadosOActivos(list, len, !state);
		if( ((state == 1 && utn_getNumberInt(&idChange, "Ingrese el ID del aviso que quiere reanudar: ", "ID invalido.\n", 1, INT_MAX, 2) == 0 &&
			avi_findById(list, len, idChange, &indexChange) == 0 && list[indexChange].estado != state &&
			cli_findById(listCliente, lenCliente, list[indexChange].idCliente, &indexCliente) == 0 && cli_show(listCliente, indexCliente) == 0)
				||
			(state == 0 && utn_getNumberInt(&idChange, "Ingrese el id del aviso que quiere pausar: ", "ID invalido.\n", 1, INT_MAX, 2) == 0 &&
			avi_findById(list, len, idChange, &indexChange) == 0 && list[indexChange].estado != state
			&& cli_findById(listCliente, lenCliente, list[indexChange].idCliente, &indexCliente) == 0 && cli_show(listCliente, indexCliente) == 0)) &&
			utn_getNumberInt(&respuesta, "¿Desea cambiar el estado del aviso? (1- Si/2- No): ", "Error.\n", SI, NO, 2) == 0)
		{
			if(respuesta == 1)
			{
				list[indexChange].estado = state;
				retorno = 0;
			}
			else
			{
				printf("Se cancelo el cambio de estado del aviso.\n");
			}
		}
		else
		{
			printf("No se puede cambiar el estado del ID seleccionado.\n");
		}
	}
	return retorno;
}
/**
 * \brief Cuenta la cantidad de avisos pausados.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \return (-1) Error / (0) Ok
 */
int avi_contarAvisosPausados(Aviso* list, int len)
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
        printf("La cantidad de avisos pausados es: %d.\n",contadorPausados);
        retorno = 0;
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
int avi_contarAvisosActivosPorId(Aviso* list, int len, int id, int* pContador)
{
    int retorno = -1;
    int contadorActivos = 0;

    if(list != NULL && len > 0 && id > 0)
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
 * \brief Cuenta la cantidad de avisos segun id.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param int id, recibira el id del cliente.
 * \return (-1) Error / (0) Ok
 */
int avi_contarAvisosPorId(Aviso* list, int len, int id,int* pContador)
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
 * \brief Cuenta la cantidad de avisos por rubro.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param int id, recibira el id del cliente.
 * \return (-1) Error / (0) Ok
 */
int avi_contarAvisosPorRubro(Aviso* list, int len, int rubro, int* pContador)
{
    int retorno = -1;
    int contador = 0;

    if(list != NULL && len > 0 && rubro > 0)
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
 * \brief Imprime el cliente que tenga mas avisos.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param int state, indica el estado de los avisos.
 * \return (-1) Error / (0) Ok
 */
int avi_printClientWithMoreAdvices(Aviso* list, int len, Cliente* listCliente, int lenCliente)
{
    int retorno = -1;
    Cliente aux;
    int contadorMaximo = 0;
    int contadorAux;

    if(list != NULL && len > 0 && listCliente != NULL && lenCliente  > 0)
    {
        for(int i=0;i<lenCliente;i++)
        {
            if( listCliente[i].isEmpty == 0 &&
				avi_contarAvisosPorId(list, len, listCliente[i].id, &contadorAux) == 0 && contadorAux >= contadorMaximo)
            {
            	aux = listCliente[i];
            	contadorMaximo = contadorAux;
            }
        }
        printf("El cliente con mas avisos creados (%d) es %s %s - Cuit: %s.\n", contadorMaximo, aux.name, aux.lastName, aux.cuit);
        retorno = 0;
    }
    return retorno;
}
/**
 * \brief Imprime el rubro que tenga mas avisos.
 * \param Aviso* list, Es el puntero al array
 * \param int len, es el limite de array
 * \param int state, indica el estado de los avisos.
 * \return (-1) Error / (0) Ok
 */
static int rub_printRubroConMasAvisos(Aviso* list, int len, Rubro* listRubro)
{
    int retorno = -1;
    Aviso aux;
    int contadorMaximo = 0;
    int contadorAux;

    if(list != NULL && len > 0)
    {
        for(int i=0;i<len;i++)
        {
            if( list[i].isEmpty == 0 &&
				avi_contarAvisosPorRubro(list, len, list[i].rubro, &contadorAux) == 0 && contadorAux >= contadorMaximo)
            {
            	aux = list[i];
            	contadorMaximo = contadorAux;
            }
        }
        printf("El rubro con mas avisos creados (%d) es el %d.\n", contadorMaximo, aux.rubro);
        retorno = 0;
    }
    return retorno;
}
/**
 * \brief Realiza un alta forzada de un elemento.
 * \param Cliente* list, Es el puntero al array.
 * \param int len, es el limite de array
 * \param int idCliente, indica el id del cliente.
 * \param int rubro, indica el rubro del aviso.
 * \param char* texto, Puntero al espacio de memoria.
 * \return (-1) Error / (0) Ok
 */
int avi_altaForzada(Aviso* list, int len, int idCliente, int rubro, char* texto)
{
    int retorno = -1;
    int index;

    if(list != NULL && len > 0 && idCliente > 0 && rubro > 0 && texto != NULL)
    {
		if(avi_findFree(list, len, &index) == 0)
		{
			strncpy(list[index].text, texto, LONG_TEXTO);
			list[index].idCliente = idCliente;
			list[index].rubro = rubro;
			list[index].estado = ACTIVO;
			list[index].idAviso = generateNewId();
			list[index].isEmpty = 0;
			retorno = 0;
		}
    }
    return retorno;
}
/**
 * \brief Incrementa el id y lo retorna.
 * \return Retorna el id
 */
static int generateNewId(void)
{
	static int id = 0;

	id++;
	return id;
}
/**
 * \brief Inicializa el array .
 * \param Rubro* listRubro, Es el puntero al array.
 * \param int lenRubro, es el limite de array.
 */
static void rub_init(Rubro* listRubro, int lenRubro)
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
static int rub_estaEnMiListaDeRubro(Rubro* listRubro, int lenRubro, int rubro)
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
static void rub_generarListaDeRubro(Rubro* listRubro, int lenRubro, Aviso* list)
{
	int i;
	int indexRubro = 0;

	if (listRubro != NULL && lenRubro > 0 && list != NULL)
	{
		rub_init(listRubro,lenRubro);
		for(i=0;i<lenRubro; i++)
		{
			if(rub_estaEnMiListaDeRubro(listRubro, lenRubro, list[i].rubro) == 0)
			{
				listRubro[i].tipo = list[i].rubro;
				listRubro[indexRubro].isEmpty = 0;
				indexRubro++;
			}
		}
	}
}
/**
 * \brief Genera la lista de rubros
 * \param Rubro* listRubro, Es el puntero al array.
 * \param int lenRubro, es el limite de array.
 * \param int rubro, indica el rubro que se va a comparar
 * \return (-1) Error / (0) Ok
 */
int rub_generarInformeDeRubro(Aviso* list)
{
	int retorno = -1;
	Rubro listRubro[QTY_AVI];

	if (list != NULL)
	{
		rub_generarListaDeRubro(listRubro, QTY_AVI, list);
		rub_printRubroConMasAvisos(list, QTY_AVI, listRubro);
		retorno = 0;
	}
	return retorno;
}
