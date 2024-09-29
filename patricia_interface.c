#include<stdio.h>
#include<locale.h>

#include "patricia_functions.h"

int main() {
    //Adicionar caracteres em PT-BR
    setlocale(LC_ALL, "Portuguese");

    //Declarar árvore e variáveis de menu
    Node *patricia_tree = NULL;
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
            printf("\n\tWelcome to the Patricia Tree interface!\n\n");
            system("pause");
            system("cls");

            //Loop de operações da Árvore Patricia
            do{
                printf("\n[1] Create Patricia Tree"
                       "\n[2] Destroy Patricia Tree"
                       "\n[3] Search an element"
                       "\n[4] Insert an element"
                       "\n[5] Remove an element"
                       "\n[6] Print Patricia Tree"
                       "\n[0] Exit\n\n");
                scanf("%d",&menu);

                system("cls");

                switch(menu) {

                    //Sair do menu
                    case 0:
                        break;

                    //Criar Árvore Patricia
                    case 1:
                        if(patricia_tree == NULL) {
                            patricia_tree = (Node*)malloc(sizeof(Node));
                            create_patricia(patricia_tree);
                        }
                        else printf("\nA Patricia Tree already exists in memory. Destroy it before creating another one.\n");

                        printf("\n");
                        break;

                    //Destruir Árvore Patricia
                    case 2:
                        break;

                    //Buscar elemento na Árvore Patricia
                    case 3:
                        if(patricia_tree != NULL) {
                            if(patricia_tree->bit != -1) {
                                printf("\nType the element you are looking for: ");
                                scanf("%d",&k);

                                printf("\n\t%d\n", search(patricia_tree, k));
                            }
                            else printf("\nInsert an element before searching for it!\n");
                        }
                        else printf("\nCreate a Patricia Tree before searching for an element!\n");

                        printf("\n");
                        break;

                    //Inserir elemento na Árvore Patricia
                    case 4:
                        if(patricia_tree != NULL) {
                            printf("\nType the element you want to insert: ");
                            scanf("%d",&k);

                            insertion(patricia_tree, k);
                        }
                        else printf("\nCreate a Patricia Tree before inserting an element!\n");

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
            printf("\n\tBem-vindo à interface de Árvore Patricia\n\n");
            system("pause");
            system("cls");

            do{
                menu = 0;
            }while(menu!=0);

            break;
    }

    return 0;
}
