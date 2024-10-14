#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#define INVALID_NUMBER -1
#define MAX_LENGHT 50
#include "patricia_functions.h"
#include "verify_string.h"


int main(){
    // Adicionar caracteres em PT-BR
    setlocale(LC_ALL, "Portuguese");

    //Declarar �rvore e vari�veis de menu
    Node *patricia_trie = NULL;
    int number_language,number_menu, number_bits_in_key, max_value;
    char str_language[2], str_menu[2], str_bits_in_key[10], word[MAX_LENGHT];
    
    
    printf("By Daniel Servejeira & Raphael Leiva & Rennan Collado\n");
    
    //Menu de idiomas (EN-US & PT-BR)
    do{
        printf("\nSelect your language: "
               "\n[1] English"
               "\n[2] Portuguese (Coming soon...)\n\n");
        fgets(str_language, sizeof(str_language),stdin);
        remove_newline(str_language);
        clear_stdin();
          

        number_language = verify_string(str_language); 

        printf("Retorno %d\n", number_language);          

        if(number_language == INVALID_NUMBER){
            printf("Invalid input. Please enter a valid number.\n");
            continue;
        }
        system("pause");
        system("cls");
        
        if(number_language != 1 && number_language != 2){
            printf("Invalid selection. Please choose [1] for English or [2] for Portuguese.\n");
            continue;
        } 
    }while(number_language<1 || number_language>2);

    switch(number_language) {
    //Interface em EN-US
        case 1:
            printf("\n\tWelcome to the Patricia Trie interface!\n\n");
            system("pause");
            system("cls");

            do {
                printf("\nHow many bits do you want in the Patricia Trie? ");     //Verificar aqui o tam max?
                //scanf("%d",&number_bits_in_key);
                fgets(str_bits_in_key, sizeof(str_bits_in_key),stdin);
                remove_newline(str_bits_in_key);
                clear_stdin();

                number_bits_in_key = verify_string(str_bits_in_key);

                printf("Retorno %d\n", number_bits_in_key); 

                if(number_bits_in_key == INVALID_NUMBER){
                    printf("Invalid input. Please enter a valid positive number.\n");
                    continue;
                }

                system("cls");

                if(number_bits_in_key < 1){
                    printf("Please enter a number greater than 0.\n");
                    continue;
                }
            }while(number_bits_in_key<1);

            max_value = pow(2, number_bits_in_key) - 1;

            //Loop de opera��es da �rvore Patricia
            do{
                printf("\nPatricia Trie Operations - %d bits per node\n"
                       "\n[1] Create Patricia Trie"
                       "\n[2] Destroy Patricia Trie"
                       "\n[3] Search an element"
                       "\n[4] Insert an element"
                       "\n[5] Remove an element"
                       "\n[6] Print Patricia Trie"
                       "\n[0] Exit\n\n", number_bits_in_key);
                fgets(str_menu, sizeof(str_menu),stdin);
                remove_newline(str_menu);
                clear_stdin();  

                number_menu = verify_string(str_menu);

                if(number_menu){
                    printf("Invalid input. Please enter a valid positive number.\n");
                    continue;
                }

                printf("\n");
                break;

                switch(number_menu) {
                    //Sair do menu
                    case 0:
                        printf("\n");
                        break;

                    //Criar �rvore Patricia
                    case 1:
                        if(patricia_trie == NULL) {
                            patricia_trie = (Node*)malloc(sizeof(Node));
                            create_patricia(patricia_trie);
                        }
                        else printf("\nA Patricia Trie already exists in memory. Destroy it before creating another one.\n");

                        Node *result = search(patricia_trie, word, number_bits_in_key); //Alterei aqui
                        break; //Aqui?

                    //Destruir �rvore Patricia
                    case 2:
                        if(patricia_trie != NULL) {
                            destroy_patricia(patricia_trie);
                            free(patricia_trie);
                            patricia_trie = NULL;
                        }
                        else printf("\nA Patricia Trie does not exists in memory. Create it before destroy one.\n");

                        printf("\n");
                        break;

                    //Buscar elemento na �rvore Patricia
                    case 3:
                        if(patricia_trie != NULL) {
                            if(!is_empty(patricia_trie)) {
                                printf("\nType the element you are looking for: ");
                                fgets(word, sizeof(word),stdin);
                                 Node *result = search(patricia_trie, word, number_bits_in_key);    //Aqui krai

                                result != NULL ? printf("\n\tElement %d found!\n", result->key) : printf("\nElement not found!\n");
                                printf("\n\t%s\n", search(patricia_trie, word, number_bits_in_key)); //VERIFICAR ESSE PONTO
                            }
                            else printf("\nInsert an element before searching for it!\n");
                        }
                        else printf("\nCreate a Patricia Trie before searching for an element!\n");

                        printf("\n");
                        break;

                    //Inserir elemento na �rvore Patricia
                    case 4: //MODIFICAR INSERÇÂO INTEIRA
                        if(patricia_trie != NULL) {
                            do{
                                printf("\nType the binary element you want to insert (%d bits maximum): ", number_bits_in_key);
                                fgets(word, sizeof(word),stdin);
                            }while(word<0 || word>max_value);

                            insertion(patricia_trie, word, number_bits_in_key);
                        }
                        else printf("\nCreate a Patricia Trie before inserting an element!\n");

                        printf("\n");
                        break;

                    //Remover elemento na �rvore Patricia
                    case 5:
                        if(patricia_trie != NULL) {
                            if(!is_empty(patricia_trie)) {
                                //remove((*p_trie));
                            }
                            else printf("\nInsert an element before removing one!\n");
                        }
                        else printf("\nCreate a Patricia Trie before removing an element!\n");

                        break;

                    //Imprimir �rvore Patricia
                    case 6:
                        if(patricia_trie != NULL) {
                            if(!is_empty(patricia_trie)) {
                                print_patricia(patricia_trie);
                            
                            }else{
                                printf("\nThe Patricia Trie is empty.\n");
                            }
                        }else{
                            printf("\nCreate a Patricia Trie before printing it!\n");
                        }

                        printf("\n");
                        break;

                    //Op��o inv�lida
                    default:
                        printf("\nChoose a valid option!\n\n");
                        break;
                }

                if (is_empty(patricia_trie)){
                    printf("\nInsert an element before removing one!\n");
                    break;
                }

            }while(number_menu!=0);    

    // Interface em PT-BR
        case 2:
            printf("\n\tBem-vindo a interface de Patricia Trie\n\n");
            system("pause");
            system("cls");

            do{
                number_menu = 0;
            } while (number_menu != 0);

            break;
    }

    return 0;
}
