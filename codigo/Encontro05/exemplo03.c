// O que é a sequência de Fibonacci?
//https://brasilescola.uol.com.br/matematica/sequencia-fibonacci.htm

// Para compilar, abra o terminal pelo VS Code e digite:
// gcc -o exemplo03 exemplo03.c -fopenmp
//
// Para executar, digite:
// .\exemplo03.exe

#include <stdio.h>
#include <omp.h>

int fibonacci(int n);

int main()
{
    int num;
    printf("Informe um valor inteiro para calculo de Fibonacci:");
    scanf("%d", &num);
    int res = fibonacci(num);
    printf("\nResultado: %d", res);
}

int fibonacci(int n)
{
    int fib1, fib2, result;
    if (n == 0 || n == 1)
    {
        result = n;
        printf("\nresult - [%d]", result);
    }
    else
    {
        // cria uma tarefa assíncrona
        #pragma omp task shared(fib1)
        fib1 = fibonacci(n - 1);
        printf("\nfib1 - [%d]", fib1);

        // cria uma tarefa assíncrona
        #pragma omp task shared(fib2)
        fib2 = fibonacci(n - 2);
        printf("\nfib2 - [%d]", fib2);

        // espera pelas tarefas assíncronas lançadas
        #pragma omp taskwait
        result = fib1 + fib2;
        printf("\nresult - [%d]", result);
    }
    return result;
}