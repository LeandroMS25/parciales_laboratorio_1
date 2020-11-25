#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
	LinkedList* this = (LinkedList*)malloc(sizeof(LinkedList));

	if(this != NULL)
	{
		this->pFirstNode = NULL;
		this->size = 0;
	}
	return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* auxNode = NULL;

	if (this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))
	{
		auxNode = this->pFirstNode;
		for (int i = 0; i < nodeIndex; i++)
		{
			auxNode = auxNode->pNextNode;
		}
	}
	return auxNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	int returnAux = -1;
    Node* newNode;
    Node* prevNode;

    newNode = (Node*) malloc(sizeof(Node));
    if (this != NULL && newNode != NULL && nodeIndex >= 0 && nodeIndex <= this->size)
	{
		newNode->pElement = pElement;
		if(nodeIndex == 0)
		{
			newNode->pNextNode = this->pFirstNode;
			this->pFirstNode = newNode;
		}
		else
		{
			prevNode = getNode(this, nodeIndex - 1);
			if(prevNode != NULL)
			{
				newNode->pNextNode = prevNode->pNextNode;
				prevNode->pNextNode = newNode;
			}
		}
		this->size++;
		returnAux = 0;
	}
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
	/*
    int returnAux = -1;
    Node* auxNode = (Node*) malloc(sizeof(Node));
    Node* prevNode;

    if(this != NULL && auxNode != NULL)
    {
    	prevNode = getNode(this, this->size - 1);
    	auxNode->pElement = pElement;
    	if(prevNode != NULL)
		{
    		prevNode->pNextNode = auxNode;
		}
    	else
    	{
    		this->pFirstNode = auxNode;
    	}
    	this->size++;
    	returnAux = 0;
    }
    return returnAux;
	*/
	int returnAux = -1;
	if(this!=NULL)
	{
		if(addNode(this, ll_len(this), pElement)==0)
		{
			returnAux = 0;
		}
	}
	return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxNode;

    if(this != NULL && index >= 0 && index < this->size)
    {
		auxNode = getNode(this, index);
		if(auxNode != NULL)
		{
			returnAux = auxNode->pElement;
		}
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
	int returnAux = -1;
	Node* auxNode;

	if(this != NULL && index >= 0 && index < this->size)
	{
		auxNode = getNode(this, index);
		if(auxNode != NULL)
		{
			auxNode->pElement = pElement;
			returnAux = 0;
		}
	}
	return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
	int returnAux = -1;
	Node* deleteNode = getNode(this, index);
	Node* prevNode;

	if(this != NULL && (index >= 0 && index < ll_len(this)) && deleteNode != NULL)
	{
		prevNode = getNode(this, index - 1);
		if(prevNode != NULL)
		{
			prevNode->pNextNode = deleteNode->pNextNode;
		}
		else
		{
			this->pFirstNode = deleteNode->pNextNode;
		}
		free(deleteNode);
		this->size--;
		returnAux = 0;
	}
	return returnAux;
}
/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL && this->size > 0)
    {
    	for (int i = this->size - 1; i >= 0; i--)
    	{
    		ll_remove(this, i);
		}
    	returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

	if(this != NULL && ll_clear(this) == 0)
	{
		free(this);
		returnAux = 0;
	}
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    void* auxElement;

    if(this != NULL && this->size > 0)
    {
    	for (int i = 0; i < this->size; i++)
    	{
    		auxElement = ll_get(this, i);
    		if(auxElement == pElement)
    		{
    			returnAux = i;
    			break;
    		}
		}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
    	if(this->size == 0)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this != NULL && index >= 0 && index <= this->size)
    {
    	if(addNode(this, index, pElement) == 0)
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;

    if(this != NULL && index >= 0 && index < this->size)
    {
    	returnAux = ll_get(this, index);
    	ll_remove(this, index);
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
	int returnAux = -1;

	if(this != NULL)
	{
		if(ll_indexOf(this, pElement) != -1)
		{
			returnAux = 1;
		}
		else
		{
			returnAux = 0;
		}
	}
	return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    void* auxElement;
    int contadorIguales = 0;

    if(this != NULL && this2 != NULL)
    {
    	returnAux = 0;
    	if(this->size >= this2->size)
    	{
    		for (int i = 0; i < this->size; i++)
    		{
    			auxElement = ll_get(this2, i);
    			if(ll_contains(this, auxElement) == 1)
    			{
    				contadorIguales++;
    			}
    			else
    			{
    				break; // Por si alguno no se encuentra en la primer lista.
    			}
			}
    		if(contadorIguales == this2->size)
    		{
    			returnAux = 1;
    		}
    	}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* pElement;

    if(this != NULL && from >= 0 && from <= to && to <= this->size)
    {
    	cloneArray = ll_newLinkedList();
    	for (int i = from; i <= to; i++)
    	{
    		pElement = ll_get(this, i);
    		if(pElement != NULL)
    		{
				ll_add(cloneArray, pElement);
			}
		}
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL)
    {
    	cloneArray = ll_subList(this, 0, this->size);
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    void* elementX;
    void* elementY;
    int flagSwap = 1;

    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))
    {
    	while(flagSwap)
    	{
    		flagSwap = 0;
    		for (int i = 0; i < this->size - 1; i++)
			{
				elementX = ll_get(this, i);
				elementY = ll_get(this, i+1);
				if( elementX != NULL && elementY != NULL &&
					((order == 0 && pFunc(elementX,elementY) < 0) ||
					(order == 1 && pFunc(elementX,elementY) > 0)))
				{
					ll_set(this, i, elementY);
					ll_set(this, i+1, elementX);
					flagSwap = 1;
				}
			}
    	}
    	returnAux = 0;
    }
    return returnAux;
}
/** \brief Recorre la lista y actua de acuerdo a lo que haya en la funcion criterio.
 * \param this LinkedList* Puntero a la lista
 * \param void (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_map(LinkedList* this, void (*pFunc)(void*))
{
    int returnAux = -1;
    int len = ll_len(this);
    void* pElement;

    if(this != NULL && pFunc != NULL)
    {
    	for (int i= 0; i < len; i++)
    	{
    		pElement = ll_get(this, i);
    		pFunc(pElement);
    		returnAux = 0;
		}
    }
    return returnAux;
}
/** \brief Recorre la lista y actua de acuerdo a lo que haya en la funcion criterio.
 * \param this LinkedList* Puntero a la lista.
 * \param void (*pFunc) Puntero a la funcion criterio.
 * \param void* arg, Puntero al espacio de memorio del argumento.
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_mapArg(LinkedList* this, int (*pFunc)(void*,void*), void* arg)
{
    int returnAux = -1;
    int len = ll_len(this);
    void* pElement;

    if(this != NULL && pFunc != NULL)
    {
    	for (int i= 0; i < len; i++)
    	{
    		pElement = ll_get(this, i);
    		if(pFunc(pElement, arg) == 1)
    		{
    			returnAux = 0;
    		}
    	}
    }
    return returnAux;
}
/** \brief Recorre el arrayList y llama una funcion para filtrar elementos.
 * \param this LinkedList* Puntero a la lista
 * \param int (*pFunc) Puntero a la funcion criterio
 * \return int Retorna una Linkedlist.
 */
LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*,void*), void* arg)
{
	//LinkedList* newList = ll_clone(this);
	int len = ll_len(this);
	void* pElement;

	if(this != NULL && pFunc != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			pElement = ll_get(this, i);
			if(pFunc(pElement,arg) == 1)
			{
				ll_remove(this, i);
				i--;
			}
		}
	}
	return this;
}
/** \brief Recorre la lista y acumula valores de tipo float.
 * \param this LinkedList* Puntero a la lista
 * \param int (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
float ll_reduceFloat(LinkedList* this, float (*pFunc)(void*))
{
	int returnAux = -1;
	int len = ll_len(this);
	void* pElement;

	if(this != NULL && pFunc != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			pElement = ll_get(this, i);
			returnAux += pFunc(pElement);
		}
	}
	return returnAux;
}
/** \brief Recorre la lista y acumula valores de tipo int.
 * \param this LinkedList* Puntero a la lista
 * \param int (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_reduceInt(LinkedList* this, int (*pFunc)(void*,void*), void* arg)
{
	int returnAux = 0;
	int len = ll_len(this);
	void* pElement;

	if(this != NULL && pFunc != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			pElement = ll_get(this, i);
			returnAux += pFunc(pElement, arg);
		}
	}
	return returnAux;
}
