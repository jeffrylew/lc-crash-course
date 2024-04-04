from functools import cache


def minPathSumDS1(grid: list[list[int]]) -> int:
    @cache
    def dp(row, col):
        if row + col == 0:
            return grid[row][col]

        min_sum = float("inf")
        if row > 0:
            min_sum = min(min_sum, dp(row - 1, col))

        if col > 0:
            min_sum = min(min_sum, dp(row, col - 1))

        return grid[row][col] + min_sum

    num_rows = len(grid)
    num_cols = len(grid[0])
    return dp(num_rows - 1, num_cols - 1)


def minPathSumDS2(grid: list[list[int]]) -> int:
    num_rows = len(grid)
    num_cols = len(grid[0])
    dp = [[0] * num_cols for _ in range(num_rows)]
    dp[0][0] = grid[0][0]

    for row in range(num_rows):
        for col in range(num_cols):
            if row + col == 0:
                continue

            min_sum = float("inf")
            if row > 0:
                min_sum = min(min_sum, dp[row - 1][col])

            if col > 0:
                min_sum = min(min_sum, dp[row][col - 1])

            dp[row][col] = grid[row][col] + min_sum

    return dp[num_rows - 1][num_cols - 1]


def minPathSumDS3(grid: list[list[int]]) -> int:
    num_rows = len(grid)
    num_cols = len(grid[0])
    dp = [float("inf")] * num_cols
    dp[0] = 0

    for row in range(num_rows):
        next_row = [0] * num_cols
        for col in range(num_cols):
            next_row[col] = dp[col]
            if col > 0:
                next_row[col] = min(next_row[col], next_row[col - 1])

            next_row[col] += grid[row][col]

        dp = next_row

    return dp[num_cols - 1]
