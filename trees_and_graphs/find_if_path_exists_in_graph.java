class Solution
{
    public boolean validPath(int n, int[][] edges, int source, int destination)
    {
        Map<Integer, List<Integer>> graph = new HashMap<>();
        boolean[] seen = new boolean[n];

        for (int[] edge : edges)
        {
            int a = edge[0];
            int b = edge[1];
            graph.computeIfAbsent(a, val -> new ArrayList<Integer>()).add(b);
            graph.computeIfAbsent(b, val -> new ArrayList<Integer>()).add(a);
        }

        return dfsRecursive(graph, seen, source, destination);
    }

    private boolean dfsRecursive(Map<Integer, List<Integer>> graph,
                                 boolean[]                   seen,
                                 int                         currNode,
                                 int                         destination)
    {
        if (currNode == destination)
        {
            return true;
        }

        if (!seen[currNode])
        {
            seen[currNode] = true;
            for (int nextNode : graph.get(currNode))
            {
                if (dfsRecursive(graph, seen, nextNode, destination))
                {
                    return true;
                }
            }
        }

        return false;
    }
}