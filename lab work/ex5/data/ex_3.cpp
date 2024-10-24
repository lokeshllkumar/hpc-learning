#include <iostream>
#include <omp.h>
#include <fstream>

#define N 512

void init_matrix(double matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 1;
        }
    }
}

void multiply_matrix(double A[N][N], double B[N][N], double C[N][N], int op) {
    switch(op) {
        // serial
        case 0:
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k]* B[k][j];
                }
            }
        }
        break;
        
        // static
        case 1:
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k]* B[k][j];
                }
            }
        }
        break;

        //dynamic
        case 2:
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k]* B[k][j];
                }
            }
        }
        break;

        //guided
        case 3:
        #pragma omp parallel for schedule(guided)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = 0;
                for (int k = 0; k < N; k++) {
                    C[i][j] += A[i][k]* B[k][j];
                }
            }
        }
        break;

        default:
        std::cout << "Invalid option!" << std::endl;
        break;
    }
}

int main() {
    std::ofstream outfile("data5_2.dat");


    double A[N][N], B[N][N], C[N][N];

    init_matrix(A);
    init_matrix(B);

    // serial
    double start = omp_get_wtime();
    multiply_matrix(A, B, C, 0);
    double duration = omp_get_wtime() - start;
    outfile << "Serial Code - " << duration << std::endl;


    // static
    start = omp_get_wtime();
    multiply_matrix(A, B, C, 1);
    duration = omp_get_wtime() - start;
    outfile << "Parallel Static Code - " << duration << std::endl;

    // dynamic
    start = omp_get_wtime();
    multiply_matrix(A, B, C, 2);
    duration = omp_get_wtime() - start;
    outfile << "Parallel Dynamic Code - " << duration << std::endl;

    // guided
    start = omp_get_wtime();
    multiply_matrix(A, B, C, 3);
    duration = omp_get_wtime() - start;
    outfile << "Parallel Guided Code - " << duration << std::endl;

    outfile.close();

    return 0;
}