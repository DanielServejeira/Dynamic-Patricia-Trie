#ifndef PATRICIA_FUNCTIONS
#define PATRICIA_FUNCTIONS

typedef struct node{
    unsigned key; //numero binario
    int bit; //profundidade do no na arvore
    struct no *left, *right; //ponteiros pra esquerda e direita
}Node;

unsigned bit(unsigned key, int k);
void create_patricia(Node **p_tree);
Node *recursive_search(Node *p_tree, unsigned x, int w);
Node *search(Node *p_tree, unsigned x);
Node *recursive_insertion(Node *p_tree, unsigned key, int w, Node *last);
void insertion(Node **p_tree, unsigned key);

#include "patricia_functions.c"

#endif
