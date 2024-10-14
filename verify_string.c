#include <string.h>
#include <ctype.h>  // Adicione essa biblioteca para isdigit()
#include <stdlib.h> // Para atoi()

/**
 * Funcao para verificar se o input e um numero valido.
 * @param str Ponteiro para uma string de caracteres.
 * @return -1 se nao for digito, e retorna o valor inteiro da string se for digito.
 */

int verify_string(const char *str) {
    if (*str == '\0') return -1;  // Verifica se a string está vazia

    const char *p = str;          // Ponteiro para percorrer a string
    while (*p != '\0') {          // Verifica cada caractere
        if (!isdigit(*p)) {
            return -1;            // Retorna -1 se encontrar um caractere não numérico
        }
        p++;
    }

    return atoi(str);             // Converte a string original e retorna o valor numérico
}

/**
 * Funcao para remover o '\n' da string e poder convertê-la para um int 
 * @param str Ponteiro para uma string de caracteres
 */
void remove_newline(char *str) {    //
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';  // Remove o caractere '\n'
    }
}

/**
 * Funcao para limpar o buffer manualmente para evitar erros ligados a residuos de leitura
 * @param  null
 * @return void 
 */
void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Consome até o final da linha
}
