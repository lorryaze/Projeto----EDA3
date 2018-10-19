#include <stdio.h>
#include <stdlib.h>

int mostrarMenu();
void openFile(FILE *);

//tipo de dado
typedef struct contato{
    char nome[101];
    char celular[11];
    char endereco[101];
    unsigned int cep;
    char data[11];
} Contato;

//elementos da lista
typedef struct  elemento{
	Contato dados;	
	struct elemento *antes;
	struct elemento *depois;
} Elemento;

typedef struct elemento *Lista;
//estrutura de controle
/*typedef struct node{
	Elemento *inicio; //ponteiro p o primero elemento da lista
	Elemento *fim;	//ponteiro p o ultimo elemento da lista
	int tamanho;
}Node; */

Lista *criaLista();
void liberaLista(Lista *);
int main(int argc, char *argv[]) {

    FILE *file; 
    file = fopen("contatos.txt", "r");
    openFile(file);
    
    Lista *li;
    li = criaLista();
    liberaLista(li);
	        
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

Lista *criaLista(){
	Lista *li = (Lista*) malloc(sizeof(Lista));
	if(li != NULL){
		*li = NULL;
	}
	return li;
}
void liberaLista(Lista *li){
	if(li != NULL){
		Elemento *no;
		while((*li) != NULL) {
			no = *li;
			*li = (*li) -> depois;
			free(no);
		}
		free(li);
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
