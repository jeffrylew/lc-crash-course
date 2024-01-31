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
