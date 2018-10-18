#include <stdio.h>

void openFile(FILE *file);

int main() {
    
    FILE *file; 
    file = fopen("contatos.txt", "r");
    openFile(file);

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
}
