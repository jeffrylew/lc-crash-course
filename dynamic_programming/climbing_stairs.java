public class SolutionDS1
{
    public int climb_Stairs(int i, int n)
    {
        if (i > n)
        {
            return 0;
        }

        if (i == n)
        {
            return 1;
        }

        return climb_Stairs(i + 1, n) + climb_Stairs(i + 2, n);
    }

    public int climbStairs(int n)
    {
        return climb_Stairs(0, n);
    }
}

public class SolutionDS2
{
    public int climb_Stairs(int i, int n, int memo[])
    {
        if (i > n)
        {
            return 0;
        }

        if (i == n)
        {
            return 1;
        }

        if (memo[i] > 0)
        {
            return memo[i];
        }

        memo[i] = climb_Stairs(i + 1, n, memo) + climb_Stairs(i + 2, n, memo);
        return memo[i];
    }

    public int climbStairs(int n)
    {
        int memo[] = new int[n + 1];
        return climb_Stairs(0, n, memo);
    }
}
