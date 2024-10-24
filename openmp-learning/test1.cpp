#include <iostream>
#include <omp.h>
#include <fstream>

using namespace std;

void func_task(int n) {
    // some task
    cout << n << endl;
}

int main() {
    omp_set_num_threads(4); // set num of threads
    int n = omp_get_num_threads(); // get num of threads
    cout << "Number of threads = " << n << endl;

    #pragma omp parallel // creates multiple threads to exec code blocks concurrently; parallelize at block level
    {
        cout << "Hello  " << omp_get_thread_num() << endl;
    }

    int sum = 0;

    #pragma omp parallel for // distributes loop iterations among threads
    for (int i = 0; i < 100; i++) { // ensures that only one threads execs a block at a time
        #pragma omp critical
        {
            sum += i;
        }
    }

    sum = 0;
    #pragma omp parallel for
    for (int i = 0; i < 100; i++) {
        #pragma omp atomic // atomic access to var
        sum += i;
    }

    sum = 0;
    #pragma omp parallel for reduction(+:sum) // sombines res for all threads usign a reduction operator (+, -, *, etc.)
    for (int i = 0; i < 100; i++) {
        sum += 1;
    }

    #pragma omp parallel
    {
        #pragma omp for nowait // removes the implicit barrier at the end of the for loop, allowing threads to continue without waiting for others to finish
        for (int i = 0; i < 10; i++) {
            cout << "Task" << endl;
        }

        cout << omp_get_thread_num() << endl;
    }

    #pragma omp parallel for schedule(static, 4) // divides iterations of loop among threads; strategies are static, dynamic, and guided
    for (int i = 0; i < 16; i++) {
        cout << "Hello" << endl;
    }

    #pragma omp parallel sections
    {
        #pragma omp section // divides tasks among threads where wach task execs only once
        cout << "Task 1" << endl;

        #pragma omp section
        cout << "Task 2" << endl;
    }

    #pragma omp parallel
    {
        #pragma omp single // ensures that block of code only runs once by a single thread
        cout << "Executed only once" << endl;
    }

    #pragma omp parallel
    {
        #pragma omp master // code block only exec by master thread
        cout << "Master thread" << endl;
    }

    #pragma omp parallel
    {
        cout << "Before barrier" << endl;
        #pragma omp barrier // sync threads, ensures that all threads reach a point before continuing
        cout << "After barrier" << endl;
    }

    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task // defines independent tasks that can run in parallel
            func_task(1);

            #pragma omp task
            func_task(2);
        }
    }

    double start = omp_get_wtime(); // returns the time
    double duration = omp_get_wtime() - start;
    cout << "Duration = " << duration << endl;

    ofstream outfile("data1.dat");
    outfile << "Serial" << "\t" << "Time" << "\t" << "Dummy" << endl;
    outfile << 1 << "\t" << duration << "\t" << 1 << endl;
    outfile << 2 << "\t" << duration * 2 << "\t" << 2 << endl;
    outfile.close();

    return 0;
}