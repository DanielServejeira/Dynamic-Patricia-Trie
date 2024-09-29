#include<stdio.h>
#include<locale.h>

#include "patricia_functions.h"

int main() {
    //Adicionar caracteres em PT-BR
    setlocale(LC_ALL, "Portuguese");

    //Declarar árvore e variáveis de menu
    Node *patricia_trie = NULL;
    int language, menu, k;

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

            //Loop de operações da Árvore Patricia
            do{
                printf("\n[1] Create Patricia Trie"
                       "\n[2] Destroy Patricia Trie"
                       "\n[3] Search an element"
                       "\n[4] Insert an element"
                       "\n[5] Remove an element"
                       "\n[6] Print Patricia Trie"
                       "\n[0] Exit\n\n");
                scanf("%d",&menu);

                system("cls");

                switch(menu) {

                    //Sair do menu
                    case 0:
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
                            if(!is_empty) {
                                printf("\nType the element you are looking for: ");
                                scanf("%d",&k);

                                printf("\n\t%d\n", search(patricia_trie, k));
                            }
                            else printf("\nInsert an element before searching for it!\n");
                        }
                        else printf("\nCreate a Patricia Trie before searching for an element!\n");

                        printf("\n");
                        break;

                    //Inserir elemento na Árvore Patricia
                    case 4:
                        if(patricia_trie != NULL) {
                            printf("\nType the element you want to insert: ");
                            scanf("%d",&k);

                            insertion(patricia_trie, k);
                        }
                        else printf("\nCreate a Patricia Trie before inserting an element!\n");

                        printf("\n");
                        break;

                    //Remover elemento na Árvore Patricia
                    case 5:
                        break;

                    //Imprimir Árvore Patricia
                    case 6:
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
