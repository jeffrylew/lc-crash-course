class Solution_TopDown
{
    Map<Integer, Integer> memo = new HashMap<>();

    // 1. A function that returns the answer
    public int dp(int i, int[] cost)
    {
        if (i <= 1)
        {
            // 3. Base case(s)
            return 0;
        }

        if (memo.containsKey(i))
        {
            return memo.get(i);
        }

        // 2. Recurrence relation
        memo.put(i, Math.min(dp(i - 1, cost) + cost[i - 1],
                             dp(i - 2, cost) + cost[i - 2]));

        return memo.get(i);
    }

    public int minCostClimbingStairs(int[] cost)
    {
        return dp(cost.length, cost);
    }
}
