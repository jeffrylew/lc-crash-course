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
