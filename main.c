#include <stdio.h>
#include <stdlib.h>

int mostrarMenu();
void openFile(FILE *);

typedef struct Contact{
    char name[101];
    char cell[11];
    char address[101];
    unsigned int cep;
    char birth[11];
} contact;

typedef struct node{
    contact data;
    struct node *next;
} Node;

typedef struct list{
    int size;
    Node *head;
} List;

List* createList();

int main(int argc, char *argv[]) {

    FILE *file; 
    file = fopen("contatos.txt", "r");
    openFile(file);
    
    List *lista=  createList();
    printf("%d\n", lista -> size);

    
    int opcao = 0;
    while(opcao != 5){
        opcao = mostrarMenu();
        switch(opcao){
            case 1: //chamar função de inserir novo registro
                break;
            
            case 2: //chamar função de remover registro
                break;

            case 3: //chamar função de pesquisar registro
                break;

            case 4: // chamar função de listar todos os registros
                break;

            case 5: //sai do programa
                break;
            
            default:
                printf("Opção inválida\n");
                break;
        }
    }

    fclose(file);
    return 0;
}

void openFile(FILE *file){
    
    if(file == NULL){
        printf("Arquivo não encontrado!");
    }
    else{
        char arr[100];
        while(fgets(arr, 100, file)!= NULL){
          //  printf("%s", arr);
        }
    }
    printf("\n");
}

List* createList() {
    List *list = (List*) malloc(sizeof(List));

    list -> size = 0;
    list -> head = NULL;

    return list;
}

int mostrarMenu(){
    int opcao = 0;

    printf("---------------------------------- \n");
    printf("          Menu de Opções \n");    
    printf("----------------------------------\n");
    printf("1- Inserir novo registro\n");
    printf("2- Remover registro\n");
    printf("3- Pesquisar registro\n");
    printf("4- Listar todos os registro\n");
    printf("5- Sair\n");
    printf("\nEscolha uma das opções: \n");
    scanf("%d", &opcao);

    return opcao;
}