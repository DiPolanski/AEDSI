#include <stdio.h>

int main() {
    int X, N;

    scanf("%i %i", &X, &N);

    int qnt_atual = X;
    for (int i = 0; i < N; i++) {
        int M;
        scanf("%i", &M);

        qnt_atual -= M;
        qnt_atual += X;
    }

    printf("%i\n", qnt_atual);
    return 0;
}
