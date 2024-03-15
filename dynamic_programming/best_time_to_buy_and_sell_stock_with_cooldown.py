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
