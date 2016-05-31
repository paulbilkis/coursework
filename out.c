#include <stdio.h>
#include "headers.h"
void out_orders (order *ord){
  order *head = get_head_order(ord);
  a_product *pp;
  while(head != NULL){
     printf ("@id:%d", head->id);
     print_title(head->title);
     pp = head->contains;
     printf ("\ncontains:\n");
     while (pp!= NULL){
       if(pp->product != NULL){
	 printf ("%d pcs of", pp->num);
	 print_title((pp->product)->title);
       }else{
	 printf("PRODUCT NOT FOUND");
       }
       printf("\n");
       pp = pp->n;
     }
     printf ("\n============\n");
     head = head->n;
   }
}

void fout_orders (order *ord, FILE *f){
  order *head = get_head_order(ord);
  a_product *pp;
  while(head != NULL){
    fprintf (f,"@id:%d", head->id);
    fprint_title(head->title,f);
     pp = head->contains;
     fprintf (f,"\ncontains:\n");
     while (pp!= NULL){
       if(pp->product != NULL){
	 fprintf (f,"%d pcs of", pp->num);
	 fprint_title((pp->product)->title,f);
       }else{
	 fprintf(f,"PRODUCT NOT FOUND");
       }
       fprintf(f,"\n");
       pp = pp->n;
     }
     fprintf (f,"============\n");
     head = head->n;
   }
}
