#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int qntdElemetos;
	Lista *head; //ponteiro p o primero elemento da lista
	Lista *tail; //ponteiro p o ultimo elemento da lista
} Header;

int mostrarMenu();
Header *inicializaHeader();
void liberaLista(Lista *);
Contato *criaRegistro();
char *validaData(char data[]);
char *validaCelular(char celular[]);
void insereRegistro(Header *header, Contato *contato);
void insertionSort(Header *header, Contato *contato);
void procuraContato(Header *header, char *nome);
Contato *insereArquivo(FILE *arquivo,Header *header);
void listaContatos(Header *header);
void removeContato(Header *header, char *nome); 

int main(int argc, char *argv[]) {
    FILE *file;
    file = fopen("contatos.txt", "r");
    Header *header = inicializaHeader();
    insereArquivo(file,header);

    //liberaLista(li);
	        
    int opcao = 0;
    while(opcao != 5){
        opcao = mostrarMenu();
        switch(opcao){
            case 1:
                insereRegistro(header, criaRegistro());
                break;
            
            case 2: //chamar função de remover registro
                getchar();
                printf("\nDigite o nome que deseja retirar:");
                char nomeRem[101];
                gets(nomeRem);
                removeContato(header,nomeRem);
                break;

            case 3: //chamar função de pesquisar registro
                getchar();
                printf("\nDigite o nome que deseja pesquisar:");
                char nome[101];
                gets(nome);
                procuraContato(header, nome);
                break;

            case 4: // chamar função de listar todos os registros
                listaContatos(header);
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


Header *inicializaHeader() {
	Header *header = (Header*) malloc(sizeof(Header));
    header->qntdElemetos=0;
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
    header->qntdElemetos++;

    if(header->head == NULL) {
        header->head = novoElemento;
        header->tail = novoElemento;
        novoElemento->prox = NULL;
        novoElemento->anterior = NULL;
    }
    else {
       // insertionSort(header,contato);
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


void procuraContato(Header *header, char *nome){
    int i = 1;
    for(Lista *aux = header->head; aux != NULL; aux=aux->prox){
        Contato *nomeNaLista = (Contato *)aux->contato;

        if (strstr(nomeNaLista, nome) != NULL){
           printf("\nitem %d: \n",i);
            printf("nome: %s\n",nomeNaLista->nome);
            printf("celular: %s\n",nomeNaLista->celular);
            printf("endereco: %s\n",nomeNaLista->endereco);
            printf("cep: %d\n",nomeNaLista->cep);
            printf("data: %s\n",nomeNaLista->data);
            i++;
        }
    }
}

void removeContato(Header *header, char *nome){
    int i =0;
     for(Lista *aux = header->head; aux != NULL; aux = aux->prox) {
        Contato *nomeNaLista = (Contato *)aux->contato;
        if (strstr(nomeNaLista, nome) != NULL){
            printf("%d\n", header->qntdElemetos);
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
                aux = NULL; 
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
    if (i ==1){
        header->head->prox->anterior = NULL;
        header->head = header->head->prox;
    }   
}

Contato *insereArquivo(FILE *arquivo,Header *header){
    
    if(arquivo == NULL){
        FILE *arquivo;
        char contato[] = "contatos.txt";
        printf("\nArquivo não encontrado");
        arquivo = fopen(contato, "w");
        printf("\narquivo criado");
    }
    else{
        char arr[100];
        do{
            char nome[101], celular[11];
            char endereco[101], data[11];
            char cep[6];
            if(fgets(nome, 200, arquivo) == NULL){
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
            }
        }while(fgets(arr, 100, arquivo)!= NULL);
    }
}

void listaContatos(Header *header){
    int i = 1;
   for(Lista *aux = header->head; aux != NULL; aux = aux->prox) {
        Contato *nomeNaLista = (Contato *)aux->contato;
        printf("\nitem %d: \n",i);
        printf("nome: %s\n",nomeNaLista->nome);
        printf("celular: %s\n",nomeNaLista->celular);
        printf("endereco: %s\n",nomeNaLista->endereco);
        printf("cep: %d\n",nomeNaLista->cep);
        printf("data: %s\n",nomeNaLista->data);
        i++;
    }
}