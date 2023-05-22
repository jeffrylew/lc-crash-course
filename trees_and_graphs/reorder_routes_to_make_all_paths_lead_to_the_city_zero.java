class Solution
{
    Set<String> roads = new HashSet<>();
    Map<Integer, List<Integer>> graph = new HashMap<>();
    Set<Integer> seen = new HashSet<>();

    public String convertToHash(int row, int col)
    {
        return String.valueOf(row) + "," + String.valueOf(col);
    }

    public int dfsRecursive(int node)
    {
        int ans = 0;

        for (int neighbor : graph.get(node))
        {
            if (!seen.contains(neighbor))
            {
                if (roads.contains(convertToHash(node, neighbor)))
                {
                    ans++;
                }

                seen.add(neighbor);
                ans += dfsRecursive(neighbor);
            }
        }

        return ans;
    }

    public int dfsIterative(int start)
    {
        int ans = 0;

        Stack<Integer> stack = new Stack<>();
        stack.push(start);

        while (!stack.empty())
        {
            int node = stack.pop();

            for (int neighbor : graph.get(node))
            {
                if (!seen.contains(neighbor))
                {
                    if (roads.contains(convertToHash(node, neighbor)))
                    {
                        ans++;
                    }

                    seen.add(neighbor);
                    stack.push(neighbor);
                }
            }
        }

        return ans;
    }

    public int minReorder(int n, int[][] connections)
    {
        for (int i = 0; i < n; i++)
        {
            graph.put(i, new ArrayList<>());
        }

        for (int[] connection : connections)
        {
            int x = connection[0];
            int y = connection[1];

            graph.get(x).add(y);
            graph.get(y).add(x);
            roads.add(convertToHash(x, y));
        }

        seen.add(0);
        return dfsRecursive(0);
        // return dfsIterative(0);
    }
}