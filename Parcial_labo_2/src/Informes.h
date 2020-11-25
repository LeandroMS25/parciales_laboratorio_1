/*
 * Informes.h
 *
 *  Created on: 25 nov. 2020
 *      Author: Leandro Sobrino
 */

#ifndef INFORMES_H_
#define INFORMES_H_

int informes_imprimirVentaConMasAfiches(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente);
// int informes_imprimirClienteConMasOrMenosAfichesConLimite(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente, int limite);
int informes_imprimirClienteConMasOrMenosAfiches(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente);

#endif /* INFORMES_H_ */
