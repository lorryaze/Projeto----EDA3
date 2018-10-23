#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define true 1
#define false 0

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

int mostrarMenu();
Header *inicializaHeader();
void liberaLista(Lista *);
Contato *criaRegistro();
char *validaData(char data[]);
char *validaCelular(char celular[]);
void insereRegistro(Header *header, Contato *contato);
void procuraContato(Header *header, char *nome);
Contato *insereArquivo(Header *header);
void listaContatos(Header *header);
void removeContato(Header *header, char *nome); 
void insertionSort(Header *header);
void visualizarRegistro(Header *header);
void registraNoArquivo(Header *header);
int stringIsEmpty(char* nome);
int listaVazia(Header *header);
char *nomeToupper(char *nome);
unsigned int validaCep(unsigned int cep);

int main(int argc, char *argv[]) {
    Header *header = inicializaHeader();

    insereArquivo(header);
	        
    int opcao = 0;
    while(opcao != 5){
        opcao = mostrarMenu();
        switch(opcao){
            case 1: 
                insereRegistro(header, criaRegistro());
                printf("Registro criado com sucesso !\n");
                break;
            
            case 2:
                getchar();
                printf("\nDigite o nome que deseja retirar: ");
                char nomeRem[101];
                gets(nomeRem);
                removeContato(header,nomeRem);
                break;

            case 3:
                getchar();
                printf("\nDigite o nome que deseja pesquisar: ");
                char nome[101];
                gets(nome);
                procuraContato(header, nome);
                break;

            case 4:
                insertionSort(header);
                visualizarRegistro(header);

            case 5:
                insertionSort(header);
                registraNoArquivo(header);
                break;
            
            default:
                printf("Opção inválida\n");
                break;
        }
    }
    return 0;
}

Header *inicializaHeader() {
	Header *header = (Header*) malloc(sizeof(Header));
    header->qntdElemetos=0;
    header->head = NULL;
    header->tail = NULL;
    header->qntdElemetos = 0;
	return header;
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
    int cepCorreto = validaCep(cep);
    novoContato->cep = cepCorreto;

    getchar();
    // ler data e armazena 
    printf("\nDigite a data(dd/mm/aaaa): ");
    gets(data);
    char *correctData = validaData(data);
    strcpy(novoContato->data, correctData);
    
    return novoContato;
}

unsigned int validaCep(unsigned int cep){
    int tam = (cep/10000);
    while (tam>9){
        printf("O CPF deve ter apenas 5 números");
        printf("\nDigite o CEP: ");
        scanf("%d", &cep);
        tam = (cep/10000);
    }
    return cep;
}

char *validaData(char data[]) {
    while(data[2] != '/' && data[5] != '/') {
        printf("Valor incorreto, formato exigido: dd/mm/aaaa\n");
        printf("\nDigte a data: ");
        gets(data);
    }
    return data;
}

char *validaCelular(char celular[]) {
    while(celular[5] != '-') {
        printf("Valor incorreto, formato exigido: xxxxx-xxxx\n");
        printf("\nDigte o celular: ");
        gets(celular);
    }

    return celular;
}


void procuraContato(Header *header, char *nome){
    int i = 1;

    if(listaVazia(header)) {
        printf("Lista vazia!\n\n");
        return;
    }

    for(Lista *aux = header->head; aux != NULL; aux=aux->prox){
        Contato *nomeNaLista = (Contato *)aux->contato;

        if (strstr(nomeNaLista->nome, nome) != NULL){
            printf("\nitem %d: \n",i);
            printf("nome: %s\n",nomeNaLista->nome);
            printf("celular: %s\n",nomeNaLista->celular);
            printf("endereco: %s\n",nomeNaLista->endereco);
            printf("cep: %d\n",nomeNaLista->cep);
            printf("data: %s\n",nomeNaLista->data);
            i++;
        }
    }

    if(i == 1) {
        printf("Contato não encontrado!\n");
    }
}

