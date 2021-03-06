#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
float rnd (float num){
  return (((rand() % 10))*0.01 + 1)*num;
}

void in_product (FILE *f, product **el, source *sources){

  product *cur=NULL, *src=NULL;
  unsigned id, i, j=0,was_end=1;
  float num;
  char c;
  str *title;
  a_src *temp;
  time_t t;
  int rad;
  srand((unsigned) time(&t));
  while (!feof(f)){
    i=0;
    while (i < BLOCK_SIZE && fscanf(f, "%c", &c) != EOF){
      if (was_end){
        if (cur != NULL)(cur->title)->size += j;
        j=0;
        src = (product *) malloc(sizeof(product));
        fscanf(f, "%d", &id);
        src->id = id;
        src->prev = NULL;
        src->n = NULL;
        src->contains = NULL;
        src->title = (str *) malloc(sizeof(str));
        (src->title)->size = 0;
        (src->title)->n = NULL;
        (src->title)->prev = NULL;
        if (cur == NULL){
          cur = src;
        }else{
          cur->n = src;
          src->prev = cur;
        }
        cur = src;
        i++;
        was_end = 0;
        continue;
      }else{
        if (c == '\n'){
          was_end = 1;
          continue;
        }else if(c == '#'){
          fscanf (f, "%d:%f", &id, &num);
          temp = (a_src *) malloc(sizeof(a_src));
          temp->n = NULL;
          temp->prev = NULL;
          temp->src = get_source(sources, id);
          rad = rand();
          if ((temp->src)->type != 'p') temp->num = (((rad % 10))*0.01 + 1)*num;
          else temp->num = (int) num;
          
          if (cur->contains == NULL){
            cur->contains = temp;
          }else{
            (cur->contains)->n = temp;
            temp->prev = cur->contains;
            cur->contains = temp;
          }
          i++;
        }else{
         i++;
         if (j < TITLE_SIZE - (cur->title)->size){
           (cur->title)->data[(cur->title)->size + j] = c;
           j++;
         }else{
          title = (str *) malloc (sizeof(str));
          title->size=0;
          title->n=NULL;
          title->data[0] = c;
          ((cur)->title)->n = title;
          ((cur)->title)->size = j;
          title->prev = (cur)->title;
          (cur)->title = title;
          j=1;
         } 
        }
      }
    }
  }



  
  *el = get_head_product(cur);
  product *head = *el;

  while (head != NULL){
    temp = get_head_a_src(head->contains);
    head->contains = temp;
    head = head->n;
  }
  
  if(((*el)->title)->size == 0) ((*el)->title)->size = j;
  
}

void in_orders (FILE *f, order **el, product *products){

  order *cur=NULL, *src=NULL;
  unsigned id, clientid,i,was_end=1;
  int num;
  char c;
  str *title;
  
  while (!feof(f)){
    i=0;
    while (i < BLOCK_SIZE && fscanf(f, "%c", &c) != EOF){
      if (was_end){
        src = (order *) malloc(sizeof(order));
        fscanf(f, "%d", &id);
        src->id = id;
        src->prev = NULL;
        src->n = NULL;
        src->contains = NULL;
        if (cur == NULL){
          cur = src;
        }else{
          cur->n = src;
          src->prev = cur;
        }
        cur = src;
        i++;
        was_end = 0;
        continue;
      }else{
        if (c == '\n'){
          was_end = 1;
          continue;
        }else if(c == '@'){
          fscanf(f, "%d", &clientid);
          cur->client_id = clientid;
        }else if(c == '#'){
          fscanf (f, "%d:%d", &id, &num);
          cur->contains = get_product(products, id);
          cur->num = num;
          //was_end=1;
          i++;
        }
      }
    }
  }

  
  *el = get_head_order(cur);
  
}


void in_source (FILE *f, source **el){

  source *cur=NULL, *src=NULL;
  unsigned id, i, j=0,was_end=1;
  float num;
  char c, type;
  str *title;

  while (!feof(f)){
    i=0;
    while (i < BLOCK_SIZE && fscanf(f, "%c", &c) != EOF){
      if (was_end){
        if (cur != NULL)(cur->title)->size += j;
        j=0;
        src = (source *) malloc(sizeof(source));
        fscanf(f, "%d:%f:%c", &id, &num, &type);
        if (type == 'p') num = (int) num;
        src->id = id;
        src->num = num;
        src->type = type;
        src->prev = NULL;
        src->n = NULL;
        src->title = (str *) malloc(sizeof(str));
        (src->title)->size = 0;
        (src->title)->n = NULL;
        (src->title)->prev = NULL;
        if (cur == NULL){
          cur = src;
        }else{
          cur->n = src;
          src->prev = cur;
        }
        cur = src;
        i++;
        was_end = 0;
        continue;
      }else{
        if (c == '\n'){
          was_end = 1;
          continue;
        }else{
         i++;
         if (j < TITLE_SIZE - (cur->title)->size){
           (cur->title)->data[(cur->title)->size + j] = c;
           j++;
         }else{
          title = (str *) malloc (sizeof(str));
          title->size=0;
          title->n=NULL;
          title->data[0] = c;
          ((cur)->title)->n = title;
          ((cur)->title)->size = j;
          title->prev = (cur)->title;
          (cur)->title = title;
          j=1;
         } 
        }
      }
    }
  }

  *el = get_head_source(cur);
  
  if(((*el)->title)->size == 0) ((*el)->title)->size = j;
  
}

void in_clients (FILE *f, client **el){

  client *cur=NULL, *src=NULL;
  unsigned id, i, j=0,was_end=1;
  char c;
  str *title;

  while (!feof(f)){
    i=0;
    while (i < BLOCK_SIZE && fscanf(f, "%c", &c) != EOF){
      if (was_end){
        if (cur != NULL)(cur->title)->size += j;
        j=0;
        src = (client *) malloc(sizeof(client));
        fscanf(f, "%d", &id);
        src->id = id;
        src->prev = NULL;
        src->n = NULL;
        src->title = (str *) malloc(sizeof(str));
        (src->title)->size = 0;
        (src->title)->n = NULL;
        (src->title)->prev = NULL;
        if (cur == NULL){
          cur = src;
        }else{
          cur->n = src;
          src->prev = cur;
        }
        cur = src;
        i++;
        was_end = 0;
        continue;
      }else{
        if (c == '\n'){
          was_end = 1;
          continue;
        }else{
         i++;
         if (j < TITLE_SIZE - (cur->title)->size){
           (cur->title)->data[(cur->title)->size + j] = c;
           j++;
         }else{
          title = (str *) malloc (sizeof(str));
          title->size=0;
          title->n=NULL;
          title->data[0] = c;
          ((cur)->title)->n = title;
          ((cur)->title)->size = j;
          title->prev = (cur)->title;
          (cur)->title = title;
          j=1;
         } 
        }
      }
    }
  }

  *el = get_head_client(cur);
  
  if(((*el)->title)->size == 0) ((*el)->title)->size = j;
  
}
