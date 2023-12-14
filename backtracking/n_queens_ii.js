/**
 * @param {number} n
 * @returns {number}
 */
var totalNQueens = function(n) {
    const backtrack = (row, diagonals, antiDiagonals, cols) => {
        // Base case - N queens have been placed
        if (row == n)
        {
            return 1;
        }

        let solutions = 0;
        for (let col = 0; col < n; col++)
        {
            const currDiagonal = row - col;
            const currAntiDiagonal = row + col;

            //! If the queen is not placeable
            if (cols.has(col)
                || diagonals.has(currDiagonal)
                || antiDiagonals.has(currAntiDiagonal))
            {
                continue;
            }

            // "Add" the queen to the board
            cols.add(col);
            diagonals.add(currDiagonal);
            antiDiagonals.add(currAntiDiagonal);

            // Move onto the next row with the updated board state
            solutions += backtrack(row + 1, diagonals, antiDiagonals, cols);

            // "Remove" the queen from the board since we have already
            // explored all valid paths using the above function call
            cols.delete(col);
            diagonals.delete(currDiagonal);
            antiDiagonals.delete(currAntiDiagonal);
        }

        return solutions;
    };

    return backtrack(0, new Set(), new Set(), new Set());
};
