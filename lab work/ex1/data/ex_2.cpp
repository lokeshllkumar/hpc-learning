#include <iostream>
#include <vector>
#include <chrono>

void method1(const std::vector<std::vector<double>>& A, const std::vector<double>& x, std::vector<double>& b) {
    int N = A.size();
    for (int i = 0; i < N; i++) {
        b[i] = 0;
        for (int j = 0; j < N; j++) {
            b[i] += A[i][j] * x[j];
        }
    }
}

void method2(const std::vector<std::vector<double>>& A, const std::vector<double>& x, std::vector<double>& b) {
    int N = A.size();
    for (int i = 0; i < N; i++) {
        b[i] = 0;
        for (int j = 0; j < N; j++) {
            b[i] += A[j][i] * x[i];
        }
    }
}

int main() {
    const std::vector<int> sizes = {128, 512, 1024, 2048, 4096, 8192};

    std::cout << "N" << "\t" << "Time taken by method 1" << "\t" << "Time taken by method 2" << "\t" << "FLOPs" << std::endl;

    for (int N : sizes) {
        std::vector<std::vector<double>> A(N, std::vector<double>(N));
        std::vector<double> x(N);
        std::vector<double> b1(N, 0);
        std::vector<double> b2(N, 0);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = static_cast<double>(rand()) / RAND_MAX;
            }
            x[i] = static_cast<double>(rand()) / RAND_MAX;
        }

        auto start1 = std::chrono::high_resolution_clock::now();
        method1(A, x, b1);
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration1 = end1 - start1;
        double timeMethod1 = duration1.count();

        auto start2 = std::chrono::high_resolution_clock::now();
        method2(A, x, b2);
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration2 = end2 - start2;
        double timeMethod2 = duration2.count();

        double flops = 2.0 * N * N;

        std::cout << N << "\t" << timeMethod1 << "\t" << timeMethod2 << "\t" << flops << std::endl;
    }

    return 0;
}