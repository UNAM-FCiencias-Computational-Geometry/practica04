/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 */

#include "red_black_tree/rb_tree.h"

#include "points/2d_points.h"
#include "double_linked_list/double_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

rb_node sentinel = {NULL,NULL,NULL,BLACK,NULL,NULL,NULL};

/**  Verifica si el arbol que se le pase esta vacio o no.*/
int empty_rb_tree(struct rb_tree* tree)
{
	if (tree == NULL)
		return tree == NULL;

	return tree->size == 0;
}

/**
 * Toma el nodo tmp1 y le aplica una rotacion hacia la izquierda.
 *
 *     tmp1                   tmp2
 *     / \                    /	\
 *	  *  tmp2        -->    tmp1 *
 *       / \                / \
 *      c   *              *   c
 */
void left_rotate(rb_tree* tree, rb_node* node)
{
	struct rb_node *tmp1, *tmp2;
	tmp1 = node;
	tmp2 = node->right;
	
	tmp1->right = tmp2->left;
	
	if (tmp2->left != &sentinel) 
		tmp2->left->parent = tmp1;

	tmp2->parent = tmp1->parent;

	if (tmp1->parent == &sentinel) {
		tree->root = tmp2;
	} else if (tmp1 == tmp1->parent->left) {
		tmp1->parent->left = tmp2;
	} else {
		tmp1->parent->right = tmp2;
	}

	tmp2->left = tmp1;
	tmp1->parent = tmp2;
}

/** Toma el nodo tmp1 y le aplica una rotacion hacia la derecha .
 *
 *     tmp1             tmp2
 *     / \              / \
 *   tmp2 *    -->     * tmp1
 *   / \                  /	\
 *	*   c                c   *
 */
void right_rotate(rb_tree* tree, rb_node* node)
{
	struct rb_node *tmp1, *tmp2;
	tmp1 = node;
	tmp2 = node->left;

	tmp1->left = tmp2->right;

	if (tmp2->right != &sentinel)
		tmp2->right->parent = tmp1;

	tmp2->parent = tmp1->parent;

	if (tmp1->parent == &sentinel) {
		tree->root = tmp2;
	} else if(tmp1 == tmp1->parent->left) {
		tmp1->parent->left = tmp2;
	} else {
		tmp1->parent->right = tmp2;
	}
	
	tmp2->right = tmp1;
	tmp1->parent = tmp2;
}

/**
 * Compone el arbol una vez que se inserta un nodo como hoja y descompone
 * las propiedades del arbol.
 */
void rb_insert_fixup(rb_tree* tree, rb_node* node)
{

	struct rb_node *tmp1, *tmp2;
	tmp1 = node;

	while (tmp1->parent->color == RED) {
		/** El padre de node es hijo izquierdo. */
		if (tmp1->parent == tmp1->parent->parent->left) {
			
			/** tmp es el tío derecho del padre de node*/
			tmp2 = tmp1->parent->parent->right;
			
			/** Caso 1: tmp tiene color rojo. */
			if (tmp2->color == RED) {
				
				tmp1->parent->color = BLACK;
				tmp2->color = BLACK;
				tmp1->parent->parent->color = RED;
				
				tmp1 = tmp1->parent->parent;
				
			} else {
				/** Caso 2: tmp tiene color negro y node es hijo derecho.
				 *  convertimos el caso 2 en el caso 3.
				 */
				if ( tmp1 == tmp1->parent->right) {
					tmp1 = tmp1->parent;
					left_rotate(tree, tmp1);
				}

				/** Caso 3: tmp tiene color negro y node es hijo izquierdo.*/
				tmp1->parent->color = BLACK;
				tmp1->parent->parent->color = RED;

				right_rotate(tree,tmp1->parent->parent);
			}

		} else {
			/** tmp es el tío izquierdo del padre de node.*/
			tmp2 = tmp1->parent->parent->left;

			/** Caso 1: tmp tiene color rojo*/
			if (tmp2->color == RED) {
				
				tmp1->parent->color = BLACK;
				tmp2->color = BLACK;
				tmp1->parent->parent->color = RED;
				
				tmp1 = tmp1->parent->parent;
				
			} else {
				/** Caso 2: tmp tiene color negro y node es hijo izquierdo.
				 *  convertimos el caso 2 en el caso 3.
				 */
				if ( tmp1 == tmp1->parent->left) {
					tmp1 = tmp1->parent;
					right_rotate(tree, tmp1);
				}

				/** Caso 3: tmp tiene color negro y node es hujo derecho.*/
				tmp1->parent->color = BLACK;
				tmp1->parent->parent->color = RED;

				left_rotate(tree,tmp1->parent->parent);
			}

		}
	}

	tree->root->color = BLACK;
}

