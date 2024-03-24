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
