class Solution
{
    private int size;

    private int backtrack(int row, int diagonals, int antiDiagonals, int cols)
    {
        // Base case: N queens have been placed
        if (row == size)
        {
            return 1;
        }

        int num_solutions = 0;
        for (int col = 0; col < size; col++)
        {
            // Bit masks. Add size to avoid negative bit shifting
            int currDiagonal = 1 << (row - col + size);
            int currAntiDiagonal = 1 << (row + col);
            int currCol = 1 << col;

            // If the queen is not placeable. Check if bits are set
            if ((cols & currCol) != 0
                || (diagonals & currDiagonal) != 0
                || (antiDiagonals & currAntiDiagonal) != 0)
            {
                continue;
            }

            // "Add" the queen to the board
            cols ^= currCol;
            diagonals ^= currDiagonal;
            antiDiagonals ^= currAntiDiagonal;

            // Move onto the next row with the updated board state
            num_solutions += backtrack(row + 1, diagonals, antiDiagonals, cols);

            // "Remove" the queen from the board since we have already
            // explored all valid paths using the above function call
            cols ^= currCol;
            diagonals ^= currDiagonal;
            antiDiagonals ^= currAntiDiagonal;
        }

        return num_solutions;
    }

    public int totalNQueens(int n)
    {
        size = n;
        return backtrack(0, 0, 0, 0);
    }
}