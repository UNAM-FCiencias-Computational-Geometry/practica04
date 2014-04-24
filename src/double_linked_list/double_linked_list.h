/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Una lista doblemente ligada que sirve como stack y como queue.
 * Sirve para tener listas de puntos o segmentos, se le indica 
 * al inicar la lista.
 */

#ifndef DOUBLE_LINKED_LIST_H_
#define DOUBLE_LINKED_LIST_H_

#include "points/2d_points.h"


/**
 *  |-----------|   left |-----------|  right |-----------|
 *  |           | <----- | list_item | -----> |           |
 *  |-----------|        |-----------|        |-----------|
 */
struct list_item {
	/**
	 * Apunto de cualquier tipo para representar puntos, segmentos o caras,
	 * para obtener la estructura original debes de hacer un cast. 
	*/
	vertex* element;
	struct list_item* left;
	struct list_item* right;   	
};

/**
 * |------------|                     |------------|
 * |    head    | ----->  .... <----- |    tail    |
 * |------------|                     |------------|
 */
struct double_linked_list {
	struct list_item* head;
	struct list_item* tail;

	/** Numero de elementos que tiene dentro la lista. */
	int size;
};

/**
 * Renombramos las dos estructuras anteriores, para usarlas de 
 * forma más sencilla.
 */
typedef struct list_item item;
typedef struct double_linked_list list;

/** Inicializa una lista con sus apuntadores nulos. */
list* init_double_linked_list();

/** Destruye una lista liberando la memoria de sus elementos. */
void destroy_double_linked_list(list* list);

/* Inicializa un elemento de la lista. **/
item* init_list_item(void);

/* Destruye solo un elemento de la lista. **/
void destroy_list_item(item* item);

/** Hace una copia de la lista dada, sin hacer copia de los elementos. */
list* create_copy_list(list* list);

/* Indica si la lista que se le pasa esta vacía. **/
int empty_list(list* list);

/* Agrega un nuevo punto o segmento al frente o hasta el final de la lista. **/
void push_back(list* list, vertex* element);
void push_front(list* list, vertex* element);

/**
 * Quita un punto o segmento al frente o hasta el final de la lista, regresa nulo
 * si la lista esta vacia. El apuntador que regresa esta funcion debe de castearse
 * antes de ser usado en otra funcion.
 */
vertex* pop_back(list* list);
vertex* pop_front(list* list);

/**
 * Regresa el punto o segmento que esta al frente o al final de la lista.
 * El apuntador que regresa esta funcion debe de castearse anrtes de ser usado
 * en otra funcion.
 */
vertex* pick_back(list* list);
vertex* pick_front(list* list);

#endif
