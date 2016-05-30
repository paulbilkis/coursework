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
       printf ("%d %d pieces of ", (pp->product)->id, pp->num);
       print_title((pp->product)->title);
       printf("\n");
       pp = pp->n;
     }
     printf ("\n============\n");
     head = head->n;
   }
}
