from functools import cache


def maxValueOfCoinsDS1(piles: list[list[int]], k: int) -> int:
    @cache
    def get_max_value(curr_pile: int, remain_coins: int) -> int:
        if curr_pile == len(piles) or remain_coins == 0:
            return 0

        # Skip this pile
        max_value = get_max_value(curr_pile + 1, remain_coins)
        curr_value = 0

        for coin in range(min(remain_coins, len(piles[curr_pile]))):
            curr_value += piles[curr_pile][coin]
            max_value = max(max_value,
                            get_max_value(curr_pile + 1,
                                          remain_coins - coin - 1)
                            + curr_value)

        return max_value

    return get_max_value(0, k)


def maxValueOfCoinsDS2(piles: list[list[int]], k: int) -> int:
    num_piles = len(piles)
    dp = [[0] * (k + 1) for _ in range(num_piles + 1)]

    for curr_pile in range(num_piles - 1, -1, -1):
        for remain_coins in range(1, k + 1):
            # Skip this pile
            dp[curr_pile][remain_coins] = dp[curr_pile + 1][remain_coins]
            curr_value = 0
            for coin in range(min(remain_coins, len(piles[curr_pile]))):
                curr_value += piles[curr_pile][coin]
                dp[curr_pile][remain_coins] = max(
                    dp[curr_pile][remain_coins],
                    dp[curr_pile + 1][remain_coins - coin - 1]
                    + curr_value)

    return dp[0][k]
