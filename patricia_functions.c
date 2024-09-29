#include<limits.h>
#include <stdbool.h>

#define BITS_IN_KEY 4

/**
 * Função para verificar qual o bit em uma posição na chave
 * @param key Chave em binário, pos Posição do bit
 * @return {@code unsigned} | {@code 1} se o bit é 1, {@code 0} se o bit não é 1
 */
unsigned bit(unsigned key, int pos) {
    return key >> (BITS_IN_KEY - pos-1) & 1;
}

/**
 * Função para criar a estrutura da Patricia Trie
 * @param **p_trie Patricia Trie
 */
void create_patricia(Node **p_trie) {
    *p_trie = malloc(sizeof(Node));
    (*p_trie)->key = UINT_MAX;
    (*p_trie)->left = (*p_trie)->right = *p_trie;
    (*p_trie)->bit = -1;
}

/**
 * Função para verificar se a árvore está vazia
 * @param *p_trie Patricia Trie
 * @return {@code boolean} | {@code true} se está vazia, {@code false} se não está vazia
 */
bool is_empty(Node *p_trie) {
    int dummy_bit_value = -1;

    if(p_trie->bit == dummy_bit_value) return true;
    return false;
}

/**
 * Função que retorna um ponteiro para um nó do nível mais profundo da árvore
 * @param *p_trie Patricia Trie, w Profundidade do nó atual
 * @return {@code Node*}
 */
Node *recursive_find_depth(Node *p_trie, int w) {
    if(p_trie->left->bit > w) return recursive_find_depth(p_trie->left, p_trie->left->bit);
    else if(p_trie->right->bit > w) return recursive_find_depth(p_trie->right, p_trie->right->bit);
    else return p_trie;
}

/**
 * Função para destruir Patricia Trie
 * @param **p_trie Patricia Trie
 */
void destroy_patricia(Node **p_trie) {
    Node *node = NULL;

    while(!is_empty((*p_trie))) {
        node = recursive_find_depth((*p_trie), (*p_trie)->bit);
        //removal((*p_trie), node);
    }
}

Node *recursive_search(Node *p_trie, unsigned key, int w) { //x = chave procurada; w = altura do no
    if (p_trie->bit <= w) return p_trie; //se a altura do no for menor ou igual a w, retorna a arvore

    if (bit(key, p_trie->bit) == 0) return recursive_search(p_trie->left, key, p_trie->bit); //se o bit correspondente a profundidade do no eh = 0, busca esquerda
    else return recursive_search(p_trie->right, key, p_trie->bit); //senao, busca direita
}

Node *search(Node *p_trie, unsigned x) {
    Node *node = recursive_search(p_trie->left, x, -1); //novo no recebe o no achado
    return node->key == x ? node : NULL; //se for igual a procura, retorna o no, senao nulo
}

Node *recursive_insertion(Node *p_trie, unsigned key, int w, Node *last) { //ponteiro de no
    Node *new_node; //cria novo no que sera inserido

    if (p_trie->bit >= w || p_trie->bit <= last->bit) { //se o bit atual for maior ou igual a w ou o bit atual for menor ou igual ao bit atual do pai
        new_node = malloc(sizeof(Node)); //define novo no
        new_node->key = key;
        new_node->bit = w;

        if (bit(key, new_node->bit) == 1) { //se a posicao atual do bit na chave for igual a 1
            new_node->left = p_trie; //esquerda aponta pra outro no
            new_node->right = new_node; //direita aponta pra ele mesmo
        }
        else {
            new_node->left = new_node; //esquerda aponta pra ela mesma
            new_node->right = p_trie; //direita aponta pra outro no
        }

        return new_node; //retorna novo no
    }

    if (bit(key, p_trie->bit) == 0) p_trie->left = recursive_insertion(p_trie->left, key, w, p_trie); //se o bit atual for = 0, recursao pra esquerda
    else p_trie->right = recursive_insertion(p_trie->right, key, w, p_trie); //senao, recursao pra direita

    return p_trie;
}

void insertion(Node **p_trie, unsigned key) { //ponteiro de ponteiro do no da arvore
    int i;

    Node *tree = recursive_search((*p_trie)->left, key, -1); //faz a busca
    if (key == tree->key) return; //se a busca for igual a chave que seria inserida, nao insere

    for (i = 0; bit(key, i) == bit(tree->key, i); i++) ; //enquanto os bits forem iguais
        (*p_trie)->left = recursive_insertion((*p_trie)->left, key, i, *p_trie); //insere recursivamente na arvore
}
