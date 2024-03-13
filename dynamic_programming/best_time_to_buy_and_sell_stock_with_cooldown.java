public int maxProfitDS1(int[] prices)
{
    int sold = Integer.MIN_VALUE;
    int hold = Integer.MIN_VALUE;
    int reset = 0;

    for (int price : prices)
    {
        int pre_sold = sold;

        sold = hold + price;
        hold = Math.max(hold, reset - price);
        reset = Math.max(reset, pre_sold);
    }

    return Math.max(sold, reset);
}

public int maxProfitDS2(int[] prices)
{
    int[] max_profit = new int[prices.length + 2];

    for (int prev_day = prices.length - 1; prev_day >= 0; prev_day--)
    {
        int case1 = 0;

        // Case 1) Buy on prev_day and sell on curr_day for prices[curr_day]
        for (int curr_day = prev_day + 1; curr_day < prices.length; curr_day++)
        {
            int profit = (prices[curr_day] - prices[prev_day])
                         + max_profit[curr_day + 2];

            case1 = Math.max(profit, case1);
        }

        // Case 2) No transaction with the stock at prices[prev_day]
        int case2 = max_profit[prev_day + 1];

        // Wrap up the two cases
        max_profit[prev_day] = Math.max(case1, case2);
    }

    return max_profit[0];
}
