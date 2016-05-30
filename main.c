
#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int main(void){
  source *src;
  product *prd;
  order *ord;
  FILE *f = fopen ("in.txt", "r");
   in_source(f, &src);
   fclose(f);
   f = fopen("in-product.txt", "r");
   in_product (f, &prd, src);
   fclose(f);
   f = fopen("in-orders.txt", "r");
   in_orders(f, &ord, prd);
   fclose(f);
   a_src *t;
   while (prd != NULL){
     printf ("id:%d name:", prd->id);
     print_title(prd->title);
     t = prd->contains;
     printf ("\ncontains:\n");
     while (t!= NULL){
       printf ("id:%d %f%c of", (t->src)->id, t->num, (t->src)->type);
       print_title((t->src)->title);
       printf("\n");
       t = t->n;
     }
     printf ("\n============\n");
     prd = prd->n;
   }
   //   printf ("\n\n num of gold in order #1: %f\n\n", num_of_res(ord, 1, 3));
   //prd = get_head_product(prd);  
   //printf("\n%d\n", iscorrect(src, ord, 0, ps, 2));
   int *arg, n, i, *res,ls;
   //order *ord33 = from_arg_to_list (ord, arg, 3);
   printf("order have been read:\n");
   out_orders(ord);
   printf("\n*-*-*-*-*-*\n");
   n = from_list_to_arg(ord, &arg);
   res = (int*) malloc(n*sizeof(int));
   for (i=0;i<n;i++)
     res[i] = 0;
   
   
   recursive(src, ord, arg, res, 0,0,n);
   ls = longest_solution(d, size, max);
   for(i=0;i<=max;i++){
     printf("\n(%d)\n", d[ls][i]);
     }
}
