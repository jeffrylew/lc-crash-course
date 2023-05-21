class Solution
{
    int m;
    int n;
    int[][] directions = new int[][]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    Set<String> seen = new HashSet<>();

    public String convertToHash(int row, int col)
    {
        return String.valueOf(row) + "," + String.valueOf(col);
    }

    public boolean valid(int row, int col, char[][] grid)
    {
        return 0 <= row
            && row < m
            && 0 <= col
            && col < n
            && grid[row][col] == '1';
    }

    public void dfsRecursive(int row, int col, char[][] grid)
    {
        for (int[] direction : directions)
        {
            int nextRow = row + direction[0];
            int nextCol = col + direction[1];
            String hash = convertToHash(nextRow, nextCol);

            if (valid(nextRow, nextCol, grid) && !seen.contains(hash))
            {
                seen.add(hash);
                dfsRecursive(nextRow, nextCol, grid);
            }
        }
    }

    public void dfsIterative(int startRow, int startCol, char[][] grid)
    {
        Stack<Integer> rowStack = new Stack<>();
        Stack<Integer> colStack = new Stack<>();
        rowStack.push(startRow);
        colStack.push(startCol);

        while (!rowStack.empty())
        {
            int row = rowStack.pop();
            int col = colStack.pop();

            for (int[] direction : directions)
            {
                int nextRow = row + direction[0];
                int nextCol = col + direction[1];
                String hash = convertToHash(nextRow, nextCol);

                if (valid(nextRow, nextCol, grid) && !seen.contains(hash))
                {
                    seen.add(hash);
                    rowStack.push(nextRow);
                    colStack.push(nextCol);
                }
            }
        }
    }

    public int numIslands(char[][] grid)
    {
        int ans = 0;
        m = grid.length;
        n = grid[0].length;

        for (int row = 0; row < m; row++)
        {
            for (int col = 0; col < n; col++)
            {
                String hash = convertToHash(row, col);
                if (grid[row][col] == '1' && !seen.contains(hash))
                {
                    ans++;
                    seen.add(hash);
                    dfsRecursive(row, col, grid);
                    // dfsIterative(row, col, grid);
                }
            }
        }

        return ans;
    }
}