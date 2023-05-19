class Solution
{
    Map<Integer, List<Integer>> graph = new HashMap<>();
    boolean[] seen;

    public void dfsRecursive(int node)
    {
        for (int neighbor: graph.get(node))
        {
            if (!seen[neighbor])
            {
                seen[neighbor] = true;
                dfsRecursive(neighbor);
            }
        }
    }

    public void dfsIterative(int node)
    {
        Stack<Integer> stack = new Stack<>();
        stack.push(node);

        while (!stack.empty())
        {
            int node = stack.pop();
            for (int neighbor: graph.get(node))
            {
                if (!seen[neighbor])
                {
                    seen[neighbor] = true;
                    stack.push(neighbor);
                }
            }
        }
    }

    public int findCircleNum(int[][] isConnected)
    {
        // Build the graph
        for (int i = 0; i < n; i++)
        {
            if (!graph.containsKey(i))
            {
                graph.put(i, new ArrayList<>());
            }

            for (int j = i + 1; j < n; j++)
            {
                if (!graph.containsKey(j))
                {
                    graph.put(j, new ArrayList<>());
                }

                if (isConnected[i][j] == 1)
                {
                    graph.get(i).add(j);
                    graph.get(j).add(i);
                }
            }
        }

        seen = new boolean[n];
        int ans = 0;

        for (int i = 0; i < n; i++)
        {
            if (!seen[i])
            {
                // Add all nodes of a connected component to the set
                ans++;
                seen[i] = true;
                dfsRecursive(i);
                // dfsIterative(i);
            }
        }

        return ans;
    }
}