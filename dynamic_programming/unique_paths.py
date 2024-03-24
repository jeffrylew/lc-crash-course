from functools import cache


def uniquePathsDS1(m: int, n: int) -> int:
    @cache
    def get_unique_paths(row: int, col: int) -> int:
        if row + col == 0:
            # Base case
            return 1

        num_ways = 0
        if row > 0:
            num_ways += get_unique_paths(row - 1, col)

        if col > 0:
            num_ways += get_unique_paths(row, col - 1)

        return num_ways

    return get_unique_paths(m - 1, n - 1)


def uniquePathsDS2(m: int, n: int) -> int:
    dp = [[0] * n for _ in range(m)]
    dp[0][0] = 1

    for row in range(m):
        for col in range(n):
            if row > 0:
                dp[row][col] += dp[row - 1][col]

            if col > 0:
                dp[row][col] += dp[row][col - 1]

    return dp[m - 1][n - 1]


def uniquePathsDS3(m: int, n: int) -> int:
    dp = [0] * n
    dp[0] = 1

    for _ in range(m):
        next_row = [0] * n
        for col in range(n):
            next_row[col] += dp[col]
            if col > 0:
                next_row[col] += next_row[col - 1]

        dp = next_row

    return dp[n - 1]
