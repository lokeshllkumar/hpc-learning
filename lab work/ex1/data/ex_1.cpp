#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <vector>

double estimatePi(int numSamples) {
    int pointsInsideCircle = 0;

    for (int i = 0; i < numSamples; i++) {
        double x = static_cast<double>(rand()) / RAND_MAX;
        double y = static_cast<double>(rand()) / RAND_MAX;

        if (x * x + y * y <= 1) {
            pointsInsideCircle++;
        }
    }

    return 4.0 * pointsInsideCircle / numSamples;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    const int maxSamples = 1000000;
    const int step = 10000;

    std::vector<int> sampleSizes;
    std::vector<double> times;
    std::vector<double> errors;
    std::vector<double> pi;

    for (int numSamples = step; numSamples <= maxSamples; numSamples += step) {
        auto start = std::chrono::high_resolution_clock::now();
        double piEstimate = estimatePi(numSamples);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        double timeTaken = duration.count();
        double error = std::abs(M_PI - piEstimate);

        sampleSizes.push_back(numSamples);
        times.push_back(timeTaken);
        errors.push_back(error);
        pi.push_back(piEstimate);
    }

    std::cout << "Samples\tTime\tError\tPi Estimate" << std::endl;
    for (size_t i = 0; i < sampleSizes.size(); ++i) {
        std::cout << sampleSizes[i] << "\t" << times[i] << "\t" << errors[i] << "\t" << pi[i] << std::endl;
    }

    return 0;
}