void removeContato(Header *header, char *nome){
    int i =0, contatoEncontrado = 0;

    if(listaVazia(header)) {
        printf("Lista vazia!\n");
        return;
    }
     for(Lista *aux = header->head; aux != NULL; aux = aux->prox) {
        Contato *nomeNaLista = (Contato *)aux->contato;

        if (strstr(nomeNaLista->nome, nome) != NULL){
            contatoEncontrado = 1;
            if(header->qntdElemetos == 1){
                header->head=NULL;
                header->tail=NULL;
                free(aux);
                break;
            }
            else if (aux->anterior==NULL){
                i = 1;
            }
            else if(aux->prox == NULL){
                aux->anterior->prox= NULL;
                header->tail = aux->anterior;
                free(aux);
            }
            else{
                aux->anterior->prox = aux->prox;
                aux->prox->anterior = aux->anterior;
                Lista *temp = aux->anterior;
                free(aux);
                aux= temp;
            }
            header->qntdElemetos--;
        }
    }
    if (i == 1){
        header->head->prox->anterior = NULL;
        header->head = header->head->prox;
    }   
    if(contatoEncontrado == 0) {
        printf("Contato não encontrado\n");
    }
}

Contato *insereArquivo(Header *header){
    FILE *arquivo = fopen("contatos.txt","r");
    
    if(arquivo == NULL){
        printf("\nArquivo não encontrado");
        arquivo = fopen("contatos.txt", "w");
        printf("\nNovo arquivo criado");
    }
    else{
        char arr[100];
        do{
            char nome[101], celular[11];
            char endereco[101], data[11];
            char cep[6];
            fgets(nome, 200, arquivo);
            if(stringIsEmpty(nome)){
                break;
            }
            else{
                fgets(celular, 20, arquivo);
                fgets(endereco, 200, arquivo);
                fgets(cep,50,arquivo);
                fgets(data, 200, arquivo);
                Contato *novoContato = (Contato*) malloc(sizeof(Contato));
                strcpy(novoContato->nome, strtok(nome,"\n"));
                strcpy(novoContato->celular, strtok(celular,"\n"));
                strcpy(novoContato->endereco, strtok(endereco,"\n"));
                novoContato->cep =atoi(cep);
                strcpy(novoContato->data, strtok(data,"\n"));
                insereRegistro(header, novoContato);
                fgets(arr,100,arquivo);
            }
        }while(arr != NULL);
    }
    fclose(arquivo);
}

int stringIsEmpty(char* string) {
    int isEmpty = true;
    
    if(string == NULL) 
        return true;
    if(strlen(string) == 0)
        return true;

    for(int i = 0; i<strlen(string); i++) {
        if(string[i] != ' ' && string[i] != '\n' && string[i] && '\t') {
            isEmpty = false;
        }
    }

    return isEmpty;
}

void insertionSort(Header *header) {
    if(listaVazia(header) == true){
        return;
    }
    for(Lista *i = header->head->prox; i != NULL; i = i->prox) {
        Contato *escolhido = (Contato *)i->contato;
        char nome[101], celular[11], endereco[101], data[11];
        unsigned int cep;
        
        strcpy(nome, escolhido->nome);
        strcpy(celular, escolhido->celular);
        strcpy(endereco, escolhido->endereco);
        strcpy(data, escolhido->data);
        cep = escolhido->cep;


        Lista *j = i->anterior;
        Contato *ordenado = (Contato *)j->contato;

        while( (j != NULL) && (strcasecmp((ordenado->nome), (nome)) >= 0)) {
            Contato *alteraContato = (Contato *)j->prox->contato;

            strcpy(alteraContato->nome, ordenado->nome);
            strcpy(alteraContato->celular, ordenado->celular);
            strcpy(alteraContato->endereco, ordenado->endereco);
            alteraContato->cep = ordenado->cep;
            strcpy(alteraContato->data, ordenado->data);

            j = j->anterior;

            if(j != NULL)
                ordenado = (Contato *) j->contato;
        }

        Contato *alteraContato;

        if(j == NULL)
            alteraContato = (Contato *)header->head->contato;
        else
            alteraContato = (Contato *)j->prox->contato;

        strcpy(alteraContato->nome, nome);
        strcpy(alteraContato->celular, celular);
        strcpy(alteraContato->endereco, endereco);
        alteraContato->cep = cep;
        strcpy(alteraContato->data, data);
    }
}
void visualizarRegistro(Header *header) {
    Lista *aux;
    
    printf("---------------------------------- \n");
    printf("          Lista de Contatos        \n");    
    printf("----------------------------------\n");
    
    if(listaVazia(header)) {
        printf("Lista vazia!\n\n");
        return;
    }

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
    FILE *agenda = fopen("contatos.txt", "w");

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
    fclose(agenda);
}

int listaVazia(Header *header) {
    if(header->head == NULL) {
        return true;
    }
    return false;
}