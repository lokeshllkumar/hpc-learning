#include <iostream>
#include <omp.h>

using namespace std;

int sumOfNaturalNumbers(int n) {
    if (n <= 1)
        return n;

    int sum = 0;

    #pragma omp task shared(sum)
    sum = n + sumOfNaturalNumbers(n - 1);

    return sum;
}

int main() {
    int n = 10;

    if (n < 0) {
        cout << "Please enter a non-negative integer." << endl;
    } else {
        int result = sumOfNaturalNumbers(n);
        cout << "The sum of the first " << n << " natural numbers is: " << result << endl;
    }

    return 0;
}
