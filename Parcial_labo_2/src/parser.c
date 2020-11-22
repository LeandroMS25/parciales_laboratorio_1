#include <stdio.h>
#include <stdlib.h>
#include "Cliente.h"
#include "Ventas.h"
#include "LinkedList.h"

/** \brief Parsea los datos de los clientes desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEnvio LinkedList*
 * \return int
 *
 */
int parser_clienteFromText(FILE* pFile , LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Cliente* auxCliente;
	int r;
	char var1[4096], var2[4096], var3[4096], var4[4096];

	if(pFile != NULL && pArrayListCliente != NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",var1,var2,var3,var4);
		do
		{
			r = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",var1,var2,var3,var4);
			auxCliente = cliente_newParam(var1, var2, var3, var4);
			if(auxCliente != NULL)
			{
				if(r == 4)
				{
					ll_add(pArrayListCliente, auxCliente);
					retorno = 0;
				}
				else
				{
					cliente_delete(auxCliente);
				}
			}
			else
			{
				printf("Cliente NULL");
			}
		}while(!feof(pFile));
	}
    return retorno;
}

/** \brief Parsea los datos de las ventas desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEnvio LinkedList*
 * \return int
 *
 */
int parser_ventasFromText(FILE* pFile , LinkedList* pArrayListVenta)
{
	int retorno = -1;
	Ventas* auxVenta;
	int r;
	char var1[4096], var2[4096], var3[4096], var4[4096], var5[4096], var6[4096];

	if(pFile != NULL && pArrayListVenta != NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",var1,var2,var3,var4,var5,var6);
		do
		{
			r = fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",var1,var2,var3,var4,var5,var6);
			auxVenta = ventas_newParam(var1, var2, var3, var4, var5, var6);
			if(auxVenta != NULL)
			{
				if(r == 6)
				{
					ll_add(pArrayListVenta, auxVenta);
					retorno = 0;
				}
				else
				{
					ventas_delete(auxVenta);
				}
			}
			else
			{
				printf("Venta NULL");
			}
		}while(!feof(pFile));
	}
    return retorno;
}
