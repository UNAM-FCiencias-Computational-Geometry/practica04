/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 */

#include "range_tree/range_tree.h"

#include <stdlib.h>
#include <stdio.h>

int main(void)
{			  

	vertex *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m, *n, *o, *p,
		*q, *r, *s, *t, *u, *v, *w, *z;

	a = init_point(1.3,1.44, "A");
	b = init_point(1.44,1.16, "B");
	c = init_point(1.7,1.58, "C");
	d = init_point(1.8,1.24,"D");
	e = init_point(2.32,1.6,"E");
	f = init_point(2.32,1.28,"F");
	g = init_point(2.82, 1.24,"G");
	h = init_point(2.74,1.7,"H");
	i = init_point(3.22,1.7,"I");
	j = init_point(3.22,1.36,"J");
	k = init_point(3.72,1.36,"K");
	l = init_point(3.64,1.78,"L");
	m = init_point(0.42,0.42,"M");
	n = init_point(0.6,2.52,"N");
	o = init_point(2.72,3.2,"O");
	p = init_point(3.6,3.56,"P");
	q = init_point(4.54,3.42,"Q");
	r = init_point(4.54,2.5,"R");
	s = init_point(4.6,1.64,"S");
	t = init_point(4.42,0.44,"T");
	u = init_point(3.58,0.46,"U");
	v = init_point(2.24,0.5,"V");
	w = init_point(1.64,0.6,"W");
	z = init_point(1.88,2.68,"Z");

	list* set_of_points = init_double_linked_list();

	push_back(set_of_points, a);
	push_back(set_of_points, b);
	push_back(set_of_points, c);
	push_back(set_of_points, d);
	push_back(set_of_points, e);
	push_back(set_of_points, f);
	push_back(set_of_points, g);
	push_back(set_of_points, h);
	push_back(set_of_points, i);
	push_back(set_of_points, j);
	push_back(set_of_points, k);
	push_back(set_of_points, l);
	push_back(set_of_points, m);
	push_back(set_of_points, n);
	push_back(set_of_points, o);
	push_back(set_of_points, p);
	push_back(set_of_points, q);
	push_back(set_of_points, r);
	push_back(set_of_points, s);
	push_back(set_of_points, t);
	push_back(set_of_points, u);
	push_back(set_of_points, v);
	push_back(set_of_points, w);
	push_back(set_of_points, z);
	
	
	ra_tree* range_tree = build_2d_range_tree(set_of_points);

	double x, x1, y, y1;
	x = 1.0;
	x1 = 4.0;

	y = 1.0;
	y1 = 2.0;

	list* points = two_d_range_query(range_tree, x, x1, y, y1);
	
	return EXIT_SUCCESS;
}
