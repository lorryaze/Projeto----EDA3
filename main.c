#include <stdio.h>
#include <stdlib.h>

void openFile(FILE *file);
int mostrarMenu();

int main(int argc, char *argv[]) {
    
    FILE *file; 
    file = fopen("contatos.txt", "r");
    openFile(file);

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