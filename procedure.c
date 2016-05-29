#include <stdio.h>
#include "headers.h"
void delete_imp_orders (order *ord, source *src){
  order *temp,*head = get_head_order(ord);
  while (head!=NULL){
    if(!iscorrect(src,ord,0,0,head->id)){
      (head->n)->prev = head->prev;
      (head->prev)->n = head->n;
      temp = head->n;
      free(head);
      head = temp;
    }else{
      head = head->n;
    }
  }
}

order * from_arg_to_list (order *ord, int *orders, int n){
  int i;
  order *order=NULL;
  for (i=0; i<n; i++){
    if (order == NULL){
      order = get_order(ord, orders[i]);
      order->n = NULL;
      order->prev = NULL;
    }else{
      temp = get_order(ord, orders[i]);
      temp->prev = order;
      temp->n = NULL;
      order->n = temp;
      order = temp;
    }
  }
  return get_head_order(order);
}

int iscorrect (source *src, order *ord, int n, int *res, int p){
  int i;
  source *hsrc;
  order *a;
  float num=0;
  hsrc = get_head_source(src);
  while (hsrc!=NULL){
    num=0;
    if(res != 0){
      for (i=0; i<=n; i++){
	num += num_of_res(ord, res[i], hsrc->id);
	//printf("\n\n%d %d %f\n\n", hsrc->id, res[i], num);
      }
    }
    num += num_of_res(ord, p, hsrc->id);
    if (num > hsrc->num) return 0;
    hsrc = hsrc->n;
  }
  return 1;
}

float num_of_res (order *ord, unsigned order_id, unsigned source_id){
  order *order = get_order(ord, order_id);
  a_product *aprd = order->contains;
  a_src *asrc;
  float num=0;
  while(aprd!=NULL){
    asrc = (aprd->product)->contains;//начало списка состава a_src
    while (asrc!=NULL){
      if ((asrc->src)->id == source_id)
	  num += aprd->num * asrc->num;
      asrc = asrc->n;
    }
    aprd = aprd->n;
  }
  return num;
}
