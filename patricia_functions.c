#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "patricia_functions.h"

/**
 * Função para verificar se o bit já foi comparado com todos os bits da chave
 * @param key Chave em binário, pos Posição do bit, bits_in_key Quantidade de bits na chave
 */
int safeBitTest(char *key, int pos)
{
    int key_lenght = strlen(key);

    if (pos < key_lenght * 16)
        return bit(key, pos) != 0;
    if (pos > key_lenght * 16 + 15)
        return 0;
    return 1;
}

/**
 * Fun��o para verificar qual o bit em uma posi��o na chave
 * @param *key Chave de caracteres (string)
 * @param pos Posi��o do bit
 * @return {@code unsigned} | {@code 1} se o bit � 1, {@code 0} se o bit n�o � 1
 */
unsigned bit(char *key, int pos)
{
    int char_size = 8;
    int bits_in_key = char_size - 1;
    int char_index = pos / char_size; // index do caractere na string
    int bit_index = pos % char_size;  // posicao do bit dentro do caractere

    return key[char_index] >> (bits_in_key - bit_index) & 1;
}

/**
 * Fun��o para criar a estrutura da Patricia Trie
 * @param **p_trie Patricia Trie
 */
void create_patricia(Node **p_trie)
{
    *p_trie = malloc(sizeof(Node));
    (*p_trie)->key = NULL;
    (*p_trie)->left = (*p_trie)->right = *p_trie;
    (*p_trie)->bit = -1;
}

/**
 * Fun��o para verificar se a �rvore est� vazia
 * @param *p_trie Patricia Trie
 * @return {@code int} | {@code 1} se est� vazia, {@code 0} se n�o est� vazia
 */
int is_empty(Node *p_trie)
{
    int dummy_bit_value = -1;

    if (p_trie->left->bit == dummy_bit_value)
        return 1;
    return 0;
}

/**
 * Fun��o que retorna um ponteiro para um n� do n�vel mais profundo da �rvore
 * @param *p_trie Patricia Trie
 * @param w Profundidade do n� atual
 * @return {@code Node*}
 */
Node *recursive_find_depth(Node *p_trie, int w)
{
    if (p_trie->left->bit > w)
        return recursive_find_depth(p_trie->left, p_trie->left->bit);
    else if (p_trie->right->bit > w)
        return recursive_find_depth(p_trie->right, p_trie->right->bit);
    else
        return p_trie;
}

/**
 * Fun��o para destruir Patricia Trie
 * @param **p_trie Patricia Trie
 */
void destroy_patricia(Node **p_trie)
{
    Node *node;

    while (!is_empty(*p_trie))
    {
        node = recursive_find_depth(*p_trie, (*p_trie)->bit);
        delete_node(node, node->key);
    }
}

/**
 * Fun��o recursiva que retorna o n� cuja profundidade n�o � maior que a de seu antecessor
 * @param *p_trie Patricia Trie
 * @param *key Chave de caracteres (string)
 * @param w Profundidade do n� atual
 * @return {@code Node*}
 */
Node *recursive_search(Node *p_trie, char *key, int w)
{ // x = chave procurada; w = altura do no
    if (p_trie->bit <= w)
        return p_trie; // se a altura do no for menor ou igual a w, retorna a arvore

    if (safeBitTest(key, p_trie->bit) == 0)
        return recursive_search(p_trie->left, key, p_trie->bit); // se o bit correspondente a profundidade do no eh = 0, busca esquerda
    else
        return recursive_search(p_trie->right, key, p_trie->bit); // senao, busca direita
}

/**
 * Fun��o que retorna se a chave foi encontrada
 * @param *p_trie Patricia Trie
 * @param *key Chave de caracteres (string)
 * @return {@code Node*}
 */
Node *search(Node *p_trie, char *key)
{
    Node *node = recursive_search(p_trie->left, key, -1); // novo no recebe o no achado
    return node->key == key ? node : NULL;                // se for igual a procura, retorna o no, senao nulo
}

/**
 * Fun��o recursiva que retorna o novo n� inserido
 * @param *p_trie Patricia Trie
 * @param *key Chave de caracteres (string)
 * @param w Profundidade do n� atual
 * @param *last N� antecessor
 * @return {@code Node*}
 */
