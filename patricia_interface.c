#include <stdio.h>
#include <locale.h>
#include <math.h>

#include "patricia_functions.h"

int main() {
    //Adicionar caracteres em PT-BR
    setlocale(LC_ALL, "Portuguese");

    //Declarar árvore e variáveis de menu
    Node *patricia_trie = NULL;
    int language, menu, bits_in_key, k, max_value;

    //Menu de idiomas (EN-US & PT-BR)
    do{
        printf("By Daniel Servejeira & Raphael Leiva\n"
               "\nSelect your language: "
               "\n[1] English"
               "\n[2] Portuguese (Coming soon...)\n\n");
        scanf("%d",&language);

        system("cls");
    }while(language<1 || language>2);

    switch(language) {

        //Interface em EN-US
        case 1:
            printf("\n\tWelcome to the Patricia Trie interface!\n\n");
            system("pause");
            system("cls");

            do {
                printf("\nHow many bits do you want in the Patricia Trie? ");
                scanf("%d",&bits_in_key);
                system("cls");
            }
            while(bits_in_key<1);

            max_value = pow(2, bits_in_key) - 1;

            //Loop de operações da Árvore Patricia
            do{
                printf("\nPatricia Trie Operations - %d bits per node\n"
                       "\n[1] Create Patricia Trie"
                       "\n[2] Destroy Patricia Trie"
                       "\n[3] Search an element"
                       "\n[4] Insert an element"
                       "\n[5] Remove an element"
                       "\n[6] Print Patricia Trie"
                       "\n[0] Exit\n\n", bits_in_key);
                scanf("%d",&menu);

                system("cls");

                switch(menu) {

                    //Sair do menu
                    case 0:
                        printf("\n");
                        break;

                    //Criar Árvore Patricia
                    case 1:
                        if(patricia_trie == NULL) {
                            patricia_trie = (Node*)malloc(sizeof(Node));
                            create_patricia(patricia_trie);
                        }
                        else printf("\nA Patricia Trie already exists in memory. Destroy it before creating another one.\n");

                        printf("\n");
                        break;

                    //Destruir Árvore Patricia
                    case 2:
                        if(patricia_trie != NULL) {
                            destroy_patricia(patricia_trie);
                            free(patricia_trie);
                            patricia_trie = NULL;
                        }
                        else printf("\nA Patricia Trie does not exists in memory. Create it before destroy one.\n");

                        printf("\n");
                        break;

                    //Buscar elemento na Árvore Patricia
                    case 3:
                        if(patricia_trie != NULL) {
                            if(!is_empty(patricia_trie)) {
                                printf("\nType the element you are looking for: ");
                                scanf("%d",&k);

                                printf("\n\t%d\n", search(patricia_trie, k, bits_in_key));
                            }
                            else printf("\nInsert an element before searching for it!\n");
                        }
                        else printf("\nCreate a Patricia Trie before searching for an element!\n");

                        printf("\n");
                        break;

                    //Inserir elemento na Árvore Patricia
                    case 4:
                        if(patricia_trie != NULL) {
                            do{
                                printf("\nType the binary element you want to insert (%d bits maximum): ", bits_in_key);
                                scanf("%d",&k);
                            }while(k<0 || k>max_value);

                            insertion(patricia_trie, k, bits_in_key);
                        }
                        else printf("\nCreate a Patricia Trie before inserting an element!\n");

                        printf("\n");
                        break;

                    //Remover elemento na Árvore Patricia
                    case 5:
                        if(patricia_trie != NULL) {
                            if(!is_empty(patricia_trie)) {
                                //remove((*p_trie));
                            }
                            else printf("\nInsert an element before removing one!\n");
                        }
                        else printf("\nCreate a Patricia Trie before removing an element!\n");

                        break;

                    //Imprimir Árvore Patricia
                    case 6:
                        if(patricia_trie != NULL) {
                            if(!is_empty(patricia_trie)) {
                                print_patricia(patricia_trie);
                            }
                            else printf("\nThe Patricia Trie is empty.\n");
                        }
                        else printf("\nCreate a Patricia Trie before printing it!\n");

                        printf("\n");
                        break;

                    //Opção inválida
                    default:
                        printf("\nChoose a valid option!\n\n");
                        break;
                }

                system("pause");
                system("cls");

            }while(menu!=0);

            break;

        //Interface em PT-BR
        case 2:
            printf("\n\tBem-vindo à interface de Patricia Trie\n\n");
            system("pause");
            system("cls");

            do{
                menu = 0;
            }while(menu!=0);

            break;
    }

    return 0;
}
