class Solution
{
    int [][] grid;
    boolean [][] seen;

    public int area(int r, int c)
    {
        if (r < 0
            || r >= grid.length
            || c < 0
            || c >= grid[0].length
            || seen[r][c]
            || grid[r][c] == 0)
        {
            return 0;
        }

        seen[r][c] = true;

        return 1
            + area(r + 1, c) + area(r - 1, c) + area(r, c - 1) + area(r, c + 1);
    }

    public int maxAreaOfIslandDFSRecursive(int[][] grid)
    {
        this.grid = grid;
        seen = new boolean[grid.length][grid[0].length];

        int ans = 0;

        for (int row = 0; row < grid.length; ++row)
        {
            for (int col = 0; col < grid[0].length; ++col)
            {
                ans = Math.max(ans, area(row, col));
            }
        }

        return ans;
    }

    public int maxAreaOfIslandDFSIterative(int[][] grid)
    {
        boolean[][] seen = new boolean[grid.length][grid[0].length];
        int[] dr = new int[]{1, -1, 0, 0};
        int[] dc = new int[]{0, 0, 1, -1};

        int ans = 0;

        for (int r0 = 0; r0 < grid.length; r0++)
        {
            for (int c0 = 0; c0 < grid[0].length; c0++)
            {
                if (grid[r0][c0] == 1 && !seen[r0][c0])
                {
                    int shape = 0;
                    Stack<int[]> stack = new Stack();
                    stack.push(new int[]{r0, c0});
                    seen[r0][c0] = true;

                    while (!stack.empty())
                    {
                        int[] node = stack.pop();
                        int r = node[0];
                        int c = node[1];
                        shape++;

                        for (int k = 0; k < 4; k++)
                        {
                            int nr = r + dr[k];
                            int nc = c + dc[k];

                            if (nr >= 0
                                && nr < grid.length
                                && nc >= 0
                                && nc < grid[0].length
                                && grid[nr][nc] == 1
                                && !seen[nr][nc])
                            {
                                stack.push(new int[]{nr, nc});
                                seen[nr][nc] = true;
                            }
                        }
                    }

                    ans = Math.max(ans, shape);
                }
            }
        }

        return ans;
    }
}