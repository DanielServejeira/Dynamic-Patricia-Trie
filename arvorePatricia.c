#include<stdio.h>
#include<limits.h>

#define bitsNaChave 4

typedef struct no {
    unsigned chave; //numero binario
    int bit; //profundidade do no na arvore
    struct no *esq, *dir; //ponteiros pra esquerda e direita
} No;

unsigned bit(unsigned chave, int k) { //chave = numero binario; k = posicao do bit desejado
    return chave >> (bitsNaChave - k-1) & 1; //desloca k-1 bits pra direita e retorna a comparacao por 1
}

void inicializa(No **arvore) { //no ponteiro de ponteiro
    *arvore = malloc(sizeof(No)); //aloca no na memoria
    (*arvore)->chave = UINT_MAX; //11111111111...
    (*arvore)->esq = (*arvore)->dir = *arvore; //aponta pra ela mesma
    (*arvore)->bit = -1; //bit do no dummy sempre -1
}

No *busca_rec(No *arvore, unsigned x, int w) { //x = chave procurada; w = altura do no
    if (arvore->bit <= w) return arvore; //se a altura do no for menor ou igual a w, retorna a arvore

    if (bit(x, arvore->bit) == 0) return busca_rec(arvore->esq, x, arvore->bit); //se o bit correspondente a profundidade do no eh = 0, busca esquerda
    else return busca_rec(arvore->dir, x, arvore->bit); //senao, busca direita
}

No *busca(No *arvore, unsigned x) {
    No *t = busca_rec(arvore->esq, x, -1); //t recebe o no achado
    return t->chave == x ? t : NULL; //se for igual a procura, retorna o no, senao nulo
}

No *insere_rec(No *arvore, unsigned chave, int w, No *pai) { //ponteiro de no
    No *novo; //cria novo no que sera inserido

    if (arvore->bit >= w || arvore->bit <= pai->bit) { //se o bit atual for maior ou igual a w ou o bit atual for menor ou igual ao bit atual do pai
        novo = malloc(sizeof(No)); //define novo no
        novo->chave = chave;
        novo->bit = w;

        if (bit(chave, novo->bit) == 1) { //se a posicao atual do bit na chave for igual a 1
            novo->esq = arvore; //esquerda aponta pra outro no
            novo->dir = novo; //direita aponta pra ele mesmo
        }
        else {
            novo->esq = novo; //esquerda aponta pra ela mesma
            novo->dir = arvore; //direita aponta pra outro no
        }

        return novo; //retorna novo no
    }

    if (bit(chave, arvore->bit) == 0) arvore->esq = insere_rec(arvore->esq, chave, w, arvore); //se o bit atual for = 0, recursao pra esquerda
    else arvore->dir = insere_rec(arvore->dir, chave, w, arvore); //senao, recursao pra direita

    return arvore;
}

void insere(No **arvore, unsigned chave) { //ponteiro de ponteiro do no da arvore
    int i;

    No *t = busca_rec((*arvore)->esq, chave, -1); //faz a busca
    if (chave == t->chave) return; //se a busca for igual a chave que seria inserida, nao insere

    for (i = 0; bit(chave, i) == bit(t->chave, i); i++) ; //enquanto os bits forem iguais
        (*arvore)->esq = insere_rec((*arvore)->esq, chave, i, *arvore); //insere recursivamente na arvore
}

int main() {

    return 0;
}
