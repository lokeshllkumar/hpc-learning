#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>
#include <chrono>

using namespace std;

struct CSRMatrix {
    int rows, cols;
    vector<int> row_ptr, col_idx;
    vector<double> vals;
};

CSRMatrix read_mtx(const string &filename) {
    ifstream infile(filename);
    
    CSRMatrix matrix;
    int nz;
    infile >> matrix.rows >> matrix.cols >> nz;

    matrix.row_ptr.resize(matrix.rows + 1);
    matrix.col_idx.resize(nz);
    matrix.vals.resize(nz);

    int row, col;
    double val;

    vector<int> row_count(matrix.rows + 1, 0);

    for (int i = 0; i < nz; i++) {
        infile >> row >> col >> val;
        row--;
        col--;
        matrix.col_idx[i] = col;
        matrix.vals[i] = val;
        row_count[row + 1]++;
    }

    for (int i = 1; i <= matrix.rows; i++) {
        matrix.row_ptr[i] = matrix.row_ptr[i - 1] + row_count[i];
    }

    return matrix;
}

void spmv(const CSRMatrix &matrix, const vector<double> &v, vector<double> &res, int threads) {
    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < matrix.rows; i++) {
        double sum = 0.0;
        for (int j = matrix.row_ptr[i]; j < matrix.row_ptr[i + 1]; j++) {
            sum += matrix.vals[j] * v[matrix.col_idx[j]];
        }
        res[i] = sum;
    }
}

int main() {
    ofstream outfile("data_1_0.dat");
    outfile << "Num of threads" << "\t" << "Time in seconds" << endl; 

    CSRMatrix matrix = read_mtx("1138_bus.mtx");

    vector<double> v(matrix.cols, 1.0);
    vector<double> res(matrix.rows, 0.0);

    vector<int> numThreads = {1, 2, 4, 8};

    for (int i = 0; i < numThreads.size(); i++) {
        double start = omp_get_wtime();
    spmv(matrix, v, res, numThreads[i]);
    double duration = omp_get_wtime() - start;
    outfile << numThreads[i] << "\t" << duration << endl;
    }

    return 0;
}