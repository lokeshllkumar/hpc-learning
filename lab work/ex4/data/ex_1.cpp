#include <iostream>
#include <random>
#include <omp.h>
#include <time.h>
#include <chrono>
#include <unistd.h>
#include <fstream>

#define NUM_THREADS 4

using namespace std;

int get_rand_num() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(0, 100);

    return dis(gen);
}

void temp(int time) {
    struct timespec req;
    req.tv_sec = time / 1000;
    req.tv_nsec = (time % 1000) * 1000000;
    nanosleep(&req, nullptr);
}

int main() {
    omp_set_num_threads(NUM_THREADS);

    ofstream outfile("data4_0.dat");

    // static - using i values
    double start = omp_get_wtime();
    #pragma omp parallel for schedule(static, 4)
    for (int i = 1; i <= 100; i++) {
        temp(i);
    }
    double duration = omp_get_wtime() - start;
    outfile << "Static using i values" << " - " << duration << endl; 

    // static - using random values
    start = omp_get_wtime();
    #pragma omp parallel for schedule(static, 4)
    for (int i = 1; i <= 100; i++) {
        int rand = get_rand_num();
        temp(rand);
    }
    duration = omp_get_wtime() - start;
    outfile << "Static using random values" << " - " << duration << endl; 

    // dynamic - using i values
    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, 4)
    for (int i = 1; i <= 100; i++) {
        temp(i);
    }
    duration = omp_get_wtime() - start;
    outfile << "Dynamic using i values" << " - " << duration << endl; 

    // dynamic - using random values
    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, 4)
    for (int i = 1; i <= 100; i++) {
        int rand = get_rand_num();
        temp(rand);
    }
    duration = omp_get_wtime() - start;
    outfile << "Dynamic using random values" << " - " << duration << endl;

    // guided - using i values
    start = omp_get_wtime();
    #pragma omp parallel for schedule(guided, 4)
    for (int i = 1; i <= 100; i++) {
        temp(i);
    }
    duration = omp_get_wtime() - start;
    outfile << "Guided using i values" << " - " << duration << endl; 

    // guided - using random values
    start = omp_get_wtime();
    #pragma omp parallel for schedule(guided, 4)
    for (int i = 1; i <= 100; i++) {
        int rand = get_rand_num();
        temp(rand);
    }
    duration = omp_get_wtime() - start;
    outfile << "Guided using random values" << " - " << duration << endl;

    outfile.close();

    return 0;
}