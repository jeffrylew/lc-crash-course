/**
 * @param {number[][]} grid
 * @return {number}
 */
var maxAreaOfIslandDFSRecursive = function(grid) {
    const dfs = (row, col, grid, seen) => {
        if (row < 0
            || row >= grid.length
            || col < 0
            || col >= grid[0].length
            || seen[row][col]
            || grid[row][col] == 0)
        {
            return 0;
        }

        seen[row][col] = true;

        return 1
            + dfs(row - 1, col, grid, seen)
            + dfs(row + 1, col, grid, seen)
            + dfs(row, col - 1, grid, seen)
            + dfs(row, col + 1, grid, seen);
    }

    let seen = new Array(grid.length);
    for (let row = 0; row < grid.length; row++)
    {
        seen[row] = new Array(grid[0].length).fill(false);
    }

    let ans = 0;

    for (let row = 0; row < grid.length; row++)
    {
        for (let col = 0; col < grid[0].length; col++)
        {
            ans = Math.max(ans, dfs(row, col, grid, seen));
        }
    }

    return ans;
};