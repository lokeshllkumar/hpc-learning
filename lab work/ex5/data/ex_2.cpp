#include <iostream>
#include <omp.h>
#include <fstream>

long long fib_serial(int n) {
    if (n <= 1) {
        return n;
    }

    return fib_serial(n - 1) + fib_serial(n - 2);
}

long long fib_parallel(int n) {
    if (n <= 1) {
        return n;
    }

    long long x, y;
    #pragma omp task shared(x)
    x = fib_parallel(n - 1);

    #pragma omp task shared(y)
    y = fib_parallel(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    std::ofstream outfile("data5_1.dat");

    int n;
    std::cout << "Enter the position of the Fibonacci number to be printed: " << std::endl;
    std::cin >> n;

    double start = omp_get_wtime();
    long long fib = fib_serial(n);
    double duration = omp_get_wtime() - start;

    outfile << "Serial Code - " << duration << std::endl;

    start = omp_get_wtime();
    fib = fib_parallel(n);
    duration = omp_get_wtime() - start;

    outfile << "Parallelized Code - " << duration << std::endl;

    outfile.close();
}