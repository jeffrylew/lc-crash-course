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
}