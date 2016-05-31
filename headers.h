#ifndef HEADERS_H
#define HEADERS_H
#include <stdio.h>
#include "structures.h"
void in_source (FILE *f, source **el);
void in_product (FILE *f, product **el, source *sources);
void in_orders (FILE *f, order **el, product *products);
void print_title (str *head);
str * get_head (str *el);
source * get_head_source (source *el);
product * get_head_product (product *el);
source * get_source (source *el, unsigned id);
product * get_product (product *el, unsigned id);
order * get_order (order *el, unsigned id);
order * get_head_order(order *el);
a_src * get_head_a_src (a_src *el);
a_product * get_head_a_product (a_product *el);
float num_of_res (order *ord, unsigned order_id, unsigned source_id);
int iscorrect (source *src, order *ord, int n, int *res, int p);
void delete_imp_orders (order *ord, source *src);
order * from_arg_to_list (order *ord, int *orders, int n);
int from_list_to_arg (order *ord, int **arg);
int longest_solution (int **solutions, order *ord, int n, int max);
int recursive (source *src, order *ord, int *p, int *res, int j, int cur, int n);
int is_there_prd (product *prd, int id);
int is_there_src (source *src, int id);
void fprint_title (str *head, FILE *f);
void fout_orders (order *ord, FILE *f);
client * get_head_client(client *h);
void out_orders (order *ord, client *clt);
extern int max;
extern int **d;
extern int size;
#endif // HEADERS_H
