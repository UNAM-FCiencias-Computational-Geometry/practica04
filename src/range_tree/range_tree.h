/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Contiene el conjunto de funciones y la estructura de los arboles de rango.
 */

#ifndef RANGE_TREE_H_
#define RANGE_TREE_H_

#include "points/2d_points.h"
#include "red_black_tree/rb_tree.h"
#include "double_linked_list/double_linked_list.h"

/**
 *         parent
 *          /
 *       ra_node [x_mid,tree_assoc]      
 *        /   \
 *      left right
 *
 * tree_assoc representa el arbol de busqueda binario(ordenado por el eje Y)
 *            asociado al nodo.
 *
 * x_mid es el punto que es la media del conjunto de puntos(con respecto
 *       al eje X)
 */
struct ra_node {
    vertex* x_mid;
	
	struct ra_node* left;
	struct ra_node* right;
	
	struct rb_tree* tree_assoc;
	 
};

/** Renombramos la estructura para un mejor uso. */
typedef struct ra_node ra_node;

/** Estructura que representa un árbol de rangos. */
struct ra_tree {
	struct ra_node* root;
};

/** Renombramos la estructura para un mejor uso. */
typedef struct ra_tree ra_tree;

/** Inicia y destruye nodos del arbol de rangos.*/
ra_node* init_ra_node(void);
void destroy_ra_node(ra_node* ra_node);

/** Inicializa y destruye la estructura del arbol de rangos. */
ra_tree* init_ra_tree(void);
void destroy_ra_tree(ra_tree* ra_tree);

/**
 * Funciones para crear un arbol de rangos, la primera es la que regresa ya el
 * arbol y la segunda es la que se manda a llamar de forma recursiva.
 */
ra_tree* build_2d_range_tree(list* set_of_points);
ra_node* build_2d_range_tree_node(list* set_of_points);

/**
 * Funciones para encontrar el nodo split, practicamente son iguales, pero 
 * por problemas de tipo tipo y campos hay que usar hacer dos funciones
 * distintas
 */
rb_node* find_split_node_1d(rb_tree* tree, double y, double y1);
ra_node* find_split_node_2d(ra_tree* ra_tree, double x, double x1);

/**
 * Funcion para hacer la busqueda de rango en un arbol rojo-negro.
 * tree es el arbol en el cual se hara la busqueda de rangos.
 * (y,y1) es el rango en el cual se hace la busqueda,
 * report_points es la lista donde se guardarn los puntos que esten en el rango,
 *               esa lista ya debe de estar inicializada antes de pasarsela a
 *               esta funcion.
 *
 * NOTA: Debe de estar ordenado por el eje Y.
 */
void one_d_range_query(rb_tree* tree, double y, double y1, list* report_points);

/**
 * Funcion para hacer la busqueda de rango en segunda dimension, recibe el
 * arbol y el rango donde se hace la busqueda.
 * Regresa la lista con los puntos dentro del arbol.
 */
list* two_d_range_query(ra_tree* ra_tree, double x, double x1,
						double y, double y1);

/**
 * Reporta los puntos dentro del arbol subtree y los guarda en la lista que
 * se le pasa.
 */
void report_tree(list* list_of_points, rb_node* subtree);

#endif
