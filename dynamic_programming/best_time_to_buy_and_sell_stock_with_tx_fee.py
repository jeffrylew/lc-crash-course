def maxProfitDS1(prices: list[int], fee: int) -> int:
    num_days = len(prices)
    hold, free = [0] * num_days, [0] * num_days

    # In order to hold a stock on day 0, we have
    # no other choice but to buy it for prices[0]
    hold[0] = -prices[0]

    for curr_day in range(1, num_days):
        hold[curr_day] = max(hold[curr_day - 1],
                             free[curr_day - 1] - prices[curr_day])
        free[curr_day] = max(free[curr_day - 1],
                             hold[curr_day - 1] + prices[curr_day] - fee)

    return free[-1]
