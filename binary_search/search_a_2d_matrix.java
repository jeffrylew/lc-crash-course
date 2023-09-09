public boolean searchMatrix(int[][] matrix, int target)
{
    int nrows = matrix.length;    // = m
    int ncols = matrix[0].length; // = n

    int left = 0;
    int right = nrows * ncols - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int row = mid / ncols;
        int col = mid % ncols;
        int num = matrix[row][col];

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
}