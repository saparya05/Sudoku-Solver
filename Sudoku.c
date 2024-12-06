#include <stdio.h>
#include <stdbool.h>
#define N 9 // Size of the Sudoku grid
// Function to print the Sudoku grid
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            printf("%2d", grid[row][col]);
        }
        printf("\n");
    }
}
// Function to check if it's safe to place a number in a particular cell
bool isSafe(int grid[N][N], int row, int col, int num)
{
    // Check the row
    for (int x = 0; x < N; x++)
    {
        if (grid[row][x] == num)
        {
            return false;
        }
    }
    // Check the column
    for (int x = 0; x < N; x++)
    {
        if (grid[x][col] == num)
        {
            return false;
        }
    }
    // Check the 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }
    return true;
}
// Function to find an empty cell in the grid
bool findEmptyLocation(int grid[N][N], int *row, int *col)
{
    for (*row = 0; *row < N; (*row)++)
    {
        for (*col = 0; *col < N; (*col)++)
        {
            if (grid[*row][*col] == 0)
            {
                return true;
            }
        }
    }
    return false;
}
// Function to solve the Sudoku grid using backtracking
bool solveSudoku(int grid[N][N])
{
    int row, col;
    // If there is no empty cell left, Sudoku is solved
    if (!findEmptyLocation(grid, &row, &col))
    {
        return true;
    }
    // Try placing numbers from 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        // Check if it is safe to place the number
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
            // Recursively attempt to solve the rest of the grid
            if (solveSudoku(grid))
            {
                return true;
            }
            // Backtrack if placing num didn't lead to a solution
            grid[row][col] = 0;
        }
    }
    // Return false if no solution exists
    return false;
}

// Main function to test the Sudoku solver
int main()
{
    // Example grid with es representing empty cells
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    if (solveSudoku(grid))
    {
        printGrid(grid);
    }
    else
    {
        printf("No solution exists.\n");
    }
    return 0;
}