#include <iostream>
#include <omp.h> 

using namespace std;

void Hello(int my_id, int total_threads) {
    cout << "Hi from Thread " << my_id << " of " << total_threads << endl;
}

int main() {
    omp_set_num_threads(8);
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();
        Hello(id, nt);
    }
    
    return 0;
}
