class SolutionDS1
{
    int num_days;
    int[][][] memo;
    int[] prices;

    private int get_max_profit(int curr_day, int holding_stock, int remain_tx)
    {
        if (curr_day == num_days || remain_tx == 0)
        {
            return 0;
        }

        if (memo[curr_day][holding_stock][remain_tx] != -1)
        {
            return memo[curr_day][holding_stock][remain_tx];
        }

        int max_profit = get_max_profit(curr_day + 1, holding_stock, remain_tx);
        if (holding_stock == 1)
        {
            max_profit = Math.max(max_profit,
                                  get_max_profit(curr_day + 1, 0, remain_tx - 1)
                                  + prices[curr_day]);
        }
        else
        {
            max_profit = Math.max(max_profit,
                                  get_max_profit(curr_day + 1, 1, remain_tx)
                                  - prices[curr_day]);
        }

        memo[curr_day][holding_stock][remain_tx] = max_profit;
        return max_profit;
    }

    public int maxProfit(int k, int[] prices)
    {
        num_days = prices.length;
        memo = new int[num_days][2][k + 1];
        for (int curr_day = 0; curr_day < num_days; curr_day++)
        {
            for (int holding_idx = 0; holding_idx < 2; holding_idx++)
            {
                Arrays.fill(memo[curr_day][holding_idx], -1);
            }
        }

        this.prices = prices;
        return get_max_profit(0, 0, k);
    }
}

public int maxProfitDS2(int k, int[] prices)
{
    int num_days = prices.length;
    int[][][] dp = new int[num_days + 1][2][k + 1];

    for (int curr_day = num_days - 1; curr_day >= 0; curr_day--)
    {
        for (int remain_tx = 1; remain_tx <= k; remain_tx++)
        {
            for (int holding_stock = 0; holding_stock < 2; holding_stock++)
            {
                int max_profit = dp[curr_day + 1][holding_stock][remain_tx];
                if (holding_stock == 1)
                {
                    max_profit = Math.max(max_profit,
                                          dp[curr_day + 1][0][remain_tx - 1]
                                          + prices[curr_day]);
                }
                else
                {
                    max_profit = Math.max(max_profit,
                                          dp[curr_day + 1][1][remain_tx]
                                          - prices[curr_day]);
                }

                dp[curr_day][holding_stock][remain_tx] = max_profit;
            }
        }
    }

    return dp[0][0][k];
}