/** 
 * Coloca al nodo b como hijo del padre de a y le indica al nodo
 * b que su padre cambio, al nodo a no le dice que su padre ya 
 * no hace referencia
 */
void rb_transplant(rb_tree* tree,rb_node* a, rb_node* b)
{
	if (a->parent == &sentinel) {
		tree->root = b;
	} else if (a == a->parent->left) {
		a->parent->left = b;
	} else {
		a->parent->right = b;
	}
	
	b->parent = a->parent;
}

/**
 * Busca un un nodo en el arbol que contenga exactamente el punto que se le paso.
 **/
rb_node* rb_node_search(rb_tree* tree, vertex* element)
{
	struct rb_node* tmp;
	tmp = tree->root;

	while(tmp != &sentinel) {
		if (tree->coordinate == Y ? 
			tmp->element->y == element->y :
			tmp->element->x == element->x) {
			break;
		} else if(tree->coordinate == Y ?
				  tmp->element->y < element->y :
				  tmp->element->x < element->x) {
			tmp = tmp->right;
		} else {
			tmp = tmp->left;
		}
	}
	
	if (tmp == &sentinel)
		return NULL;

	return tmp;
}

/**
 * Compone las propiedades del arbol una vez que el nodo que se le paso se
 * borra.
 */
void rb_delete_fixup(struct rb_tree* tree, struct rb_node* node)
{
	struct rb_node *tmp1, *tmp2;
	tmp1 = node;
	
	while ((tmp1 != tree->root) && (tmp1->color == BLACK)) {
		
		if (tmp1 == tmp1->parent->left) {
			tmp2 = tmp1->parent->right;
			
			if (tmp2->color == RED) {
			
				tmp2->color = BLACK;
				tmp1->parent->color = RED;
				
				left_rotate(tree,tmp1->parent);
				tmp2 = tmp1->parent->right;
			}
			
			
			if ((tmp2->left->color == BLACK) && (tmp2->right->color == BLACK)) {
				
				tmp2->color = RED;
				tmp1 = tmp1->parent;
				
			} else {
				if (tmp2->right->color == BLACK) {
					
					tmp2->left->color = BLACK;
					tmp2->color = RED;
					right_rotate(tree,tmp2);
					tmp2 = tmp1->parent->right;					
				}
				
				tmp2->color = tmp1->parent->color;
				tmp1->parent->color = BLACK;
				tmp2->right->color = BLACK;
				
				left_rotate(tree,tmp1->parent);
				tmp1 = tree->root;
			}
		} else {
			tmp2 = tmp1->parent->left;
			
			if (tmp2->color == RED) {
				
				tmp2->color = BLACK;
				tmp1->parent->color = RED;
				
				right_rotate(tree,tmp1->parent);
				tmp2 = tmp1->parent->left;
			}
			
			if ((tmp2->right->color == BLACK) && (tmp2->left->color == BLACK)) {
				
				tmp2->color = RED;
				tmp1 = tmp1->parent;
				
			} else {
				if (tmp2->left->color == BLACK) {
					
					tmp2->right->color = BLACK;
					tmp2->color = RED;
					left_rotate(tree,tmp2);
					tmp2 = tmp1->parent->left;					
				}
				
				tmp2->color = tmp1->parent->color;
				tmp1->parent->color = BLACK;
				tmp2->left->color = BLACK;
				
				right_rotate(tree,tmp1->parent);
				tmp1 = tree->root;
			}
			
		}
	}
	tmp1->color = BLACK;
}

/**
 * Regresa el nodo que tenga el punto con la menor coordenada X o Y.
 */
struct rb_node* rb_min_node(struct rb_node* node)
{
	struct rb_node* tmp = node;

	if (tmp == NULL)
		return NULL;

	if (tmp == &sentinel)
		return tmp;

	while(tmp->left != &sentinel)
		tmp = tmp->left;

	return tmp;
}

/**
 * Regresa el nodo que tenga el punto con la mayor coordenada X o Y.
 */
struct rb_node* rb_max_node(struct rb_node* node)
{
	struct rb_node* tmp = node;
	
	if (tmp == NULL)
		return NULL;

	if (tmp == &sentinel)
		return tmp;

	while(tmp->right != &sentinel)
		tmp = tmp->right;
	
	return tmp;
}

/** Pregunta si es el hijo izquierdo */
int is_left_son(rb_node* node)
{
	if (node->parent == &sentinel) {
		return 1;
	}

	return node->parent->left == node;

}

struct rb_tree* init_rb_tree(coordinate coordinate)
{
	struct rb_tree* tree;
	tree = (struct rb_tree*) malloc(sizeof(struct rb_tree));

	if (tree == NULL) {
		printf("Ya no hay memoria disponible: init_rb_tree()\n");
		exit(EXIT_FAILURE);
	}

