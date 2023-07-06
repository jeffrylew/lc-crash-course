public int dfsRecursive(int                         curr_node,
                        Set<Integer>                visited,
                        Map<Integer, List<Integer>> graph)
{
    visited.add(curr_node);

    int count = 1;

    for (int neighbor : graph.getOrDefault(curr_node, new ArrayList<>()))
    {
        if (!visited.contains(neighbor))
        {
            count += dfsRecursive(neighbor, visited, graph);
        }
    }

    return count;
}

public int maximumDetonation(int[][] bombs)
{
    Map<Integer, List<Integer>> graph = new HashMap<>();
    int n = bombs.length;

    // Build the graph
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int xi = bombs[i][0];
            int yi = bombs[i][1];
            int ri = bombs[i][2];

            int xj = bombs[j][0];
            int yj = bombs[j][1];
            int rj = bombs[j][2];

            long dx2 = (long)(xi - xj) * (xi - xj);
            long dy2 = (long)(yi - yj) * (yi - yj);
            long ri2 = (long)ri * ri;
            long rj2 = (long)rj * rj;

            if (ri2 >= dx2 + dy2)
            {
                graph.computeIfAbsent(i, k -> new ArrayList<>()).add(j);
            }

            if (rj2 >= dx2 + dy2)
            {
                graph.computeIfAbsent(j, k -> new ArrayList<>()).add(i);
            }
        }
    }

    int answer = 0;

    for (int i = 0; i < n; i++)
    {
        int count = dfsRecursive(i, new HashSet<>(), graph);

        answer = Math.max(answer, count);
    }

    return answer;
}