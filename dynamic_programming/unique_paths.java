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

public int uniquePathsDS2
{
    int dp[][] = new int[m][n];
    dp[0][0] = 1;

    for (int row = 0; row < m; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row > 0)
            {
                dp[row][col] += dp[row - 1][col];
            }

            if (col > 0)
            {
                dp[row][col] += dp[row][col - 1];
            }
        }
    }

    return dp[m - 1][n - 1];
}

public int uniquePathsDS3
{
    int dp[] = new int[n];
    dp[0] = 1;

    for (int row = 0; row < m; row++)
    {
        int[] nextRow = new int[n];
        for (int col = 0; col < n; col++)
        {
            //! dp[col] is like previous row, dp[row - 1][col]
            //! nextRow[col] is dp[row][col]
            nextRow[col] += dp[col];
            if (col > 0)
            {
                //! nextRow[col - 1] is like previous col, dp[row][col - 1]
                //! nextRow[col] is dp[row][col]
                nextRow[col] += nextRow[col - 1];
            }
        }

        dp = nextRow;
    }

    return dp[n - 1];
}
