public class SolutionDS1
{
    public int climb_Stairs(int curr_step, int n)
    {
        if (curr_step > n)
        {
            return 0;
        }

        if (curr_step == n)
        {
            return 1;
        }

        return climb_Stairs(curr_step + 1, n) + climb_Stairs(curr_step + 2, n);
    }

    public int climbStairs(int n)
    {
        return climb_Stairs(0, n);
    }
}

public class SolutionDS2
{
    public int climb_Stairs(int curr_step, int n, int memo[])
    {
        if (curr_step > n)
        {
            return 0;
        }

        if (curr_step == n)
        {
            return 1;
        }

        if (memo[curr_step] > 0)
        {
            return memo[curr_step];
        }

        memo[curr_step] =
            climb_Stairs(curr_step + 1, n, memo)
            + climb_Stairs(curr_step + 2, n, memo);
        return memo[curr_step];
    }

    public int climbStairs(int n)
    {
        int memo[] = new int[n + 1];
        return climb_Stairs(0, n, memo);
    }
}

public class SolutionDS3
{
    public int climbStairs(int n)
    {
        if (n == 1)
        {
            return 1;
        }

        int dp[] = new int[n + 1];
        dp[1] = 1;
        dp[2] = 2;

        for (int curr_step = 3; curr_step <= n; curr_step++)
        {
            dp[curr_step] = dp[curr_step - 1] + dp[curr_step - 2];
        }

        return dp[n];
    }
}

public class SolutionDS4
{
    public int climbStairs(int n)
    {
        if (n == 1)
        {
            return 1;
        }

        int first = 1;
        int second = 2;
        for (int curr_step = 3; curr_step <= n; curr_step++)
        {
            int third = first + second;
            first = second;
            second = third;
        }

        return second;
    }
}
