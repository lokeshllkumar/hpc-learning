#include <iostream>
using namespace std;

int factorial(int n) {
    if (n <= 1)
        return 1;
    long long res = 1;
    #pragma omp task shared(res)
    {
        res = n * factorial(n - 1);
    }

    return res;
}

int main() {
    int number = 5;

    if (number < 0) {
        cout << "Factorial is not defined for negative numbers." << endl;
    } else {
        int result = factorial(number);
        cout << "Factorial of " << number << " is: " << result << endl;
    }

    return 0;
}
