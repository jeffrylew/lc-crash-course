public Map<Integer, List<Integer>> buildGraph(int[][] edges)
{
    Map<Integer, List<Integer>> graph = new HashMap<>();

    for (int[] edge: edges)
    {
        int x = edge[0];
        int y = edge[1];

        if (!graph.containsKey(x))
        {
            graph.put(x, new ArrayList<>());
        }
        graph.get(x).add(y);

        // Uncomment following lines if the graph is undirected
        // if (!graph.containsKey(y))
        // {
        //     graph.put(y, new ArrayList<>());
        // }
        // graph.get(y).add(x);
    }

    return graph;
}