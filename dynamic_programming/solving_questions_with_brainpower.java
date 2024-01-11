class SolutionTopDown
{
    Map<Integer, Long> memo = new HashMap<>();

    public long dp(int i, int[][] questions)
    {
        if (i >= questions.length)
        {
            return 0;
        }

        if (memo.containsKey(i))
        {
            return memo.get(i);
        }

        int next_idx = i + questions[i][1] + 1;
        memo.put(
            i,
            Math.max(questions[i][0] + dp(next_idx, questions),
                     dp(i + 1, questions)));
        return memo.get(i);
    }

    public long mostPoints(int[][] questions)
    {
        return dp(0, questions);
    }
}

public long mostPointsBottomUp(int[][] questions)
{
    int questions_length = questions.length;

    // + 1 to avoid out of bounds
    long[] dp = new long[questions_length + 1];

    for (int i = questions_length - 1; i >= 0; i--)
    {
        int next_idx = i + questions[i][1] + 1;

        // Need to make sure we don't go out of bounds
        dp[i] =
            Math.max(questions[i][0] + dp[Math.min(next_idx, questions_length)],
                     dp[i + 1]);
    }

    return dp[0];
}