Node *recursive_insertion(Node *p_trie, char *key, int w, Node *last)
{                   // ponteiro de no
    Node *new_node; // cria novo no que sera inserido

    if (p_trie->bit >= w || p_trie->bit <= last->bit)
    {                                    // se o bit atual for maior ou igual a w ou o bit atual for menor ou igual ao bit atual do pai
        new_node = malloc(sizeof(Node)); // define novo no
        new_node->key = key;
        new_node->bit = w;

        if (safeBitTest(key, new_node->bit) == 1)
        {                               // se a posicao atual do bit na chave for igual a 1
            new_node->left = p_trie;    // esquerda aponta pra outro no
            new_node->right = new_node; // direita aponta pra ele mesmo
        }
        else
        {
            new_node->left = new_node; // esquerda aponta pra ela mesma
            new_node->right = p_trie;  // direita aponta pra outro no
        }

        return new_node; // retorna novo no
    }

    if (safeBitTest(key, p_trie->bit) == 0)
        p_trie->left = recursive_insertion(p_trie->left, key, w, p_trie); // se o bit atual for = 0, recursao pra esquerda
    else
        p_trie->right = recursive_insertion(p_trie->right, key, w, p_trie); // senao, recursao pra direita

    return p_trie;
}

/**
 * Fun��o que insere um n�
 * @param **p_trie Patricia Trie
 * @param *key Chave de caracteres (string)
 */
void insertion(Node **p_trie, char *key)
{ // ponteiro de ponteiro do no da arvore
    int i;

    Node *tree = recursive_search((*p_trie)->left, key, -1); // faz a busca
    if (key == tree->key)
        return; // se a busca for igual a chave que seria inserida, nao insere

    for (i = 0; safeBitTest(key, i) == safeBitTest(tree->key, i); i++)
        ;                                                                    // enquanto os bits forem iguais
    (*p_trie)->left = recursive_insertion((*p_trie)->left, key, i, *p_trie); // insere na arvore
}

void delete_node(Node *root, char *key)
{
    Node *grand_parent = NULL;
    Node *parent = root;
    Node *current = root;

    do
    {
        grand_parent = parent;
        parent = current;
        if (safeBitTest(key, current->bit) == 0)
            current = current->left;
        else
            current = current->right;
    } while (parent->bit < current->bit);

    if (current->key != key)
        return;

    Node *true_parent;
    Node *aux = root;
    do
    {
        true_parent = aux;
        if (safeBitTest(key, aux->bit) == 0)
            aux = aux->left;
        else
            aux = aux->right;
    } while (aux != current);

    if (current == parent) // Caso o nó seja folha
    {
        Node *current_child;
        if (safeBitTest(key, current->bit) == 0)
            current_child = current->right;
        else
            current_child = current->left;

        if (safeBitTest(key, true_parent->bit) == 0)
            true_parent->left = current_child;
        else
            true_parent->right = current_child;

        free(current);
        return;
    }

    // Se o nó for interno
    Node *sibling;

    if (safeBitTest(key, parent->bit) == 0)
        sibling = parent->right;
    else
        sibling = parent->left;

    if (safeBitTest(key, grand_parent->bit) == 0)
        grand_parent->left = sibling;
    else
        grand_parent->right = sibling;

    if (safeBitTest(key, true_parent->bit) == 0)
        true_parent->left = parent;
    else
        true_parent->right = parent;

    parent->bit = current->bit;
    parent->left = current->left;
    parent->right = current->right;

    free(current);
}

/**
 * Function to print the Patricia Trie
 * @param *node current node
 * @param *root Patricia trie root
 * @param int level
 */
void print_patricia(Node * node, Node * root, int level){

    if(node->bit == -1){        //juntar os dois?
            return;
    }
    if(node->bit <= root->bit){
        return;
    }

    print_patricia(node->right, node, level + 1);

    if(node->bit == 0){
        printf("%s(%d)(Left-%s, Right- %s)/\t\n", node->key, node->bit, node->left->key, node->right->key);
    }else{

        for(int i = 0; i < level; i++){
            printf("   ");
        }
        printf("%s(%d)(Left-%s, Right-%s)\n", node->key, node->bit, node->left->key, node->right->key);
    }
    print_patricia(node->left, node, level + 1);
}