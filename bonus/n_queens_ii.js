var totalNQueens = function(n) {
    const backtrack = (row, diagonals, antiDiagonals, cols) => {
        // Base case: N queens have been placed
        if (row == n)
        {
            return 1;
        }

        let num_solutions = 0;
        for (let col = 0; col < n; col++)
        {
            // Add n to avoid negative bit shifting
            const currDiagonal = 1 << (row - col + n);
            const currAntiDiagonal = 1 << (row + col);
            const currCol = 1 << col;

            // If the queen is not placeable
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
            num_solutions +=
                backtrack(row + 1, diagonals, antiDiagonals, cols);

            // "Remove" the queen from the board since we have already
            // explored all valid paths using the above function call
            cols ^= currCol;
            diagonals ^= currDiagonal;
            antiDiagonals ^= currAntiDiagonal;
        }

        return num_solutions;
    }

    return backtrack(0, 0, 0, 0);
};
