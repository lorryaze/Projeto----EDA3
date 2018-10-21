#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mostrarMenu();
void openFile(FILE *);

//contato
typedef struct contato{
    char nome[101];
    char celular[11];
    char endereco[101];
    unsigned int cep;
    char data[11];
} Contato;

// lista duplamente encadeada
typedef struct lista{
    int qntdElemetos;
	void *contato;	
	struct lista *anterior;
	struct lista *prox;
} Lista;

// cabeçalho
typedef struct header{
	Lista *head; //ponteiro p o primero elemento da lista
	Lista *tail; //ponteiro p o ultimo elemento da lista
} Header;

Header *inicializaHeader();
void liberaLista(Lista *);
Contato *criaRegistro();
char *validaData(char data[]);
char *validaCelular(char celular[]);
void insereRegistro(Header *header, Contato *contato);
void insertionSort(Header *header, Contato *contato);

int main(int argc, char *argv[]) {

    FILE *file; 
    file = fopen("contatos.txt", "r");
    openFile(file);
    
    Header *header = inicializaHeader();

    //liberaLista(li);
	        
    int opcao = 0;
    while(opcao != 5){
        opcao = mostrarMenu();
        switch(opcao){
            case 1:
                insereRegistro(header, criaRegistro());
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

Header *inicializaHeader() {
	Header *header = (Header*) malloc(sizeof(Header));
    header->head = NULL;
    header->tail = NULL;
	return header;
}

/*void liberaLista(Lista *li){
	if(li != NULL){
		Lista *no;
		while((*li) != NULL) {
			no = *li;
			*li = (*li) -> depois;
			free(no);
		}
		free(li);
	}
} */

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

void insereRegistro(Header *header, Contato *contato) {
    Lista *novoElemento = (Lista*) malloc(sizeof(Lista));
    if(novoElemento == NULL) {
        printf("Contato nao pode ser inserido na agenda!\n");
    }
        
    novoElemento->contato = contato;
    novoElemento->qntdElemetos++;

    if(header->head == NULL) {
        header->head = novoElemento;
        header->tail = novoElemento;
        novoElemento->prox = NULL;
        novoElemento->anterior = NULL;
    }
    else {
        insertionSort(header,contato);
/*      novoElemento->prox = NULL;
        novoElemento->anterior = header->tail;
        header->tail->prox = novoElemento;
        header->tail = novoElemento;
        novoElemento->qntdElemetos++; */
    }
}

Contato *criaRegistro() {
    Contato *novoContato;
    char nome[101], celular[11];
    char endereco[101], data[11];
    unsigned int cep;

    novoContato = (Contato*) malloc(sizeof(Contato));
    if(novoContato == NULL) {
        printf("Contato não criado, tente novamente...\n");
    }
    getchar();
    // ler nome e armazena 
    printf("Digite o nome: ");
    gets(nome);
    strcpy(novoContato->nome, nome);

    // ler celular e armazena 
    printf("\nDigte o celular(xxxxx-xxxx): ");
    gets(celular);
    char *correctCelular = validaCelular(celular);
    strcpy(novoContato->celular, correctCelular);

    // ler endereço e armazena 
    printf("\nDigte o endereco: ");
    gets(endereco);
    strcpy(novoContato->endereco, endereco);

    // ler cep e armazena 
    printf("\nDigite o CEP: ");
    scanf("%d", &cep);
    novoContato->cep = cep;

    getchar();
    // ler data e armazena 
    printf("\nDigite a data(dd/mm/aaaa): ");
    gets(data);
    char *correctData = validaData(data);
    strcpy(novoContato->data, correctData);
    
    return novoContato;
}

char *validaData(char data[]) {
/*     while(data[2] != '/' && data[5] != '/') {
        printf("Valor incorreto, formato exigido: dd/mm/aaaa\n");
        printf("\nDigte a data: ");
        gets(data);
    }*/
    return data;
}

char *validaCelular(char celular[]) {
/*     while(celular[5] != '-') {
        printf("Valor incorreto, formato exigido: xxxxx-xxxx\n");
        printf("\nDigte o celular: ");
        gets(celular);
    } */

    return celular;
}
void insertionSort(Header *header, Contato *contato) { 
    for(Lista *aux = header->head; aux != NULL; aux = aux->prox) {
        Contato *nomeNaLista = (Contato *)aux->contato;
        
        if(strcmp(nomeNaLista->nome,contato->nome) > 0) {
        } 
    }

};