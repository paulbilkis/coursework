#include "headers.h"
a_product * get_head_a_product (a_product *el){
  while (el->prev != NULL)
    el = el->prev;
  return el;
}

a_src * get_head_a_src (a_src *el){
  while (el->prev != NULL)
    el = el->prev;
  return el;
}

product * get_head_product (product *el){
  while (el->prev != NULL)
    el = el->prev;
  return el;
}

order * get_head_order (order *el){
  while (el->prev != NULL)
    el = el->prev;
  return el;
}


order * get_order (order *el, unsigned id){
  el = get_head_order(el);
  while (el != NULL && el->id != id)
    el = el->n;
  return el;
}

product * get_product (product *el, unsigned id){
  el = get_head_product(el);
  while (el != NULL && el->id != id)
    el = el->n;
  return el;
}
  
source * get_source (source *el, unsigned id){
  el = get_head_source(el);
  while (el != NULL && el->id != id)
    el = el->n;
  return el;
}

str * get_head (str *el){
  while (el->prev != NULL)
    el = el->prev;
  return el;
}
source * get_head_source (source *el){
  while (el->prev != NULL)
    el = el->prev;
  return el;
}

void print_title (str *head){
  head = get_head (head);
  while (head != NULL){
    printf ("%s", head->data);
    head = head->n;
  }
}
