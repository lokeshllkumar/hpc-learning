#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    int maxI = 10;
    int maxJ = 10;
    int target = 25; // Target sum to find
    bool found = false;

    double start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic, 2) collapse(2)
    for (int i = 0; i < maxI; ++i) {
        for (int j = 0; j < maxJ; ++j) {

            // Condition to stop: find the first pair where the sum is equal to target
            if (i * j == target && found == false) {
                #pragma omp critical
                {
                    cout << "Found target pair (" << i << ", " << j << ") with product " << target << endl;
                    found = true;
                }
            }
        }
    }
    #pragma omp barrier

    double duration = omp_get_wtime() - start;

    cout << duration << endl;

    if (!found) {
        cout << "No pair found with product equal to " << target << endl;
    }

    return 0;
}