	tree->root = &sentinel;
	tree->size = 0;
	
	tree->min = tree->max = &sentinel;
	
	tree->coordinate = coordinate;
	
	return tree;
}

void destroy_rb_tree(struct rb_tree* tree)
{
	if (tree == NULL)
		return;
	
	while (!empty_rb_tree(tree))
		rb_delete(tree,rb_min(tree));
	
	free(tree);
}

struct rb_node* init_rb_node(){
	struct rb_node* node;
	node = (struct rb_node*) malloc(sizeof(struct rb_node));
	
      	if (node == NULL) {
		printf("Ya no hay memoria disponible: init_rb_node()\n");
		exit(EXIT_FAILURE);
	}

	node->left = node->right = node->parent = &sentinel;
	node->color = RED;
	
	node->prev = node->next = &sentinel;

	node->element = NULL;

	return node;
}

void destroy_rb_node(rb_node* node)
{
	if (node != NULL && node != &sentinel)
		free(node);
}

void rb_insert(struct rb_tree* tree, vertex* element)
{	
	struct rb_node *tmp1, *tmp2;
	tmp1 = tree->root;
	tmp2 = &sentinel;

	while (tmp1 != &sentinel) {
		tmp2 = tmp1;	   
		
		if (tree->coordinate == Y ?
			element->y < tmp1->element->y :
			element->x < tmp1->element->x)
			
			tmp1 = tmp1->left;
		else
			tmp1 = tmp1->right;
	}

	struct rb_node* node;
	node = init_rb_node();
	
	node->parent = tmp2;
	node->element = element;

	if (tmp2 == &sentinel) {
		tree->root = node;
	} else if (tree->coordinate == Y ?
			   element->y < tmp2->element->y :
			   element->x < tmp2->element->x) {
		tmp2->left = node;
	} else {
		tmp2->right = node;
	}	

	rb_insert_fixup(tree,node);	
	tree->size += 1;

	/** Mantengo los apuntadores prev y next de forma consistente. */
	if (tree->min == &sentinel) {
		tree->min = tree->max = node;		
		return;
	}

	if (tree->coordinate == Y ? 
		node->element->y < tree->min->element->y :
		node->element->x < tree->min->element->x) {
		
		node->next = tree->min;
		tree->min->prev = node;

		tree->min = node;
				
		return;
	}

	if ((tree->coordinate == Y ? 
		 tree->max->element->y < node->element->y :
		 tree->max->element->x < node->element->x) ||
		
		(tree->coordinate == Y ?
		 node->element->y == tree->max->element->y :
		 node->element->x == tree->max->element->x)) {
		
		node->prev = tree->max;
		tree->max->next = node;
		
		tree->max = node;
		
		return;
	}

	rb_node *pre, *suc;
	suc = &sentinel;
	
	pre = rb_max_node(node->left);
	if (pre != &sentinel) {
		
		suc = pre->next;

		pre->next = node;
		node->prev = pre;
	} else {
		pre = node;
		while (is_left_son(pre)) {
			pre = pre->parent;
		}
		pre = pre->parent;

		suc = pre->next;

		pre->next = node;
		node->prev = pre;
	}

	suc->prev = node;
	node->next = suc;

	return;
}

vertex* rb_search(struct rb_tree* tree, vertex* element)
{
	if (tree == NULL)
		return NULL; 

	struct rb_node* tmp = rb_node_search(tree,element);

	if (tmp == NULL || tmp == &sentinel)
		return NULL;
	else
		return tmp->element;
}

vertex* rb_delete(rb_tree* tree, vertex* element)
{
	struct rb_node *tmp1, *tmp2, *tmp3;
	tmp1 = rb_node_search(tree,element);
		
	if (tmp1 == NULL || tmp1 == &sentinel)
		return NULL;

	if (tree->size == 1) {
		tree->min = tree->max = &sentinel;
	} else {
		if ((tree->min == tmp1) || (tree->max == tmp1)) {
			if (tree->min == tmp1) {
				tree->min = tmp1->next;
				tmp1->next->prev = &sentinel;
			}
			if (tree->max == tmp1) {				
				tree->max = tmp1->prev;
				tmp1->prev->next = &sentinel;
			}
		} else {
			tmp1->next->prev = tmp1->prev;
			tmp1->prev->next = tmp1->next;
		}
	}

	tmp2 = tmp1;
	color tmp2_original_color = tmp2->color;
	
	if (tmp1->left == &sentinel) {
		tmp3 = tmp1->right;
		rb_transplant(tree,tmp1,tmp1->right);
	} else if(tmp1->right == &sentinel) {
		tmp3 = tmp1->left;
		rb_transplant(tree, tmp1,tmp1->left);
	} else {
		tmp2 = rb_min_node(tmp1->right);
		tmp2_original_color = tmp2->color;
		tmp3 = tmp2->right;

		if (tmp2->parent == tmp1) {
			tmp3->parent = tmp2;
		} else {
			rb_transplant(tree,tmp2,tmp2->right);
			tmp2->right = tmp1->right;
			tmp2->right->parent = tmp2;
		}

		rb_transplant(tree,tmp1,tmp2);
		tmp2->left = tmp1->left;
		tmp2->left->parent = tmp2;
		tmp2->color = tmp1->color;
	}

	if (tmp2_original_color == BLACK)
		rb_delete_fixup(tree,tmp3);
 	
	tree->size -= 1;	
	destroy_rb_node(tmp1);
	return element;
}

