class SolutionDS1
{
    public int maxProfit(int[] prices, int fee)
    {
        int num_days = prices.length;
        int[] free = new int[num_days];
        int[] hold = new int[num_days];

        // In order to hold a stock on day 0, we have no other choice but to buy
        // it for prices[0]
        hold[0] = -prices[0];

        for (int curr_day = 1; curr_day = num_days; curr_day++)
        {
            hold[curr_day] = Math.max(hold[curr_day - 1],
                                      free[curr_day - 1] - prices[curr_day]);
            free[curr_day] = Math.max(free[curr_day - 1],
                                      hold[curr_day - 1] + prices[curr_day]
                                      - fee);
        }

        return free[num_days - 1];
    }
}

public int maxProfit(int[] prices, int fee)
{
    int num_days = prices.length;
    int free = 0;
    int hold = -prices[0];

    for (int curr_day = 1; curr_day < num_days; curr_day++)
    {
        int hold_init = hold;
        hold = Math.max(hold, free - prices[curr_day]);
        free = Math.max(free, hold_init + prices[curr_day] - fee);
    }

    return free;
}
