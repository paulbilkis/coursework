#include <stdio.h>
#include "headers.h"
void out_orders (order *ord, client *clt){
  order *head = get_head_order(ord);
  client *head_c = get_head_client(clt);
  product *pp;
  while(head_c != NULL){
     printf ("client name:");
     print_title(head_c->title);
     printf ("\norders:\n");
     while(head != NULL){
       if(head->client_id == head_c->id){
	 printf("id:%d %d pcs of ", head->id, head->num);
	 print_title((head->contains)->title);
	 printf("\n");
       }
       head = head->n;
     }
     head = get_head_order(ord);
     head_c = head_c->n;
  }   
}

void fout_orders (order *ord, FILE *f){
  order *head = get_head_order(ord);
  a_product *pp;
  /* while(head != NULL){
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
     }*/
}
