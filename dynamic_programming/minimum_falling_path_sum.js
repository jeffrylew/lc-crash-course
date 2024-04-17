/**
 * @param {number[][]} matrix
 * @return {number}
 */
var minFallingPathSumDS1 = function(matrix) {
    const findMinFallingPathSum = (row, col) => {
        // Check if outside the left or right matrix boundary
        if (col < 0 || col == matrix[0].length)
        {
            return Number.MAX_SAFE_INTEGER;
        }

        // Check if reached last row
        if (row == matrix.length - 1)
        {
            return matrix[row][col];
        }

        // Calculate min falling path sum starting from each possible next step
        const left = findMinFallingPathSum(row + 1, col - 1);
        const middle = findMinFallingPathSum(row + 1, col);
        const right = findMinFallingPathSum(row + 1, col + 1);

        return Math.min(left, middle, right);
    }

    let minFallingSum = Number.MAX_SAFE_INTEGER;
    for (let col = 0; col < matrix[0].length; col++)
    {
        minFallingSum = Math.min(minFallingSum, findMinFallingPathSum(0, col));
    }
    return minFallingSum;
};

/**
 * @param {number[][]} matrix
 * @return {number}
 */
var minFallingPathSumDS2 = function(matrix) {
    const num_rows = matrix.length;
    const num_cols = matrix[0].length;

    let memo = [];
    for (let row = 0; row < num_rows; row++)
    {
        memo.push(new Array(num_cols).fill(Number.MAX_SAFE_INTEGER));
    }

    const findMinFallingPathSum = (row, col) => {
        // Base cases
        if (col < 0 || col == num_cols)
        {
            return Number.MAX_SAFE_INTEGER;
        }

        // Check if reached last row
        if (row == num_rows - 1)
        {
            return matrix[row][col];
        }

        // Check if results were calculated before
        if (memo[row][col] != Number.MAX_SAFE_INTEGER)
        {
            return memo[row][col];
        }

        // Calculate min falling path sum starting from each possible next step
        const left = findMinFallingPathSum(row + 1, col - 1);
        const middle = findMinFallingPathSum(row + 1, col);
        const right = findMinFallingPathSum(row + 1, col + 1);

        memo[row][col] = Math.min(left, middle, right) + matrix[row][col];
        return memo[row][col];
    }

    // Start DFS with memoization from each cell in the top row
    let minFallingSum = Number.MAX_SAFE_INTEGER;
    for (let col = 0; col < num_cols; col++)
    {
        minFallingSum = Math.min(minFallingSum, findMinFallingPathSum(0, col));
    }
    return minFallingSum;
};
