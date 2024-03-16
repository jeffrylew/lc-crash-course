def maxProfitDS1(prices: list[int]) -> int:
    sold, hold, reset = float('-inf'), float('-inf'), 0

    for price in prices:
        # Alternative: the calculation is done in parallel
        # Therefore, there is no need to keep temporary variables
        # sold,hold,reset = hold + price,max(hold,reset - price),max(reset,sold)

        pre_sold = sold
        sold = hold + price
        hold = max(hold, reset - price)
        reset = max(reset, pre_sold)

    return max(sold, reset)


def maxProfitDS2(prices: list[int]) -> int:
    num_days = len(prices)

    # Pad array with additional zero to simplify the logic
    max_profit = [0] * (num_days + 2)

    for prev_day in range(num_days - 1, -1, -1):
        case1 = 0

        # Case 1) Buy and sell the stock
        for curr_day in range(prev_day + 1, num_days):
            profit = ((prices[curr_day] - prices[prev_day])
                      + max_profit[curr_day + 2])

            case1 = max(profit, case1)

        # Case 2) No transaction with the stock at prices[prev_day]
        case2 = max_profit[prev_day + 1]

        # Wrap up the two cases
        max_profit[prev_day] = max(case1, case2)

    return max_profit[0]
