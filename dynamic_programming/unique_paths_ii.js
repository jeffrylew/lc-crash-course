/**
 * @param {number[][]} obstacleGrid
 * @return {number}
 */
var uniquePathsWithObstaclesDS = function(obstacleGrid) {
    // If starting cell has an obstacle then return
    // since there are no paths to the destination
    if (obstacleGrid[0][0] == 1)
    {
        return 0;
    }

    const num_rows = obstacleGrid.length;
    const num_cols = obstacleGrid[0].length;

    // Assuming cannot modify input, create a copy
    let grid = [];
    for (let row = 0; row < num_rows; row++)
    {
        grid[row] = obstacleGrid[row].slice();
    }

    // Number of ways of reaching the starting cell is 1
    grid[0][0] = 1;

    // Fill values for first column
    for (let row = 1; row < num_rows; row++)
    {
        grid[row][0] = (grid[row][0] == 0 && grid[row - 1][0] == 1) ? 1 : 0;
    }

    // Fill values for first row
    for (let col = 1; col < num_cols; col++)
    {
        grid[0][col] = (grid[0][col] == 0 && grid[0][col - 1] == 1) ? 1 : 0;
    }

    // Fill values starting from (1, 1)
    // Number of ways of reaching cell[row][col] is
    // cell[row - 1][col] + cell[row][col - 1]
    for (let row = 1; row < num_rows; row++)
    {
        for (let col = 1; col < num_cols; col++)
        {
            if (grid[row][col] == 0)
            {
                grid[row][col] = grid[row - 1][col] + grid[row][col - 1];
            }
            else
            {
                grid[row][col] = 0;
            }
        }
    }

    // Return value stored in bottom right corner
    return grid[num_rows - 1][num_cols - 1];
};
