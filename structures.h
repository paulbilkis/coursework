#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <stdio.h>
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
  unsigned client_id;
  unsigned num;
  product *contains;
  struct order *n;
  struct order *prev;
}order;

typedef struct client{
  unsigned id;
  str *title;
  struct client *n;
  struct client *prev;
}client;

#endif // STRUCTURES_H
