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
}