class SolutionDS1
{
    private int findMinFallingPathSum(int[][] matrix, int row, int col)
    {
        // Check if outside the left or right matrix boundary
        if (col < 0 || col == matrix[0].length)
        {
            return Integer.MAX_VALUE;
        }

        // Check if reached last row
        if (row == matrix.length - 1)
        {
            return matrix[row][col];
        }

        // Calculate min falling path sum starting from each possible next step
        int left = findMinFallingPathSum(matrix, row + 1, col - 1);
        int middle = findMinFallingPathSum(matrix, row + 1, col);
        int right = findMinFallingPathSum(matrix, row + 1, col + 1);

        return Math.min(left, Math.min(middle, right)) + matrix[row][col];
    }

    public int minFallingPathSum(int[][] matrix)
    {
        int minFallingSum = Integer.MAX_VALUE;
        for (int col = 0; col < matrix[0].length; col++)
        {
            minFallingSum =
                Math.min(minFallingSum, findMinFallingPathSum(matrix, 0, col));
        }

        return minFallingSum;
    }
}

class SolutionDS2
{
    private int findMinFallingPathSum(int[][]     matrix,
                                      int         row,
                                      int         col,
                                      Integer[][] memo)
    {
        // Base cases
        if (col < 0 || col == matrix[0].length)
        {
            return Integer.MAX_VALUE;
        }

        // Check if reached last row
        if (row == matrix.length - 1)
        {
            return matrix[row][col];
        }

        // Check if the results were calculated before
        if (memo[row][col] != null)
        {
            return memo[row][col];
        }

        // Calculate min falling path sum starting from each possible next step
        int left = findMinFallingPathSum(matrix, row + 1, col - 1, memo);
        int middle = findMinFallingPathSum(matrix, row + 1, col, memo);
        int right = findMinFallingPathSum(matrix, row + 1, col + 1, memo);

        memo[row][col] =
            Math.min(left, Math.min(middle, right)) + matrix[row][col];
        return memo[row][col];
    }

    public int minFallingPathSum(int[][] matrix)
    {
        int minFallingSum = Integer.MAX_VALUE;
        Integer memo[][] = new Integer[matrix.length][matrix[0].length];

        // Start a DFS with memoization from each cell in the top row
        for (int col = 0; col < matrix[0].length; ++col)
        {
            minFallingSum =
                Math.min(minFallingSum,
                         findMinFallingPathSum(matrix, 0, col, memo));
        }

        return minFallingSum;
    }
}

public int minFallingPathSumDS3(int[][] matrix)
{
    int num_rows = matrix.length;
    int num_cols = matrix[0].length;

    int dp[][] = new int[num_rows + 1][num_cols + 1];
    for (int row = num_rows - 1; row >= 0; row--)
    {
        for (int col = 0; col < num_cols; col++)
        {
            if (col == 0)
            {
                dp[row][col] = Math.min(dp[row + 1][col], dp[row + 1][col + 1])
                               + matrix[row];
            }
            else if (col == num_cols - 1)
            {
                dp[row][col] = Math.min(dp[row + 1][col], dp[row + 1][col - 1])
                               + matrix[row];
            }
            else
            {
                dp[row][col] =
                    Math.min(dp[row + 1][col - 1],
                             Math.min(dp[row + 1][col], dp[row + 1][col + 1]))
                    + matrix[row][col];
            }
        }
    }

    int minFallingSum = Integer.MAX_VALUE;
    for (int col = 0; col < num_cols; col++)
    {
        minFallingSum = Math.min(minFallingSum, dp[0][col]);
    }
    return minFallingPathSum;
}

public int minFallingPathSumDS4(int[][] matrix)
{
    int num_rows = matrix.length;
    int num_cols = matrix[0].length;

    int dp[] = new int[num_cols + 1];
    for (int row = num_rows - 1; row >= 0; row--)
    {
        int currentRow[] = new int[num_cols + 1];
        for (int col = 0; col < num_cols; col++)
        {
            if (col == 0)
            {
                currentRow[col] =
                    Math.min(dp[col], dp[col + 1]) + matrix[row][col];
            }
            else if (col == num_cols - 1)
            {
                currentRow[col] =
                    Math.min(dp[col - 1], dp[col]) + matrix[row][col];
            }
            else
            {
                currentRow[col] = Math.min(dp[col - 1],
                                           Math.min(dp[col], dp[col + 1]))
                                  + matrix[row][col];
            }
        }

        dp = currentRow;
    }

    int minFallingSum = Integer.MAX_VALUE;
    for (int col = 0; col < num_cols; col++)
    {
        minFallingSum = Math.min(minFallingSum, dp[col]);
    }
    return minFallingSum;
}
