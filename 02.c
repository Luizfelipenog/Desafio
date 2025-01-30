#include <stdio.h>

int pertenceFibonacci(int num) {
    int a = 0, b = 1, c;

    if (num == 0 || num == 1) {// O número pertence à sequência
        return 1; 
    }

    while (b <= num) {
        c = a + b;
        a = b;
        b = c;
        
        if (b == num) {// O número pertence à sequência
            return 1; 
        }
    }
    
    return 0; // não pertence à sequência
}

int main() {
    int numero;

    printf("Digite um numero: ");
    scanf("%d", &numero);

    if (pertenceFibonacci(numero)) {
        printf("O numero %d pertence à sequência de Fibonacci.\n", numero);
    } else {
        printf("O numero %d nao pertence à sequência de Fibonacci.\n", numero);
    }

    return 0;
}
