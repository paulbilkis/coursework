
#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

int main(void){
  source *src, *head_src;
  product *prd;
  order *ord;
  client *clt;
  FILE *f = fopen ("in.txt", "r");
   in_source(f, &src);
   fclose(f);
   head_src = src;
   f = fopen("in-product.txt", "r");
   in_product (f, &prd, src);
   fclose(f);
   f = fopen("in-clients.txt", "r");
   in_clients(f, &clt);
   fclose(f);
   f = fopen("in-orders.txt", "r");
   in_orders(f, &ord, prd);
   fclose(f);
   a_src *t;
   f = fopen("log.txt", "w");
   fprintf(f, "\nsources have been red from file:\n");
   while (head_src != NULL){
     fprintf(f, "id:%d amount:%f%c name:", head_src->id, head_src->num, head_src->type);
     fprint_title(head_src->title,f);
     fprintf(f,"\n");
     head_src = head_src->n;
     }
   //src = get_head_source(src);
   fprintf(f, "\n\nproduct receipts have been red from file:\n");
   while (prd != NULL){
     fprintf (f,"id:%d name:", prd->id);
     fprint_title(prd->title, f);
     t = prd->contains;
     fprintf (f,"\ncontains:\n");
     while (t!= NULL){
       fprintf (f,"%f%c of", t->num, (t->src)->type);
       fprint_title((t->src)->title,f);
       fprintf(f,"\n");
       t = t->n;
     }
     fprintf (f,"============\n");
     prd = prd->n;
     }
   client *head_clt = clt;
   fprintf(f, "\nclients have been red from file:\n");
   while (head_clt != NULL){
     fprintf(f, "\nid:%d name:", head_clt->id);
     fprint_title(head_clt->title, f);
     head_clt = head_clt->n;
   }
   // prd = get_head_product(prd);
   int *arg, n=0, i, j,*res,ls;
   fprintf(f,"\n\norders have been read:\n");
   
   fout_orders(ord, clt,f);
   fclose(f);
   //delete_imp_orders(ord, src);
   //out_orders(ord);
   //printf("\n*-*-*-*-*-*\n");
   //printf("%f", num_of_res(ord, 1,1));
   n = from_list_to_arg(ord, &arg);
   res = (int*) malloc(n*sizeof(int));
   for (i=0;i<n;i++)
     res[i] = 0;
   	       
   f = fopen("out.txt", "w");
   recursive(src, ord, arg, res, 0,0,n);
   ls = longest_solution(d, ord, size, max);
   //for(j=0;j<4;j++) {
   //for(i=0;i<=max;i++) printf("%d ",d[ls][i]);
     printf("\n");
     //}
   
   order *result = NULL;
   if (ls != -1){
     result = from_arg_to_list(ord, d[ls], max+1);
  
   printf("orders acomplish:\n");
   fprintf(f,"orders acomplish:\n");
   out_orders(result, clt);
   get_rid_source_stock(result, src);
   fout_orders(result,clt,f);
   }else{
     printf ("None of the orders could be acomplish!\n");
   }
    
   printf ("\nleft-over stock:\n");

   head_src = get_head_source(src);
   while (head_src != NULL){
     printf("id:%d amount:%f%c name:", head_src->id, head_src->num, head_src->type);
    print_title(head_src->title);
     printf("\n");
   
         head_src = head_src->n;
	 // free(head_src->prev);
     }
   
     fclose(f);
}
