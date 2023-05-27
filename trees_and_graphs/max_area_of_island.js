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

/**
 * @param {number[][]} grid
 * @return {number}
 */
var maxAreaOfIslandDFSIterative = function(grid) {
    let seen = new Array(grid.length);
    for (let row = 0; row < grid.length; row++)
    {
        seen[row] = new Array(grid[0].length).fill(false);
    }

    const directions = [[0, 1], [0, -1], [1, 0], [-1, 0]];

    let ans = 0;

    for (let row = 0; row < grid.length; row++)
    {
        for (let col = 0; col < grid[0].length; col++)
        {
            if (seen[row][col] || grid[row][col] == 0)
            {
                continue;
            }

            let curr_area = 0;
            let stack = [[row, col]];
            seen[row][col] = true;

            while (stack.length)
            {
                const [curr_row, curr_col] = stack.pop();
                curr_area++;

                for (const [drow, dcol] of directions)
                {
                    const neighbor_row = curr_row + drow;
                    const neighbor_col = curr_col + dcol;

                    if (neighbor_row < 0
                        || neighbor_row >= grid.length
                        || neighbor_col < 0
                        || neighbor_col >= grid[0].length
                        || seen[neighbor_row][neighbor_col]
                        || grid[neighbor_row][neighbor_col] == 0)
                    {
                        continue;
                    }

                    seen[neighbor_row][neighbor_col] = true;
                    stack.push([neighbor_row, neighbor_col]);
                }
            }

            ans = Math.max(ans, curr_area);
        }
    }

    return ans;
};