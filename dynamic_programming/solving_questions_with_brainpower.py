from functools import cache


def mostPointsTopDown(questions: list[list[int]]) -> int:
    @cache
    def dp(i: int) -> int:
        if i >= len(questions):
            return 0

        next_index = i + questions[i][1] + 1
        return max(questions[i][0] + dp(next_index), dp(i + 1))

    return dp(0)
