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
	void *contato;	
	struct lista *anterior;
	struct lista *prox;
} Lista;

// cabeçalho
typedef struct header{
	Lista *head; //ponteiro p o primero elemento da lista
	Lista *tail; //ponteiro p o ultimo elemento da lista
    int qntdElemetos;
} Header;

Header *inicializaHeader();
void liberaLista(Lista *);
Contato *criaRegistro();
char *validaData(char data[]);
char *validaCelular(char celular[]);
void insereRegistro(Header *header, Contato *contato);
void insertionSort(Header *header);
void visualizarRegistro(Header *header);
void registraNoArquivo(Header *header);

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
                printf("Registro criado com sucesso ! (Qntd de contato = %d\n)", header->qntdElemetos);
                break;
            
            case 2: //chamar função de remover registro
                break;

            case 3:
                insertionSort(header);
                break;

            case 4:
                insertionSort(header);
                visualizarRegistro(header);
                break;

            case 5:
                registraNoArquivo(header);
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
    header->qntdElemetos = 0;
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
    header->qntdElemetos++;

    if(header->head == NULL) {
        header->head = novoElemento;
        header->tail = novoElemento;
        novoElemento->prox = NULL;
        novoElemento->anterior = NULL;
    }
    else {
        novoElemento->prox = NULL;
        novoElemento->anterior = header->tail;
        header->tail->prox = novoElemento;
        header->tail = novoElemento;
        header->qntdElemetos++;
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
void insertionSort(Header *header) { 
/*     Lista *i, *j, *altera;
    
    for(i = header->head->prox; i != NULL; i = i->prox) {
        Contato *escolhido = (Contato *)i->contato;
        Contato *ordenado = (Contato *)j->contato;

        altera = j->prox;
        Contato *alteraContato = (Contato *)j->contato;
        j = i->anterior;
        
        while( (j != NULL) && (strcmp(ordenado->nome,escolhido->nome) >= 0)) {
            strcpy(alteraContato->nome,ordenado->nome);
            strcpy(alteraContato->celular,ordenado->celular);
            strcpy(alteraContato->endereco,ordenado->endereco);
            alteraContato->cep = ordenado->cep;
            strcpy(alteraContato->data,ordenado->data);
            j = j->anterior;
        }

        strcpy(alteraContato->nome,escolhido->nome);
        strcpy(alteraContato->celular,escolhido->celular);
        strcpy(alteraContato->endereco,escolhido->endereco);
        alteraContato->cep = escolhido->cep;
        strcpy(alteraContato->data,escolhido->data);
    } */
}
void visualizarRegistro(Header *header) {
    Lista *aux;
    
    printf("---------------------------------- \n");
    printf("          Lista de Contatos        \n");    
    printf("----------------------------------\n");
    
    for(aux = header->head; aux != NULL; aux = aux->prox) {
        Contato *contato = (Contato *)aux->contato;
        printf("Nome: %s\n", contato->nome);
        printf("Celular: %s\n", contato->celular);
        printf("Endereco: %s\n", contato->endereco);
        printf("CEP: %d\n", contato->cep);
        printf("Data: %s\n\n", contato->data);

    }
}

void registraNoArquivo(Header *header) {
    Lista *aux;
    FILE *agenda = fopen("contatos.txt", "a");

    if(agenda == NULL) {
        printf("Erro. Alteracoes não foram salvas!");
        exit(1);
    }
    
    for(aux = header->head; aux != NULL; aux = aux->prox) {
        Contato *contato = (Contato *)aux->contato;
        fprintf(agenda, "%s\n", contato->nome);
        fprintf(agenda, "%s\n", contato->celular);
        fprintf(agenda, "%s\n", contato->endereco);
        fprintf(agenda, "%d\n", contato->cep);
        fprintf(agenda, "%s\n", contato->data);
        fprintf(agenda, "$\n");

    }
    fprintf(agenda, "\n");
}