/**
 * @param {character[][]} board
 * @param {string} word
 * @returns {boolean}
 */
var exist = function(board, word) {
    const valid = (row, col) => {
        return 0 <= row && row < nrows && 0 <= col && col < ncols;
    }

    const backtrack = (row, col, i, seen) => {
        if (i == word.length)
        {
            return true;
        }

        for (const [dcol, drow] of directions)
        {
            const nextRow = row + drow;
            const nextCol = col + dcol;

            if (valid(nextRow, nextCol) && !seen[nextRow][nextCol])
            {
                if (board[nextRow][nextCol] == word[i])
                {
                    seen[nextRow][nextCol] = true;

                    if (backtrack(nextRow, nextCol, i + 1, seen))
                    {
                        return true;
                    }

                    seen[nextRow][nextCol] = false;
                }
            }
        }

        return false;
    }

    const directions = [[0, 1], [1, 0], [0, -1], [-1, 0]];
    const nrows = board.length;
    const ncols = board[0].length;

    for (let row = 0; row < nrows; row++)
    {
        for (let col = 0; col < ncols; col++)
        {
            let seen = [];
            for (let i = 0; i < nrows; i++)
            {
                seen.push(new Array(ncols).fill(false));
            }

            seen[row][col] = true;
            if (board[row][col] == word[0] && backtrack(row, col, 1, seen))
            {
                return true;
            }
        }
    }

    return false;
};
