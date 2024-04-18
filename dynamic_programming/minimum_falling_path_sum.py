import sys


def minFallingPathSumDS1(matrix: list[list[int]]) -> int:
    num_rows = len(matrix)
    num_cols = len(matrix[0])

    # Depth First Search recursively explores all paths from current (row, col)
    def findMinFallingPathSum(row: int, col: int) -> int:
        # Check if outside the left or right matrix boundary
        if col < 0 or col == num_cols:
            return sys.maxsize

        # Check if reached last row
        if row == num_rows - 1:
            return matrix[row][col]

        # Calculate min falling path sum starting from each possible next step
        left = findMinFallingPathSum(row + 1, col - 1)
        middle = findMinFallingPathSum(row + 1, col)
        right = findMinFallingPathSum(row + 1, col + 1)

        return min(left, middle, right) + matrix[row][col]

    minFallingSum = sys.maxsize
    for col in range(0, num_cols):
        minFallingSum = min(minFallingSum, findMinFallingPathSum(0, col))

    return minFallingSum
