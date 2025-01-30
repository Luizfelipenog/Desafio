#include <stdio.h>
#include <string.h>

void inverterString(char str[]) {
    int i, j;
    char temp;
    int tamanho = strlen(str);

    
    for (i = 0, j = tamanho - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int main() {
    char string[100]; //tamanho para a string

   
    printf("Digite uma string: ");
    fgets(string, sizeof(string), stdin);

   
    string[strcspn(string, "\n")] = '\0';


    inverterString(string);

 
    printf("invertida: %s\n", string);

    return 0;
}
