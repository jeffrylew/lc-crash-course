from functools import cache


def maxProfitDS1(k: int, prices: list[int]) -> int:
    @cache
    def get_max_profit(curr_day: int, holding: bool, remain_tx: int) -> int:
        if curr_day == len(prices) or remain_tx == 0:
            return 0

        max_profit = get_max_profit(curr_day + 1, holding, remain_tx)
        if holding:
            max_profit = max(max_profit,
                             get_max_profit(curr_day + 1, False, remain_tx - 1)
                             + prices[curr_day])
        else:
            max_profit = max(max_profit,
                             get_max_profit(curr_day + 1, True, remain_tx)
                             - prices[curr_day])

        return max_profit

    return get_max_profit(0, False, k)


def maxProfitDS2(k: int, prices: list[int]) -> int:
    num_days = len(prices)
    dp = [[[0] * (k + 1) for _ in range(2)] for __ in range(num_days + 1)]

    for curr_day in range(num_days - 1, -1, -1):
        for remain_tx in range(1, k + 1):
            for holding_stock in range(2):
                max_profit = dp[curr_day + 1][holding_stock][remain_tx]
                if holding_stock:
                    max_profit = max(max_profit,
                                     dp[curr_day + 1][0][remain_tx - 1]
                                     + prices[curr_day])
                else:
                    max_profit = max(max_profit,
                                     dp[curr_day + 1][1][remain_tx]
                                     - prices[curr_day])

                dp[curr_day][holding_stock][remain_tx] = max_profit

    return dp[0][0][k]
