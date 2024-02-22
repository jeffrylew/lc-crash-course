class SolutionDS1
{
    int num_piles;
    int[][] memo;
    List<List<Integer>> piles;

    private int get_max_value(int curr_pile, int remain_coins)
    {
        if (curr_pile == num_piles || remain_coins == 0)
        {
            return 0;
        }

        if (memo[curr_pile][remain_coins] != -1)
        {
            return memo[curr_pile][remain_coins];
        }

        int max_value = get_max_value(curr_pile + 1, remain_coins);
        int curr_value = 0;

        for (int coin = 0;
             coin < Math.min(remain_coins, piles.get(i).size());
             coin++)
        {
            curr_value += piles.get(curr_pile).get(coin);
            max_value = Math.max(max_value,
                                 get_max_value(curr_pile + 1,
                                               remain_coins - coin - 1)
                                 + curr_value);
        }

        memo[curr_pile][remain_coins] = max_value;
        return max_value;
    }

    public int maxValueOfCoins(List<List<Integer>> piles, int k)
    {
        num_piles = piles.size();
        memo = new int[num_piles][k + 1];

        for (int curr_pile = 0; curr_pile < num_piles; curr_pile++)
        {
            Arrays.fill(memo[curr_pile], -1);
        }

        this.piles = piles;
        return get_max_value(0, k);
    }
}
