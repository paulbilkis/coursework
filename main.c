#include <stdio.h>
#include <stdlib.h>
#define TITLE_SIZE 10
#define BLOCK_SIZE 10
typedef struct str{
  char data[TITLE_SIZE];
  unsigned size;
  struct str *n;
  struct str *prev;
}str;

typedef struct source{
  unsigned id;
  float num;
  str *title;
  char type;
  struct source *n;
  struct source *prev;
}source;

typedef struct a_src{
  source *src;
  float num;
  struct a_src *n;
  struct a_src *prev;
}a_src;


typedef struct product{
  unsigned id;
  a_src *contains;
  str *title;
  struct product *n;
  struct product *prev;
}product;

typedef struct a_product{
  product *product;
  unsigned num;
  struct a_product *n;
  struct a_product *prev;
}a_product;

typedef struct order{
  unsigned id;
  a_product *contains;
  str *title;
  struct order *n;
  struct order *prev;
}order;


void in_source (FILE *f, source **el);
void in_product (FILE *f, product **el, source *sources);
void in_orders (FILE **f, order **el, product *prd1);
void print_title (str *head);
str * get_head (str *el);
source * get_head_source (source *el);
product * get_head_product (product *el);
source * get_source (source *el, unsigned id);
product * get_product (product *el, unsigned id);
order * get_order (order *el, unsigned id);
order * get_head_order(order *el);
a_src * get_head_a_src (a_src *el);
a_product * get_head_a_product (a_product *el);

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



void in_orders (FILE **f, order **el, product *prd1){
  char c;
  int i=0,j=0, was_set=0;
  unsigned id, num;
  str *title;
  order *tmp;
  a_product *t;
  
  while(!feof(*f)){
    i=0;
  while (i<BLOCK_SIZE && fscanf(*f, "%c", &c) != EOF){
    printf("%c", c);
    if (!was_set){
       
      if(i!=0){ tmp = (order *) malloc (sizeof(order));
	tmp->n = NULL;
	(*el)->n = tmp;
	tmp->prev = *el;
	((*el)->title)->size = ((*el)->title)->size+j;
	j=0;
	*el = tmp;
	//	title = (*el)->title;
	(*el)->title = (str *) malloc (sizeof(str));
	((*el)->title)->size=0;
	((*el)->title)->n=NULL;
	((*el)->title)->prev = NULL;
	(*el)->contains = NULL;
	
      }
      
      was_set = 1;
    }

    if (c == '\n'){
	was_set = 0;
	i++;
    }else if (c == '#'){
      if (fscanf (*f, "%d:%d", &id, &num)!=EOF){
	
	  t = (a_product *) malloc (sizeof(a_product));
	  t->prev = (*el)->contains;
	  t->n = NULL;
	  t->product = get_product(prd1, id);
	  t->num = num;
	  if ((*el)->contains != NULL)
	    ((*el)->contains)->n = t;
	  (*el)->contains = t;
	
      i++;
      }
    }else if (c == '$'){
      fscanf(*f, "%d", &id);
       (*el)->id = id;
       i++;
    }else{
      i++;
	if (j < TITLE_SIZE-((*el)->title)->size){
	  
	  ((*el)->title)->data[((*el)->title)->size+j] = c;
	  
	  j++;
	}else{

	  title = (str *) malloc (sizeof(str));
	  title->size=0;
	  title->n=NULL;
	  title->data[0] = c;
	  ((*el)->title)->n = title;
	  ((*el)->title)->size = j;
	  title->prev = (*el)->title;
	  (*el)->title = title;
	  j=1;
	}
    }
  }
  if(((*el)->title)->size == 0) ((*el)->title)->size = j;
  }
  while ((*el)->prev != NULL){
    (*el)->contains = get_head_a_product((*el)->contains);
    (*el) = (*el)->prev;
  }
  (*el)->contains = get_head_a_product((*el)->contains);
}

void in_product (FILE *f, product **el, source *sources){

  product *cur=NULL, *src=NULL;
  unsigned id, i, j=0,was_end=1;
  float num;
  char c;
  str *title;
  a_src *temp;
  
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
	  temp->num = num;
	  temp->src = get_source(sources, id);
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



int main(void){
  source *src;
  product *prd;
  /*src->n = NULL;
  src->prev= NULL;
  src->title = (str *) malloc(sizeof(str));
  (src->title)->size = 0;
  (src->title)->prev = NULL;*/
  /*product *head, *prd=(product *) malloc(sizeof(product));;
  prd->n = NULL;
  prd->prev= NULL;
  prd->contains = NULL;
  prd->title = (str *) malloc(sizeof(str));
  (prd->title)->size = 0;
  (prd->title)->prev = NULL;*/
  FILE *f = fopen ("in.txt", "r");
  // while (!feof(f)){ 
    in_source(f, &src);
   fclose(f);
   f = fopen("in-product.txt", "r");
   in_product (f, &prd, src);
   fclose(f);
   a_src *t;
   while (prd != NULL){
     printf ("%d", prd->id);
     print_title(prd->title);
     t = prd->contains;
     printf ("contains:");
     while (t!= NULL){
       printf ("%d %f ", (t->src)->id, t->num);
       print_title((t->src)->title);
       t = t->n;
     }
     printf ("\n============\n");
     prd = prd->n;
   }
   /*f = fopen ("in-product.txt", "r");
   in_product(&f, &prd, src);
   fclose(f);
    //  }
   head = get_head_product(prd);
   a_src *d=NULL;
   source *rt = get_head_source(src);
   while (rt!=NULL){
     printf ("%d\n", rt->id);
     rt = rt->n;
   }
   
   while (head != NULL){
    printf("product id:%d name:", head->id);
    print_title(head->title);
    printf("\n");
    //d = head->contains;
    //    d = d->prev;
    printf("contains: ");
    while (d!=NULL){
      printf("dd");
      print_title((d->src)->title);
      printf(" num:%f\n", d->num, (d->src)->type);
      d = d->n;
    }
    head = head->n;
    printf("=============\n");
    } */
  
  
}
