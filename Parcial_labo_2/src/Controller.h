#include "LinkedList.h"

typedef struct
{
	int id;
	int estado;
}ArgumentosFiltro;

int controller_clienteLoadFromText(char* path , LinkedList* pArrayListCliente);
int controller_ventasLoadFromText(char* path , LinkedList* pArrayListVenta);
int controller_addCliente(LinkedList* pArrayListCliente);
int controller_addVenta(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente);
int controller_modifyVenta(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente);
int controller_cobrarVenta(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente);
int controller_generarInformeDeCobrosOrDeudas(char* path , LinkedList* pArrayListCliente, LinkedList* pArrayListVentas, int estado);
int controller_imprimirVentaConMasAfiches(LinkedList* pArrayListVentas, LinkedList* pArrayListCliente);
int controller_clienteSaveAsText(char* path , LinkedList* pArrayListCliente);
int controller_ventasSaveAsText(char* path , LinkedList* pArrayListVentas);
int controller_imprimirCliente(LinkedList* pArrayListCliente);
int controller_imprimirVentas(LinkedList* pArrayListVentas);



