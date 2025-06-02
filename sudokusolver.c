#include <stdio.h>

int puzzle[9][9];

void print_puzzle(int puzzle[9][9]);
int valid_puzzle(int puzzle[9][9], int row, int col, int val);
int solve_puzzle(int puzzle[9][9], int row, int col);
void input_puzzle(int puzzle[9][9]);

int main() {
    printf("\n\tWELCOME TO SUDOKU SOLVER!");
    input_puzzle(puzzle);

    printf("\n Original Puzzle:");
    print_puzzle(puzzle);

    if (solve_puzzle(puzzle, 0, 0)) {
        printf("\n The puzzle is solved:");
        print_puzzle(puzzle);
    } else {
        printf("\n This puzzle is not solvable.\n");
    }

    return 0;
}

void input_puzzle(int puzzle[9][9]) {
    printf("\nEnter the Sudoku puzzle row by row.\nUse 0 for empty cells.\n");

    for (int row = 0; row < 9; row++) {
        printf("Enter 9 numbers for row %d (separated by space):\n", row + 1);
        for (int col = 0; col < 9; col++) {
            int num;
            scanf("%d", &num);
            if (num < 0 || num > 9) {
                printf("Invalid input! Please enter numbers between 0 and 9.\n");
                col--; // Retry this cell
            } else {
                puzzle[row][col] = num;
            }
        }
    }
}

int solve_puzzle(int puzzle[9][9], int row, int col) {
    if (col == 9 && row == 8)
        return 1;

    if (col == 9) {
        row++;
        col = 0;
    }

    if (puzzle[row][col] != 0)
        return solve_puzzle(puzzle, row, col + 1);

    for (int i = 1; i <= 9; i++) {
        if (valid_puzzle(puzzle, row, col, i)) {
            puzzle[row][col] = i;
            if (solve_puzzle(puzzle, row, col + 1))
                return 1;
            puzzle[row][col] = 0;
        }
    }

    return 0;
}

int valid_puzzle(int puzzle[9][9], int row, int col, int val) {
    for (int i = 0; i < 9; i++) {
        if (puzzle[row][i] == val || puzzle[i][col] == val)
            return 0;
    }

    int r = row - row % 3;
    int c = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle[r + i][c + j] == val)
                return 0;
        }
    }

    return 1;
}

void print_puzzle(int puzzle[9][9]) {
    printf("\n\n+-------+-------+-------+");
    for (int row = 0; row < 9; row++) {
        if (row % 3 == 0 && row != 0)
            printf("\n|-------+-------+-------|");

        printf("\n| ");
        for (int col = 0; col < 9; col++) {
            if (col % 3 == 0 && col != 0)
                printf("| ");
            if (puzzle[row][col] != 0)
                printf("%d ", puzzle[row][col]);
            else
                printf("  ");
        }
        printf("|");
    }
    printf("\n+-------+-------+-------+\n");
}

