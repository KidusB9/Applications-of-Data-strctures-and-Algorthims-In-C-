#include <iostream>
#include <vector>

using namespace std;

const int N = 8;

vector<vector<int>> board(N, vector<int>(N, 0));

bool isSafe(int row, int col) {
    // check the same row to the left
    for (int i = 0; i < col; i++) {
        if (board[row][i]) {
            return false;
        }
    }

    // check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    // check lower diagonal on left side
    for (int i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

bool solveNQueens(int col) {
    if (col == N) {
        return true;
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;

            if (solveNQueens(col + 1)) {
                return true;
            }

            board[i][col] = 0;
        }
    }

    return false;
}

int main() {
    if (solveNQueens(0)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No solution exists" << endl;
    }
    return 0;
}