vertex* rb_min(rb_tree* tree)
{
	if (empty_rb_tree(tree))
		return NULL;
	
	return tree->min->element;
}



vertex* rb_max(rb_tree* tree)
{
	if (empty_rb_tree(tree))
		return NULL;

	return tree->max->element;
}

list* rb_tree_to_list(rb_tree* tree)
{
	if (tree == NULL)
		return NULL;

	list* list = init_double_linked_list();
	rb_node* tmp = tree->min;

	while(tmp != &sentinel) {
		push_back(list,tmp->element);
		tmp = tmp->next;
	}

	return list;
}

//Inicio de implementaciones extra
void rb_inorden(rb_node* t){
	if (t->left != &sentinel)
		rb_inorden(t->left);
	printf("El punto es: (%f,%f)\n",t->element->x,t->element->y);
	if (t->right != &sentinel)
		rb_inorden(t->right);
}


void rb_range_query(rb_node* t, double y,double y1, 
	list* reported_points){
	if (t->left != &sentinel)
		rb_range_query(t->left,y,y1,reported_points);
		
	if(t->element->y >= y && t->element->y <= y1){
		push_back(reported_points, t->element);
		//printf("El punto es: (%f,%f)\n",t->element->x,t->element->y);
	}
	
	if (t->right != &sentinel)
		rb_range_query(t->right,y,y1,reported_points);
	
}

struct rb_node* getNext(struct rb_node* node){
	struct rb_node* temp=node;
	
	//Caso en el que tiene hijo derecho
	if(temp->right != &sentinel){
		temp=temp->right;
		while(temp->left!=&sentinel){
			temp = temp->left;
		}
		//printf("El nodo siguiente es: (%lf,%lf)\n",temp->point->x,temp->point->y);
		return temp;
	}
	
	//No tiene hijo derecho
	//Si tiene padre
	if(temp->parent!=&sentinel){
		//Si es hijo izquierdo
		if(temp==temp->parent->left){
			//printf("El nodo siguiente es: (%lf,%lf)\n",temp->parent->point->x,temp->parent->point->y);
			return temp->parent;
		}else{
			//Si es hijo derecho
			while(temp->parent != &sentinel && temp==temp->parent->right){
				temp=temp->parent;
			}
			if(temp->parent != &sentinel){
				//printf("El nodo siguiente es: (%lf,%lf)\n",temp->parent->point->x,temp->parent->point->y);
				return temp->parent;
			}
		}
	}
	//Si no tiene padre
	//printf("El nodo siguiente es nulo\n");
	return NULL;
}


struct rb_node* getPrev(struct rb_node* node){
	struct rb_node* temp=node;
	
	if(temp->left != &sentinel){
		temp=temp->left;
		while(temp->right != &sentinel){
			temp = temp->right;
		}
		//printf("El nodo anterior es: (%lf,%lf)\n",temp->point->x,temp->point->y);
		return temp;
	}
	
	if(temp->parent!=&sentinel){
		if(temp==temp->parent->right){
			//printf("El nodo anterior es: (%lf,%lf)\n",temp->parent->point->x,temp->parent->point->y);
			return temp->parent;
		}else{
			while(temp->parent != &sentinel && temp==temp->parent->left){
				temp=temp->parent;
			}
			if(temp->parent != &sentinel){
				//printf("El nodo anterior es: (%lf,%lf)\n",temp->parent->point->x,temp->parent->point->y);
				return temp;
			}
		}
	}
	//printf("El nodo anterior es nulo\n");
	return NULL;
}

rb_node* rb_split_node(rb_node* node, double y, double y1){
	while(y > node->element->y && node->right!= &sentinel){
		node=node->right;
	}
	while(y1 <node->element->y && node->left!= &sentinel){
		node=node->left;
	}
	
	printf("El split_node Y para y=%lf y y1=%f es: (%lf,%lf)\n",y,y1,node->element->x,node->element->y);
	return node;
}



