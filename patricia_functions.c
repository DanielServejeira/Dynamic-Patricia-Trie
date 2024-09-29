#include<limits.h>

#define bits_in_key 4

unsigned bit(unsigned key, int k) { //chave = numero binario; k = posicao do bit desejado
    return key >> (bits_in_key - k-1) & 1; //desloca k-1 bits pra direita e retorna a comparacao por 1
}

void create_patricia(Node **p_tree) { //no ponteiro de ponteiro
    *p_tree = malloc(sizeof(Node)); //aloca no na memoria
    (*p_tree)->key = UINT_MAX; //11111111111...
    (*p_tree)->left = (*p_tree)->right = *p_tree; //aponta pra ela mesma
    (*p_tree)->bit = -1; //bit do no dummy sempre -1
}

Node *recursive_search(Node *p_tree, unsigned x, int w) { //x = chave procurada; w = altura do no
    if (p_tree->bit <= w) return p_tree; //se a altura do no for menor ou igual a w, retorna a arvore

    if (bit(x, p_tree->bit) == 0) return recursive_search(p_tree->left, x, p_tree->bit); //se o bit correspondente a profundidade do no eh = 0, busca esquerda
    else return recursive_search(p_tree->right, x, p_tree->bit); //senao, busca direita
}

Node *search(Node *p_tree, unsigned x) {
    Node *tree = recursive_search(p_tree->left, x, -1); //t recebe o no achado
    return tree->key == x ? tree : NULL; //se for igual a procura, retorna o no, senao nulo
}

Node *recursive_insertion(Node *p_tree, unsigned key, int w, Node *last) { //ponteiro de no
    Node *new_node; //cria novo no que sera inserido

    if (p_tree->bit >= w || p_tree->bit <= last->bit) { //se o bit atual for maior ou igual a w ou o bit atual for menor ou igual ao bit atual do pai
        new_node = malloc(sizeof(Node)); //define novo no
        new_node->key = key;
        new_node->bit = w;

        if (bit(key, new_node->bit) == 1) { //se a posicao atual do bit na chave for igual a 1
            new_node->left = p_tree; //esquerda aponta pra outro no
            new_node->right = new_node; //direita aponta pra ele mesmo
        }
        else {
            new_node->left = new_node; //esquerda aponta pra ela mesma
            new_node->right = p_tree; //direita aponta pra outro no
        }

        return new_node; //retorna novo no
    }

    if (bit(key, p_tree->bit) == 0) p_tree->left = recursive_insertion(p_tree->left, key, w, p_tree); //se o bit atual for = 0, recursao pra esquerda
    else p_tree->right = recursive_insertion(p_tree->right, key, w, p_tree); //senao, recursao pra direita

    return p_tree;
}

void insertion(Node **p_tree, unsigned key) { //ponteiro de ponteiro do no da arvore
    int i;

    Node *tree = recursive_search((*p_tree)->left, key, -1); //faz a busca
    if (key == tree->key) return; //se a busca for igual a chave que seria inserida, nao insere

    for (i = 0; bit(key, i) == bit(tree->key, i); i++) ; //enquanto os bits forem iguais
        (*p_tree)->left = recursive_insertion((*p_tree)->left, key, i, *p_tree); //insere recursivamente na arvore
}
