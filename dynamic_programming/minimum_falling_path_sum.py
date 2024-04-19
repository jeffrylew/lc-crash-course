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
    for col in range(num_cols):
        minFallingSum = min(minFallingSum, findMinFallingPathSum(0, col))

    return minFallingSum


def minFallingPathSumDS2(matrix: list[list[int]]) -> int:
    num_rows = len(matrix)
    num_cols = len(matrix[0])
    memo = [[sys.maxsize for _ in range(num_cols)] for _ in range(num_rows)]

    def findMinFallingPathSum(row: int, col: int) -> int:
        # Base cases
        if col < 0 or col == num_cols:
            return sys.maxsize

        # Check if reached last row
        if row == num_rows - 1:
            return matrix[row][col]

        # Check if results have been calculated before
        if memo[row][col] != sys.maxsize:
            return memo[row][col]

        # Calculate min falling path sum starting from each possible next step
        left = findMinFallingPathSum(row + 1, col - 1)
        middle = findMinFallingPathSum(row + 1, col)
        right = findMinFallingPathSum(row + 1, col + 1)

        minSum = min(left, middle, right) + matrix[row][col]
        memo[row][col] = minSum
        return minSum

    minFallingSum = sys.maxsize

    # Start a DFS with memoization from each cell in the top row
    for col in range(num_cols):
        minFallingSum = min(minFallingSum, findMinFallingPathSum(0, col))

    return minFallingSum


def minFallingPathSumDS3(matrix: list[list[int]]) -> int:
    num_rows = len(matrix)
    num_cols = len(matrix[0])
    dp = [[0 for _ in range(num_cols + 1)] for _ in range(num_rows + 1)]

    for row in range(num_rows - 1, -1, -1):
        for col in range(num_cols):
            if col == 0:
                dp[row][col] = (min(dp[row + 1][col], dp[row + 1][col + 1])
                                + matrix[row][col])
            elif col == num_cols - 1:
                dp[row][col] = (min(dp[row + 1][col - 1], dp[row + 1][col])
                                + matrix[row][col])
            else:
                dp[row][col] = (min(dp[row + 1][col - 1],
                                    dp[row + 1][col],
                                    dp[row + 1][col + 1])
                                + matrix[row][col])

    return min(dp[0][:num_cols])
