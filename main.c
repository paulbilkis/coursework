
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
   int ps[] = {1};
   printf("\n%d\n", iscorrect(src, ord, 0, ps, 2));
   a_product* pp=NULL;
   while(ord != NULL){
     printf ("id:%d", ord->id);
     print_title(ord->title);
     pp = ord->contains;
     printf ("\ncontains:\n");
     while (pp!= NULL){
       printf ("%d %d pieces of ", (pp->product)->id, pp->num);
       print_title((pp->product)->title);
       printf("\n");
       pp = pp->n;
     }
     printf ("\n============\n");
     ord = ord->n;
   }
     
  
}
