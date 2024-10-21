#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);  // Inicializa o ambiente MPI
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Obtém o rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Obtém o número total de processos
    printf("Processo %d de %d\n", rank, size);
    MPI_Finalize();  // Finaliza o ambiente MPI
    return 0;
}