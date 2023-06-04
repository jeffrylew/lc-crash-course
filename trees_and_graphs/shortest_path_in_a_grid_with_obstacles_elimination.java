class State
{
    int row;
    int col;
    int remain;
    int steps;

    State(int row, int col, int remain, int steps)
    {
        this.row = row;
        this.col = col;
        this.remain = remain;
        this.steps = steps;
    }
}

class Solution
{
    int m;
    int n;
    int[][] directions = new int[][]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    public boolean valid(int row, int col)
    {
        return 0 <= row && row < m && 0 <= col && col < n;
    }

    // Runtime 29 ms: Beats 57.3%
    // Memory 44.8 MB: Beats 26.9%
    public int shortestPath1(int[][] grid, int k)
    {
        m = grid.length;
        n = grid[0].length;

        Queue<State> queue = new LinkedList<>();
        boolean[][][] seen = new boolean[m][n][k + 1];
        queue.add(new State(0, 0, k, 0));
        seen[0][0][k] = true;

        while (!queue.isEmpty())
        {
            State state = queue.remove();
            int row = state.row;
            int col = state.col;
            int remain = state.remain;
            int steps = state.steps;

            if (row == m - 1 && col == n - 1)
            {
                return steps;
            }

            for (int[] direction : directions)
            {
                int nextRow = row + direction[0];
                int nextCol = col + direction[1];

                if (valid(nextRow, nextCol))
                {
                    if (grid[nextRow][nextCol] == 0)
                    {
                        if (!seen[nextRow][nextCol][remain])
                        {
                            seen[nextRow][nextCol][remain] = true;
                            queue.add(
                                new State(nextRow, nextCol, remain, steps + 1));
                        }
                    }
                    else if (remain > 0 && !seen[nextRow][nextCol][remain - 1])
                    {
                        // Otherwise at an obstacle and can only pass if have
                        // remaining removals
                        seen[nextRow][nextCol][remain - 1] = true;
                        queue.add(
                            new State(nextRow, nextCol, remain - 1, steps + 1));
                    }
                }
            }
        }

        return -1;
    }

    // Runtime 19 ms: Beats 66.75%
    // Memory 43.8 MB: Beats 45.1%
    public int shortestPath2(int[][] grid, int k)
    {
        m = grid.length;
        n = grid[0].length;

        int[][] seen = new int[m][n];
        for (int row = 0; row < m; row++)
        {
            for (int col = 0; col < n; col++)
            {
                seen[row][col] = -1;
            }
        }

        Queue<State> queue = new LinkedList<>();
        queue.add(new state(0, 0, k, 0));

        while (!queue.isEmpty())
        {
            State state = queue.remove();
            int row = state.row;
            int col = state.col;
            int remain = state.remain;
            int steps = state.steps;

            if (row == m - 1 && col == n - 1)
            {
                return steps;
            }

            if (grid[row][col] == 1)
            {
                if (remain == 0)
                {
                    continue;
                }
                else
                {
                    remain--;
                }
            }

            if (seen[row][col] >= remain)
            {
                continue;
            }

            seen[row][col] = remain;
            for (int[] direction : directions)
            {
                int nextRow = row + direction[0];
                int nextCol = col + direction[1];

                if (valid(nextRow, nextCol))
                {
                    queue.add(new State(nextRow, nextCol, remain, steps + 1));
                }
            }
        }

        return -1;
    }
}