#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Function to take user input for board size (N)
int getUserInput() {
    int n;
    cout << "Enter the number of queens (N): ";
    cin >> n;
    return n;
}

// Function to print the solution board
void printSolution(vector<int> &board, int N) {
    cout << "\nSolution:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                cout << " Q ";
            else
                cout << " . ";
        }
        cout << endl;
    }
}

// Function to check if a queen can be placed at position (row, col)
bool isSafe(vector<int> &board, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return false;  // Conflicts in same column or diagonals
    }
    return true;
}

// Backtracking function to solve N-Queens
bool solveNQueensBacktracking(vector<int> &board, int row, int N) {
    if (row == N) {
        printSolution(board, N);
        return true;
    }
    bool foundSolution = false;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            foundSolution = solveNQueensBacktracking(board, row + 1, N) || foundSolution;
            board[row] = -1;  // Backtrack
        }
    }
    return foundSolution;
}

// Branch and Bound function (optimized solution)
bool solveNQueensBranchAndBound(int row, int N, vector<int> &board, vector<bool> &colUsed, vector<bool> &diag1, vector<bool> &diag2) {
    if (row == N) {
        printSolution(board, N);
        return true;
    }
    bool foundSolution = false;
    for (int col = 0; col < N; col++) {
        if (!colUsed[col] && !diag1[row - col + N - 1] && !diag2[row + col]) {
            board[row] = col;
            colUsed[col] = diag1[row - col + N - 1] = diag2[row + col] = true;

            foundSolution = solveNQueensBranchAndBound(row + 1, N, board, colUsed, diag1, diag2) || foundSolution;

            colUsed[col] = diag1[row - col + N - 1] = diag2[row + col] = false;  // Backtrack
        }
    }
    return foundSolution;
}

// Main function
int main() {
    int N = getUserInput();
    
    cout << "\nSolving using Backtracking:\n";
    vector<int> board(N, -1);
    if (!solveNQueensBacktracking(board, 0, N))
        cout << "No solution found using Backtracking.\n";

    cout << "\nSolving using Branch and Bound:\n";
    vector<bool> colUsed(N, false), diag1(2 * N - 1, false), diag2(2 * N - 1, false);
    if (!solveNQueensBranchAndBound(0, N, board, colUsed, diag1, diag2))
        cout << "No solution found using Branch and Bound.\n";

    return 0;
}
