#include <stdio.h>
#include <stdlib.h>
#define TITLE_SIZE 2
#define BLOCK_SIZE 2
typedef struct str{
  char data[TITLE_SIZE];
  unsigned size;
  struct str *n;
  struct str *prev;
}str;

typedef struct source{
  unsigned id;
  unsigned num;
  str *title;
  struct source *n;
  struct source *prev;
}source;

typedef struct a_src{
  source *src;
  unsigned num;
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
  a_product *contains;
  str *title;
  struct order *n;
  struct order *prev;
}order;


void in_source (FILE **f, source **el);
void in_product (FILE **f, product **el);
void in_orders (FILE **f, order **el);
void print_title (str *head);
str * get_head (str *el);
source * get_head_source (source *el);
source * get_source (source *el, unsigned id);

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

void in_product (FILE **f, product **el, source *src1){
  char c;
  int i=0,j=0, was_set=0;
  unsigned id, num;
  str *title;
  product *tmp;
  a_src *t;
  
  while(!feof(*f)){
    i=0;
  while (i<BLOCK_SIZE && fscanf(*f, "%c", &c) != EOF){
    printf("%c", c);
    if (!was_set){
      if(i!=0){ tmp = (source *) malloc (sizeof(source));
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
      }
      
      was_set = 1;
    }

    if (c == '\n'){
	was_set = 0;
	i++;
    }else if (c == '#'){
      if (fscanf (*f, "%d:%d", &id, &num)!=EOF){
	
	  t = (a_src *) malloc (sizeof(a_src));
	  t->prev = (*e)->contains;
	  t->n = NULL;
	  t->src = get_source(src1, id);
	  t->num = num;
	  if ((*e)->contains != NULL)
	    ((*e)->contains)->n = t;
	  (*e)->contains = t;
	
      i++;
      }
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
}

void in_source (FILE **f, source **el){
  char c;
  int i=0,j=0, was_set=0;
  unsigned id, num;
  str *title;
  source *tmp;
  while(!feof(*f)){
    i=0;
  while (i<BLOCK_SIZE && fscanf(*f, "%c", &c) != EOF){
    printf("%c", c);
    if (!was_set){
      if(i!=0){ tmp = (source *) malloc (sizeof(source));
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
      }
      
      was_set = 1;
    }

    if (c == '\n'){
	was_set = 0;
	i++;
    }else if (c == '#'){
      if (fscanf (*f, "%d:%d", &id, &num)!=EOF){
      (*el)->id = id;
      (*el)->num = num;
      i++;
      }
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
}


int main(void){
  source *head, *src = (source *) malloc(sizeof(source));
  src->n = NULL;
  src->prev= NULL;
  src->title = (str *) malloc(sizeof(str));
  (src->title)->size = 0;
  (src->title)->prev = NULL;
  head = src;
  FILE *f = fopen ("in.txt", "r");
  // while (!feof(f)){
    
    in_source(&f, &src);
    printf ("sss\n");
    //  }

  while (head != NULL){
    printf("id:%d num:%d", head->id, head->num);
    print_title(head->title);
    printf("\n");
    head = head->n;
  }
  free(src);
  fclose(f);
}
