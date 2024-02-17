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
