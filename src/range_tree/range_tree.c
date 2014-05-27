#include "range_tree/range_tree.h"

#include <stdio.h>
#include <stdlib.h>

void destroy_ra_tree_recursive(ra_node* ra_node)
{
	if (ra_node == NULL)
		return;

	destroy_ra_tree_recursive(ra_node->left);
	destroy_ra_tree_recursive(ra_node->right);

	destroy_ra_node(ra_node);
	
	return;
}

ra_node* init_ra_node()
{
	struct ra_node* ra_node;
	ra_node = (struct ra_node*) malloc(sizeof(struct ra_node));
	
	if (ra_node == NULL) {
		printf("YA no hay memoria disponible: init_ra_node()\n");
		exit(EXIT_FAILURE);
	}

	ra_node->x_mid = NULL;
	
	ra_node->left = NULL;
	ra_node->right = NULL;
	
	ra_node->tree_assoc = NULL;

	return ra_node;
}

void destroy_ra_node(ra_node* ra_node)
{
	
	destroy_rb_tree(ra_node->tree_assoc);

	free(ra_node);
}

ra_tree* init_ra_tree()
{
	struct ra_tree* ra_tree;
	ra_tree = (struct ra_tree*) malloc(sizeof(struct ra_tree));
	
	if (ra_tree == NULL) {
		printf("YA no hay memoria disponible: init_ra_tree()\n");
		exit(EXIT_FAILURE);
	}

	ra_tree->root = NULL;;

	return ra_tree;
}

void destroy_ra_tree(ra_tree* tree)
{
	destroy_ra_tree_recursive(tree->root);
	free(tree);
}

void inorden(ra_node* t){
	if(t != NULL){
		if(t->left!= NULL)
			inorden(t->left);
		printf("El punto es: (%lf,%lf)\n",t->x_mid->x,t->x_mid->y);
		if(t->right!= NULL)
			inorden(t->right);
	}	
}



ra_tree* build_2d_range_tree(list* set_of_points)
{
	if (set_of_points!=NULL){
		ra_tree* range_tree= init_ra_tree();
		
		if(!empty_list(set_of_points)){
			rb_tree *x_ordered= init_rb_tree(X);
			list *x_ordered_list=init_double_linked_list();
			vertex* temp;
			while(!empty_list(set_of_points)){
				temp=pick_front(set_of_points);
				//printf("El vertice insertado es: (%lf,%lf)\n",temp->x,temp->y);
				rb_insert(x_ordered,temp);
				pop_front(set_of_points);
			}
			//printf("\n\nMETIENDO\n");
			//rb_inorden(x_ordered);
			while(!empty_rb_tree(x_ordered)){
				temp=rb_min(x_ordered);
				//printf("El vertice es: (%lf,%lf)\n",temp->x,temp->y);
				push_back(x_ordered_list,temp);
				rb_delete(x_ordered,temp);
			}
			
			range_tree->root=build_2d_range_tree_node(x_ordered_list);
			
			printf("\n\n\nARBOL de rangos\n");
			inorden(range_tree->root);
			find_split_node_2d(range_tree,2300,2000);		
			printf("\n\n\nARBOL ASOCIADO\n");
			rb_inorden(range_tree->root->tree_assoc->root);
			
			find_split_node_1d(range_tree->root->tree_assoc,8500,8000);
			
	
		}
		return range_tree;
	}
	return NULL;
}

