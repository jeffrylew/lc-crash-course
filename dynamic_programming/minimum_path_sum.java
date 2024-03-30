class SolutionDS1
{
    int num_rows;
    int num_cols;
    int[][] memo;
    int[][] grid;

    private int dp(int row, int col)
    {
        if (row + col == 0)
        {
            return grid[row][col];
        }

        if (memo[row][col] != -1)
        {
            return memo[row][col];
        }

        int min_sum = Integer.MAX_VALUE;
        if (row > 0)
        {
            min_sum = Math.min(min_sum, dp(row - 1, col));
        }

        if (col > 0)
        {
            min_sum = Math.min(min_sum, dp(row, col - 1));
        }

        memo[row][col] = grid[row][col] + min_sum;
        return memo[row][col];
    }

    public int minPathSum(int[][] grid)
    {
        num_rows = grid.length;
        num_cols = grid[0].length;
        memo = new int[num_rows][num_cols];
        for (int row = 0; row < num_rows; row++)
        {
            Arrays.fill(memo[row], -1);
        }

        this.grid = grid;
        return dp(num_rows - 1, num_cols - 1);
    }
}
