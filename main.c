#include <stdio.h>
#include <stdlib.h>

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

int main() {

    FILE *file; 
    file = fopen("contatos.txt", "r");
    openFile(file);
    
    List *lista=  createList();
    printf("%d\n", lista -> size);

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
            printf("%s", arr);
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
