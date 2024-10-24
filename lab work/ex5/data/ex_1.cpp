#include <iostream>
#include <omp.h>
#include <fstream>

unsigned long long factorial_serial(int n) {
    if (n <= 1) {
        return n;
    }

    return n * factorial_serial(n - 1);
}

unsigned long long factorial_parallel(int n) {
    if (n <= 1) {
        return n;
    }

    unsigned long long res = 1;
    #pragma omp parallel shared(res)
    {
        #pragma omp single nowait
        {
            #pragma omp parallel shared(res)
            {
                res = n * factorial_parallel(n - 1);
            }
        }
    }

    #pragma omp taskwait
    return res;

    return n * factorial_serial(n - 1);
}

int main() {
    std::ofstream outfile("data5_0.dat");

    int n;
    std::cout << "Enter a positive number:" << std::endl;
    std::cin >> n;

    double start = omp_get_wtime();
    unsigned long long fact = factorial_serial(n);
    double duration = omp_get_wtime() - start;

    outfile << "Serial Code - " << duration << std::endl;

    start = omp_get_wtime();
    fact = factorial_parallel(n);
    duration = omp_get_wtime() - start;

    outfile << "Parallelized Code - " << duration << std::endl;

    outfile.close();

    return 0;
}