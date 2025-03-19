#include <stdio.h>

int main() {
    int P, D1, D2;
    scanf("%d%d%d", &P, &D1, &D2);

    int soma = D1 + D2;
    int resultado = soma % 2;

    if ((P == 0 && resultado == 0) || (P == 1 && resultado == 1)) {
        printf("0\n"); // Alice ganhou
    } else {
        printf("1\n"); // Bob ganhou
    }

    return 0;
}
