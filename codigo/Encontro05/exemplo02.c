// Para compilar, abra o terminal pelo VS Code e digite:
// gcc -o exemplo02 exemplo02.c -fopenmp
//
// Para executar, digite:
// .\exemplo02.exe

#include <stdio.h>
#include <omp.h>

#define N 1000 // Tamanho do vetor

int main() {
    int array[N];
    long sum = 0;
    
    // Inicializa o vetor com valores
    for (int i = 0; i < N; ++i) {
        array[i] = 1; // Preenche o vetor com 1s para simplificação
    }

    // Inicia a região paralela
    #pragma omp parallel
    {
        // Variável local para armazenar a soma parcial de cada thread
        long local_sum = 0;

        // Paraleliza o loop
        #pragma omp for
        for (int i = 0; i < N; ++i) {
            local_sum += array[i];
        }

        // Reduz a soma parcial para a soma global
        #pragma omp atomic
        sum += local_sum;

        printf("\nValor global: %d", sum);
        printf("\nValor local: %d", local_sum);
    }

    // Exibe o resultado
    printf("\nSoma dos elementos: %lld", sum);
    printf("\n");

    return 0;
}
