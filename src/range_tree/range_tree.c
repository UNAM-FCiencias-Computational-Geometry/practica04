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

ra_tree* build_2d_range_tree(list* set_of_points)
{
	return NULL;
}

ra_node* build_2d_range_tree_node(list* set_of_points)
{

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
	
	/**
	 * 2. if P contains only one point
	 * 3.      then Create a leaf ν storing this point, 
	 *              and make Tassoc the associated structure of ν.
	 */

	/**
	 * 4. else Split P into two subsets; one subset Pleft contains the 
	 *         points with x-coordinate less than or equal to xmid, 
	 *         the median x-coordinate, and the other subset Pright 
	 *         contains the points with x-coordinate larger than xmid.
	 */

    /**
	 * 5. νleft ← BUILD2DRANGETREE(Pleft)
	 */
		
    /**
	 * 6. νright ← BUILD2DRANGETREE(Pright)
	 */
		
	return ra_node;
}

rb_node* find_split_node_1d(rb_tree* tree, double y, double y1)
{
	rb_node* node;
	node = tree->root;

	if (node == &sentinel) 
		return NULL;
		
	return node;
}

ra_node* find_split_node_2d(ra_tree* ra_tree, double x, double x1)
{
	ra_node* ra_node;
	ra_node = ra_tree->root;

	if (ra_node == NULL) 
		return NULL;

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
