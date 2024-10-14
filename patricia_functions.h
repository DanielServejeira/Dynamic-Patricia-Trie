#ifndef PATRICIA_FUNCTIONS
#define PATRICIA_FUNCTIONS

typedef struct node{
    char *key; //numero binario
    int bit; //profundidade do no na arvore
    struct node *left, *right; //ponteiros pra esquerda e direita
}Node;

unsigned bit(char *key, int k);
void create_patricia(Node **p_trie);
int is_empty(Node *p_trie);
Node *recursive_find_depth(Node *p_trie, int w);
void destroy_patricia(Node **p_trie);
Node *recursive_search(Node *p_trie, char *key, int w);
Node *search(Node *p_trie, char *key);
Node *recursive_insertion(Node *p_trie, char *key, int w, Node *last);
void insertion(Node **p_trie, char *key);
void delete_node(Node *p_trie, unsigned key, int bits_in_key);

#include "patricia_functions.c"

#endif
