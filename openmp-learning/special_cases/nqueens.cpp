#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Function to print the board
void printBoard(const vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

// Check if a queen can be placed on board[row][col]
bool isSafe(const vector<vector<int>>& board, int row, int col, int N) {
    bool flag = false;
    // Check column
    #pragma omp parallel for
    for (int i = 0; i < row; ++i) {
        if (board[i][col]) {
            #pragma omp critical
            flag = true;
        }
    }
    #pragma omp barrier
    
    if (flag) return false;

    // Check upper-left diagonal
    flag = false;
    #pragma omp parallel for collapse(2)
    for (int i = row; i >= 0; --i) {
        for (int j = col; j >=0; --j) {
            if (board[i][col]) {
                #pragma omp critical
                flag = true;
            }
        }
    }
    #pragma omp barrier
    
    if (flag) return false;

    // Check upper-right diagonal
    flag = false;
    #pragma omp parallel for collapse(2)
    for (int i = row; i >= 0; --i) {
        for (int j = col; j < N; j++) {
            if (board[i][col]) {
                #pragma omp critical
                flag = true;
            }
        }
    }
    #pragma omp barrier

    if (flag) return false;

    return true;
}


// Recursive function to solve the N-Queens problem
bool solveNQueens(vector<vector<int>>& board, int row, int N) {
    if (row == N) { // All queens are placed
        printBoard(board, N);
        return true;
    }

    bool success = false;
    for (int col = 0; col < N; ++col) {
        {
            if (isSafe(board, row, col, N)) {
                board[row][col] = 1; // Place the queen
                success = solveNQueens(board, row + 1, N) || success; // Continue to place next queen
                board[row][col] = 0; // Backtrack
            }
        }
    }
    return success;
}

int main() {
    int N = 5;

    vector<vector<int>> board(N, vector<int>(N, 0));

    if (!solveNQueens(board, 0, N)) {
        cout << "No solution exists for N = " << N << endl;
    }

    return 0;
}