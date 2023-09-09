/**
 * @param {number[][]} matrix
 * @param {number} target
 * @returns {boolean}
 */
var searchMatrix = function(matrix, target) {
    const nrows = matrix.length;    // = m
    const ncols = matrix[0].length; // = n

    let left = 0;
    let right = nrows * ncols - 1;

    while (left <= right)
    {
        const mid = Math.floor((left + right) / 2);
        const row = Math.floor(mid / ncols);
        const col = mid % ncols;
        const num = matrix[row][col];

        if (num == target)
        {
            return true;
        }

        if (num < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return false;
};