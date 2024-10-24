#include <iostream>
#include <vector>
#include <random>
#include <omp.h>
#include <fstream>

// Function to perform 1D convolution
std::vector<double> convolve1D(const std::vector<double>& input, const std::vector<double>& kernel) {
    int input_len = input.size();
    int kernel_len = kernel.size();
    int output_len = input_len + kernel_len - 1;
    std::vector<double> output(output_len, 0.0);

    #pragma omp parallel for
    for (int i = 0; i < output_len; ++i) {
        int start = std::max(0, i - kernel_len + 1);
        int end = std::min(i + 1, input_len);
        for (int j = start; j < end; ++j) {
            output[i] += input[j] * kernel[i - j];
        }
    }
    return output;
}

int main() {
    // Measure execution time
    double start = omp_get_wtime();

    // Define the size of the vector
    int size = 100;

    // Create a vector of doubles
    std::vector<double> input(size);

    // Use a single random number generator to ensure deterministic output
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    // Fill the vector with random numbers
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        input[i] = static_cast<double>(distribution(generator));
    }

    // Define the kernel for convolution
    std::vector<double> kernel = {0.5, 1.0, 0.5};

    // Perform convolution
    std::vector<double> result = convolve1D(input, kernel);

    // Print the result
    for (double value : result) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Measure execution time
    double duration = omp_get_wtime() - start;

    // Output the execution time to a file
    std::ofstream outfile("data4_2.dat");
    outfile << "Parallel Code - " << duration << std::endl;
    outfile.close();

    return 0;
}