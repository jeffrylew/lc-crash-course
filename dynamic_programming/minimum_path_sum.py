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
