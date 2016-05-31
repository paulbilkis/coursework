#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers.h"
/*
void delete_uncorrect_prd_from_ord(order *hd){
  order *head = get_head_order(hd);
  a_product *cur, *temp;
  whi
}
*/
void delete_imp_orders (order *ord, source *src){
  order *temp,*head = get_head_order(ord);
  while (head!=NULL){
    if(!iscorrect(src,ord,0,0,head->id)){
      if(head->n != NULL) (head->n)->prev = head->prev;
      if (head->prev != NULL) (head->prev)->n = head->n;
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
  order *prev=NULL,*temp=NULL,*orde=NULL;
  for (i=0; i<n; i++){
    orde = (order*) malloc(sizeof(order));
    temp = get_order(ord, orders[i]);
    memcpy(orde, temp, sizeof(order));
    orde->n = NULL;
    orde->prev = prev;
    if (prev !=NULL) prev->n = orde;
    prev = orde;
  }
  return get_head_order(orde);
}

int from_list_to_arg (order *ord, int **arg_1){
  order *head = get_head_order(ord);
  int *arg = (int*) malloc(sizeof(int));
  int n=0;
  while(head!=NULL){
    arg = (int*) realloc(arg, (n+1)*sizeof(int));
    arg[n] = head->id;
    n++;
    head = head->n;
  }
  *arg_1 = arg;
  return n;
}

int longest_solution (int **solutions, order *ord, int n, int maxx){
  int i,j, mx=0, nm=0, i_max=0;
  order *or;
  for (i=0; i<n; i++){
    nm=0;
    for (j=0; j<=maxx; j++){
      if (solutions[i][j] != 0){
	or = get_order(ord, solutions[i][j]);
	nm += or->num;
      }
    }
    if (nm > mx){
      mx = nm;
      i_max = i;
    }
  }
  return i_max;
}

int max=0;
int **d;
int size=0;


int recursive (source *src, order *ord, int *p, int *res, int j, int cur, int n){
  if (j >= n) return 1;
  int i;
  for (i = j; i<n; i++){
    if (iscorrect (src, ord, n-1, res, p[i])){
       if (cur > max)
       max = cur;
      res[cur] = p[i];
      /*int s=0;
      for (s=0; s<n;s++)
      printf("_%d %d\n", res[s], cur);
      printf("=========");*/
      d = (int**) realloc(d, (size+1)*sizeof(int*));
      d[size] = (int*) malloc(n*sizeof(int));
      memcpy(d[size], res, n*sizeof(int));
      size++;
      
      if (recursive (src, ord, p, res, i+1, cur+1, n)) return 1;
      res[cur] = 0; //backtrace
    }
  }

  return 0;
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
	if(res[i]!=0){
	  num += num_of_res(ord, res[i], hsrc->id);
	  //printf("\n\n%d %d %f\n\n", hsrc->id, res[i], num);
	}
      }
    }
    num += num_of_res(ord, p, hsrc->id);
    //printf("%d %f*@*#*$\n", p, num);
    if (num > hsrc->num) return 0;
    hsrc = hsrc->n;
  }
  return 1;
}

float num_of_res (order *ord, unsigned order_id, unsigned source_id){
  order *ordr = get_order(ord, order_id);
  product *aprd = ordr->contains;
  a_src *asrc;
  float num=0;
    asrc = aprd->contains;//начало списка состава a_src
    while (asrc!=NULL){
      if ((asrc->src)->id == source_id)
	  num += ordr->num * asrc->num;
      asrc = asrc->n;
    }
  return num;
}
