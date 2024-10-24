#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

long long factorialCalc(int n) {
    if (n == 0) {
        return 1;
    }
    long long res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}

float sinApprox(float x, int p) {
    float res = 0.0;
    for (int i = 0; i < p; i++) {
        int exp = 2 * i + 1;
        float term = powf(-1, i) * powf(x, exp) / factorialCalc(exp);
        res += term;
    }
    return res;
}

void findSin(float* inp, float* res, int N, int p) {
    for (int i = 0; i < N; i++) {
        res[i] = sinApprox(inp[i], p);
    }
}

void testTiming(int N, int p) {
    float *x, *res;

    x = (float *)malloc(N * sizeof(float));
    res = (float *)malloc(N * sizeof(float));

    for (int i = 0; i < N; i++) {
        x[i] = (float)i / N;
    }

    clock_t start = clock();
    findSin(x, res, N, p);
    clock_t end = clock();
    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("%d\t%d\t%f\n", N, p, cpu_time);

    free(x);
    free(res);
}

int main() {
    int min_p = 3, max_p = 100;
    int min_N = 1 << 2;
    int max_N = 1 << 15;

    printf("N\tp\tTime\n");

    for (int p = min_p; p <= max_p; p += 10) {
        for (int N = min_N; N <= max_N; N *= 2) {
            testTiming(N, p);
        }
    }

    return 0;
}
