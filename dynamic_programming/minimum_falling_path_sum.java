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
