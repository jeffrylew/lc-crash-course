from functools import cache


def mostPointsTopDown(questions: list[list[int]]) -> int:
    @cache
    def dp(i: int) -> int:
        if i >= len(questions):
            return 0

        next_index = i + questions[i][1] + 1
        return max(questions[i][0] + dp(next_index), dp(i + 1))

    return dp(0)


def mostPointsBottomUp(questions: list[list[int]]) -> int:
    questions_len = len(questions)

    # + 1 to avoid out of bounds
    dp = [0] * (questions_len + 1)

    for i in range(questions_len - 1, -1, -1):
        # Need to make sure we don't go out of bounds
        next_index = min(i + questions[i][1] + 1, questions_len)

        dp[i] = max(questions[i][0] + dp[next_index], dp[i + 1])

    return dp[0]
