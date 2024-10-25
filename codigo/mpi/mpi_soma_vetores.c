#include <mpi.h>
#include <stdio.h>

#define VECTOR_SIZE 100

int main(int argc, char* argv[]) {
    int rank, size;

    // Inicializa o vetor1 no processo mestre
    int vector1[VECTOR_SIZE] = {
    387,787,690,463,315,331,632,443,748,638,
    697,649,308,438,272,865,981,821,258,210,
    523,566,781,367,875,596,322,521,514,401,
    322,487,562,557,301,344,228,892,496,169,
    985,960,114,458,599,249,916,285,799,138,
    979,547,501,326,107,616,214,168,100,784,
    456,176,820,306,483,343,742,499,847,553,
    233,973,633,470,495,910,606,446,274,779,
    506,867,800,633,201,525,825,846,689,355,
    578,927,111,331,416,292,903,312,429,680};

    printf("\nConteúdo de Vector 1 \n");
    for (int i = 0; i < VECTOR_SIZE; i++)
    {
        printf("Pos[%d] = %d | ", i, vector1[i]);
    }

    // Inicializa o vetor2 no processo mestre
    int vector2[VECTOR_SIZE] = {
    320,490,191,580,187,474,441,131,735,371,
    385,427,545,589,977,874,595,331,311,705,
    937,738,215,330,427,314,394,507,960,348,
    107,889,930,987,676,174,830,891,690,351,
    169,130,239,505,742,534,967,682,464,110,
    114,437,908,899,853,273,155,231,413,841,
    443,665,816,828,111,425,357,602,810,220,
    684,231,339,631,655,840,113,696,183,740,
    531,555,994,240,523,599,167,766,158,118,
    410,947,436,369,765,565,622,126,646,185};

    printf("\nConteúdo de Vector 2 \n");
    for (int i = 0; i < VECTOR_SIZE; i++)
    {
        printf("Pos[%d] = %d | ", i, vector2[i]);
    }

    printf("\n----------------------------------------");

    int partial_sum = 0; 
    int total_sum = 0;
    int chunk_size;
    
    MPI_Init(&argc, &argv);  // Inicializa MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Identifica o rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Obtém o número total de processos

    chunk_size = VECTOR_SIZE / size;  // Tamanho de cada parte do vetor

    int sub_vector1[chunk_size];
    int sub_vector2[chunk_size];

    // Divide os vetores entre os processos
    MPI_Scatter(vector1, chunk_size, MPI_INT, sub_vector1, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(vector2, chunk_size, MPI_INT, sub_vector2, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada processo calcula a soma parcial de seu subvetor
    printf("\n----- Cada processo calcula a soma parcial de seu subvetor -----");
    printf("\nSoma Parcial += sub_vector1[i] + sub_vector2[i]");
    for (int i = 0; i < chunk_size; i++) {
        partial_sum += sub_vector1[i] + sub_vector2[i];        
        printf("\nValor em sub_vector[1] = %d", sub_vector1[i]);
        printf("\nValor em sub_vector[2] = %d", sub_vector2[i]);
        printf("\nSoma Parcial += %d", partial_sum);
    }
    printf("\n----------------------------------------");

    // Reúne as somas parciais no processo mestre
    MPI_Gather(&partial_sum, 1, MPI_INT, &total_sum, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // O processo mestre calcula a soma total
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            total_sum += total_sum;
        }
        printf("\nSoma total: %d\n", total_sum);
    }

    MPI_Finalize();  // Finaliza MPI
    return 0;
}