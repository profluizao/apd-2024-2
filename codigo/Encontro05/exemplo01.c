// Para compilar, abra o terminal pelo VS Code e digite:
// gcc -o exemplo01 exemplo01.c -fopenmp
//
// Para executar, digite:
// .\exemplo01.exe

#include <stdio.h>
#include <omp.h>
int main()
{
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf(" hello(%d) ", ID);
        printf(" world(%d) \n", ID);
    }
}