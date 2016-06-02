#include <stdio.h>
#include "headers.h"
void out_orders (order *ord, client *clt){
  order *head = get_head_order(ord);
  client *head_c;
  product *pp;
  
  
  while(head != NULL){
    printf ("id:%d num:%d  order:", head->id, head->num);
    print_title((head->contains)->title);
    printf(" client:");
    head_c = get_client(clt, head->client_id);
    if (head_c != NULL) print_title(head_c->title);
    else printf(" null");
    printf("\n");
    head = head->n;
  }
}

void fout_orders (order *ord, client *clt, FILE *f){
  order *head = get_head_order(ord);
  client *head_c;
  product *pp;
   while(head != NULL){
     fprintf (f,"id:%d num:%d  order:", head->id, head->num);
     fprint_title((head->contains)->title,f);
     fprintf(f," client:");
    head_c = get_client(clt, head->client_id);
    if (head_c != NULL) fprint_title(head_c->title,f);
    else fprintf(f," null");
    fprintf(f,"\n");
    head = head->n;
  }
}
