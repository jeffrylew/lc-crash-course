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