ra_node* build_2d_range_tree_node(list* set_of_points)
{
	list* set_lower_points=init_double_linked_list(), *set_higher_points=init_double_linked_list();
	vertex*temp;

	if (set_of_points == NULL)
		return NULL;

	if (set_of_points->size == 0)
		return NULL;

	ra_node* ra_node = init_ra_node();
	
	/**
	 * 1. Construct the associated structure: Build a binary search 
	 * tree Tassoc on the set Py of y-coordinates of the points in P. 
	 * Store at the leaves of Tassoc not just the y-coordinate of 
	 * the points in Py, but the points themselves.
	 */
	 
	rb_tree* tAssoc=init_rb_tree(Y);
	list*copy= create_copy_list(set_of_points);
	while(!empty_list(copy)){
		temp=pick_front(copy);
		rb_insert(tAssoc, temp);
		pop_front(copy);
	}
	ra_node->tree_assoc=tAssoc;
		
	/**
	 * 2. if P contains only one point
	 * 3.      then Create a leaf ν storing this point, 
	 *              and make Tassoc the associated structure of ν.
	 */
	 if(set_of_points->size==1){
		 ra_node->x_mid=tAssoc->root->element;
		 return ra_node;
	 }else{

	/**
	 * 4. else Split P into two subsets; one subset Pleft contains the 
	 *         points with x-coordinate less than or equal to xmid, 
	 *         the median x-coordinate, and the other subset Pright 
	 *         contains the points with x-coordinate larger than xmid.
	 */
	 int half=set_of_points->size/2,count=0;
	 
	 while(count<half){
		temp=pick_front(set_of_points);
		push_back(set_lower_points,temp);
		pop_front(set_of_points);
		count++;
	 }
	 ra_node->x_mid=pick_front(set_of_points);
	 pop_front(set_of_points);
	 
	 while(!empty_list(set_of_points)){
		 temp=pick_front(set_of_points);
		 push_back(set_higher_points,temp);
		 pop_front(set_of_points);
	 }
	}
    /**
	 * 5. νleft ← BUILD2DRANGETREE(Pleft)
	 */
	ra_node->left=build_2d_range_tree_node(set_lower_points);
    /**
	 * 6. νright ← BUILD2DRANGETREE(Pright)
	 */
	ra_node->right=build_2d_range_tree_node(set_higher_points);
	
	return ra_node;
}

rb_node* find_split_node_1d(rb_tree* tree, double y, double y1)
{
	rb_node* node;
	node = tree->root;

	if (node == &sentinel) 
		return NULL;
	
	if(y<=y1)
		node=rb_split_node(node,y,y1);
	else
		node=rb_split_node(node,y1,y);
		
	return node;
}

//Funcion extra
ra_node* ra_split_node(ra_node* node, double x, double x1){
	
	while(x > node->x_mid->x && node->right!= NULL){
		node=node->right;
	}
	while(x1 <node->x_mid->x && node->left!= NULL){
		node=node->left;
	}
	
	printf("El split_node X es: (%lf,%lf)\n",node->x_mid->x,node->x_mid->y);
	return node;	
	
}
//

ra_node* find_split_node_2d(ra_tree* ra_tree, double x, double x1)
{
	ra_node* ra_node;
	ra_node= ra_tree->root;

	if (ra_node == NULL) 
		return NULL;
		
	if(x<=x1)
		ra_node= ra_split_node(ra_node,x,x1);
	else
		ra_node= ra_split_node(ra_node,x1,x);

	return ra_node;
}


void one_d_range_query(rb_tree* tree, double y, double y1, list* report_points)
{

	if (tree == NULL || report_points == NULL)
		return;
	return;	
}

list* two_d_range_query(ra_tree* ra_tree, double x, double x1,
						double y, double y1)
{

	if (ra_tree == NULL)
		return NULL;
	
	list* report_points;
	report_points = init_double_linked_list();

	/**
	 * 1. νsplit ←FINDSPLITNODE(T,a,b)
	 */
	
	/**
	 * 2. if νsplit is a leaf
	 * 3.     then Check if the point stored at νsplit must be reported.
	 */

	/**
	 * 4. else (∗Follow the path to x and call 1DRANGEQUERY on the 
	 *         subtrees right of the path. ∗)
	 */
	
	/**
	 * 5. ν ← lc(νsplit )
	 */

	/**
	 * 6. while ν is not a leaf
	 */
		
	/**
	 * 7. do if x <= xν
	 * 8.       then 1DRANGEQUERY(Tassoc(rc(ν)),[y : y'])
	 * 9.            ν ← lc(ν)
	 */
	
	/**
	 * 10.    else ν←rc(ν)
	 */
	
	return report_points;
}

void report_tree(list* list_of_points, rb_node* subtree) 
{
	return;
}
