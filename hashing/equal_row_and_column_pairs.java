public String convertToKey(int[] arr)
{
    StringBuilder sb = new StringBuilder();
    for (int i = 0; i < arr.length; i++)
    {
        sb.append(arr[i]);
        sb.append(",");
    }

    return sb.toString();
}

public int equalPairs(int[][] grid)
{
    Map<String, Integer> row_dic = new HashMap<>();
    for (int[] row : grid)
    {
        String key = convertToKey(row);
        row_dic.put(key, row_dic.getOrDefault(key, 0) + 1);
    }

    Map<String, Integer> col_dic = new HashMap<>();
    for (int col = 0; col < grid[0].length; col++)
    {
        int[] currentCol = new int[grid.length];
        for (int row = 0; row < grid.length; row++)
        {
            currentCol[row] = grid[row][col];
        }

        String key = convertToKey(currentCol);
        col_dic.put(key, col_dic.getOrDefault(key, 0) + 1);
    }

    int ans = 0;
    for (String key : row_dic.keySet())
    {
        ans += row_dic.get(key) * col_dic.getOrDefault(key, 0);
    }

    return ans;
}