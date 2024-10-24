#include <iostream>
#include <random>
#include <cmath>
#include <omp.h>
#include <fstream>

# define RADIUS 10.0
# define N_SAMPLES 10000

#define NUM_THREADS 8

using namespace std;

float get_rand_num() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(0.0, 1.0);

    return dis(gen);
}

int main()
{
    ofstream outfile("data2_0.dat");
    outfile << "NumOfSamples" << "\t" << "Duration" << "\t" << "PiEstimate" << endl;
    for (size_t j = 1000; j <= N_SAMPLES; j += 1000) {
        float pi_estimated = 0.0;
        size_t inside_circle = 0;
        double start = omp_get_wtime();
        for (size_t i = 0; i < j; i++) {
            float x_ = get_rand_num();
            float y_ = get_rand_num();
            if (pow ((x_ * x_ + y_ * y_), 0.5) < RADIUS)
                inside_circle++;
        }
        double duration = omp_get_wtime() - start;
        cout << "Original value of pi is " << M_PI << endl;
        cout << "Number of samples is " << j << endl;
        pi_estimated = 4.0 * (inside_circle / (N_SAMPLES * 1.0));
        cout << "Time to estimate pi is " << duration << " s " << endl;

        outfile << j << "\t\t" << duration << "\t\t\t" << pi_estimated << endl;
    }

    outfile.close();

    // attempt 1
    ofstream outfile1("data2_1.dat");
    outfile1 << "NumOfThreads" << "\t" << "NumOfSamples" << "\t" << "Duration" << endl;
    for (int num_of_threads = 2; num_of_threads < NUM_THREADS; num_of_threads += 2) {
        for (size_t j = 1000; j <= 10000; j += 1000) {
            float pi_estimated = 0.0;
            double start = omp_get_wtime();

            float A[num_of_threads] = {0};

            #pragma omp parallel num_threads(num_of_threads)
            {
                size_t inside_circle = 0;
                int thread_id = omp_get_thread_num();
                size_t samples_per_thread = j / num_of_threads;

                #pragma omp for
                for (size_t i = 0; i < samples_per_thread; i++) {
                    float x_ = get_rand_num();
                    float y_ = get_rand_num();
                    if (pow((x_ * x_ + y_ * y_), 0.5) < (RADIUS)) {
                        inside_circle++;
                    }
                }

                A[thread_id] = 4.0 * (inside_circle / static_cast<float>(samples_per_thread));
            }

            for (int i = 0; i < num_of_threads; i++) {
                pi_estimated += A[i];
            }
            pi_estimated /= num_of_threads;

            double duration = omp_get_wtime() - start;

            outfile1 << num_of_threads << "\t\t" << j << "\t\t" << duration << endl;
        }
    }
    outfile1.close();

    // attempt 2
    ofstream outfile2("data2_2.dat");
    outfile2 << "NumOfThreads" << "\t" << "NumOfSamples" << "\t" << "Duration" << endl;
    for (int num_of_threads = 2; num_of_threads < NUM_THREADS; num_of_threads += 2) {
        for (size_t j = 1000; j <= 10000; j += 1000) {
            float pi_estimated = 0.0;
            double start = omp_get_wtime();

            double A[num_of_threads][4];

            #pragma omp parallel num_threads(num_of_threads)
            {
                size_t inside_circle = 0;
                int thread_id = omp_get_thread_num();
                size_t samples_per_thread = j / num_of_threads;

                #pragma omp for
                for (size_t i = 0; i < samples_per_thread; i++) {
                    float x_ = get_rand_num();
                    float y_ = get_rand_num();
                    if (pow((x_ * x_ + y_ * y_), 0.5) < (RADIUS)) {
                        inside_circle++;
                    }
                }

                A[thread_id][0] = 4.0 * (inside_circle / static_cast<float>(samples_per_thread));
            }

            for (int i = 0; i < num_of_threads; i++) {
                pi_estimated += A[i][0];
            }
            pi_estimated /= num_of_threads;

            double duration = omp_get_wtime() - start;

            outfile2 << num_of_threads << "\t\t" << j << "\t\t" << duration << endl;
        }
    }
    outfile2.close();

    // attempt 3
    ofstream outfile3("data2_3.dat");
    outfile3 << "NumOfThreads" << "\t" << "NumOfSamples" << "\t" << "Duration" << endl;
    for (int num_of_threads = 2; num_of_threads < NUM_THREADS; num_of_threads += 2) {
        for (size_t j = 1000; j <= 10000; j += 1000) {
            float pi_estimated = 0.0;
            double start = omp_get_wtime();

            #pragma omp parallel num_threads(num_of_threads)
            {
                size_t inside_circle = 0;
                int thread_id = omp_get_thread_num();
                size_t samples_per_thread = j / num_of_threads;

                #pragma omp for
                for (size_t i = 0; i < samples_per_thread; i++) {
                    float x_ = get_rand_num();
                    float y_ = get_rand_num();
                    if (pow((x_ * x_ + y_ * y_), 0.5) < (RADIUS)) {
                        inside_circle++;
                    }
                }

                #pragma omp critical 
                {
                    pi_estimated = 4.0 * (inside_circle / static_cast<float>(samples_per_thread));

                }

                #pragma omp barrier
                {
                    if (thread_id == 0) {
                        pi_estimated /= num_of_threads;
                    }
                }
            }

            double duration = omp_get_wtime() - start;

            outfile3 << num_of_threads << "\t\t" << j << "\t\t" << duration << endl;
        }
    }
    outfile3.close();

    // attempt 4
    ofstream outfile4("data2_4.dat");
    outfile4 << "NumOfThreads" << "\t" << "NumOfSamples" << "\t" << "Duration" << endl;
    for (int num_of_threads = 2; num_of_threads < NUM_THREADS; num_of_threads += 2) {
        for (size_t j = 1000; j <= 10000; j += 1000) {
            float pi_estimated = 0.0;
            double start = omp_get_wtime();

            double A[num_of_threads][4];

            #pragma omp parallel num_threads(num_of_threads)
            {
                size_t inside_circle = 0;
                int thread_id = omp_get_thread_num();
                size_t samples_per_thread = j / num_of_threads;

                #pragma omp parallel for
                for (size_t i = 0; i < j; i++) {
                    float x_ = get_rand_num();
                    float y_ = get_rand_num();
                    if (pow((x_ * x_ + y_ * y_), 0.5) < (RADIUS)) {
                        A[i % num_of_threads][0] += 1.0;
                    }
                }

                for (int i = 0; i < num_of_threads; i++)
                {
                    pi_estimated = 4.0 * A[i][0] / (j * 1.0);

                }
            }

            double duration = omp_get_wtime() - start;

            outfile4 << num_of_threads << "\t\t" << j << "\t\t" << duration << endl;
        }
    }
    outfile4.close();

    return 0;
}