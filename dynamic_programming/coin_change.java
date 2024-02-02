class SolutionDS1
{
    private int total_amount;

    private int get_min_coins(int[] coins, int remaining_amt)
    {
        if (remaining_amt < 0)
        {
            return -1;
        }

        if (remaining_amt == 0)
        {
            return 0;
        }

        int min_count = total_amount + 1;

        for (int coin : coins)
        {
            int count = get_min_coins(coins, remaining_amt - coin);

            if (count == -1)
            {
                continue;
            }

            min_count = std::min(min_count, count + 1);
        }

        return min_count == (total_amount + 1) ? -1 : min_count;
    }

    public int coinChange(int[] coins, int amount)
    {
        total_amount = amount;
        return get_min_coins(coins, amount);
    }
}

class SolutionDS2
{
    private int total_amount;
    private Integer[] memo;

    private int get_min_coins(int[] coins, int remaining_amt)
    {
        if (remaining_amt < 0)
        {
            return -1;
        }

        if (remaining_amt == 0)
        {
            return 0;
        }

        if (memo[remaining_amt] != null)
        {
            return memo[remaining_amt];
        }

        int min_count = total_amount + 1;

        for (int coin : coins)
        {
            int count = get_min_coins(coins, remaining_amt - coin);
            if (count == -1)
            {
                continue;
            }

            min_count = Math.min(min_count, count + 1);
        }

        memo[remaining_amt] = min_count == (total_amount + 1) ? -1 : min_count;
        return memo[remaining_amt];
    }

    public int coinChange(int[] coins, int amount)
    {
        total_amount = amount;
        memo = new Integer[amount + 1];
        return get_min_coins(coins, amount);
    }
}

public int coinChangeDS3(int[] coins, int amount)
{
    int[] dp = new int[amount + 1];
    Arrays.fill(dp, amount + 1);

    dp[0] = 0;

    for (int remaining_amt = 1; remaining_amt <= amount; remaining_amt++)
    {
        for (int coin : coins)
        {
            if (remaining_amt - coin < 0)
            {
                continue;
            }

            dp[remaining_amt] =
                Math.min(dp[remaining_amt], dp[remaining_amt - coin] + 1);
        }
    }

    return dp[amount] == (amount + 1) ? -1 : dp[amount];
}
