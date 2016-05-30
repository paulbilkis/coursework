#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int iscorrect(int *res, int el){
  int i, sum=0;
  for (i=0; i<6; i++)
    sum+=res[i];
  if ((sum + el) <= 7) return 1;
  else return 0;
}

int longest_solution (int **solutions, int n, int max){
  int i,j;
  for (i=0; i<n; i++){
    for (j=0; j<=max && solutions[i][j] != 0; j++);
    if (j == max+1){
      return i;
    }
  }
}

int max=0;
int **d;
int size=0;

int recursive (int *p, int *res, int j, int cur){
  if (j >= 6) return 1;
  int i;
  for (i = j; i<6; i++){
    if (iscorrect (res, p[i])){
       if (cur > max)
       max = cur;
      res[cur] = p[i];
      int s=0;
      for (s=0; s<6;s++)
	printf("_%d %d\n", res[s], cur);
      printf("=========");
      d = (int**) realloc(d, (size+1)*sizeof(int*));
      d[size] = (int*) malloc((6)*sizeof(int));
      memcpy(d[size], res, (6)*sizeof(int));
      size++;
      
      if (recursive (p, res, i+1, cur+1)) return 1;
      res[cur] = 0; //backtrace
    }
  }

  return 0;
}

int main (void){
  int p[6] = {1,1,2,3,4,5};
  int res[6]={0,0,0,0,0,0};
  recursive(p, res, 0, 0);
  int ls = longest_solution(d, size, max);
  int i=0,j;
  //for (i=0; i<size; i++){
    for(j=0; j<=max;j++)
      printf ("%d %d\n", d[ls][j], ls);
  printf("==========");
  //}
}
