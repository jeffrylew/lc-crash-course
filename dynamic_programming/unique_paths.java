class SolutionDS1
{
    int[][] memo;

    private int dp(int row, int col)
    {
        if (row + col == 0)
        {
            // Base case
            return 1;
        }

        if (memo[row][col] != -1)
        {
            return memo[row][col];
        }

        int ways = 0;
        if (row > 0)
        {
            ways += dp(row - 1, col);
        }

        if (col > 0)
        {
            ways += dp(row, col - 1);
        }

        memo[row][col] = ways;
        return ways;
    }

    public int uniquePaths(int m, int n)
    {
        memo = new int[m][n];
        for (int row = 0; row < m; ++row)
        {
            Arrays.fill(memo[row], -1);
        }

        return dp(m - 1, n - 1);
    }
}
