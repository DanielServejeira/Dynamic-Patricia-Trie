#ifndef PATRICIA_FUNCTIONS
#define PATRICIA_FUNCTIONS

#include <stdbool.h>

typedef struct node{
    unsigned key; //numero binario
    int bit; //profundidade do no na arvore
    struct node *left, *right; //ponteiros pra esquerda e direita
}Node;

unsigned bit(unsigned key, int k);
void create_patricia(Node **p_trie);
bool is_empty(Node *p_trie);
Node *recursive_find_depth(Node *p_trie, int w);
void destroy_patricia(Node **p_trie);
Node *recursive_search(Node *p_trie, unsigned x, int w);
Node *search(Node *p_trie, unsigned x);
Node *recursive_insertion(Node *p_trie, unsigned key, int w, Node *last);
void insertion(Node **p_trie, unsigned key);

#include "patricia_functions.c"

#endif
