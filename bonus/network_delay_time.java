public int networkDelayTime(int[][] times, int n, int k)
{
    Map<Integer, List<Pair<Integer, Integer>>> graph = new HashMap<>();
    for (int[] edge : times)
    {
        int u = edge[0] - 1;
        int v = edge[1] - 1;
        int w = edge[2];

        graph.putIfAbsent(u, new ArrayList<>());
        graph.get(u).add(new Pair(v, w));
    }

    int[] distances = new int[n];
    Arrays.fill(distances, Integer.MAX_VALUE);

    Queue<Pair<Integer, Integer>> min_heap =
        new PriorityQueue<Pair<Integer, Integer>>(
            Comparator.comparing(Pair::getKey));
    min_heap.add(new Pair(0, k - 1));
    distances[k - 1] = 0;

    while (!min_heap.isEmpty())
    {
        Pair<Integer, Integer> curr = min_heap.remove();
        int currDist = curr.getKey();
        int node = curr.getValue();

        if (currDist > distances[node] || !graph.containsKey(node))
        {
            continue;
        }

        for (Pair<Integer, Integer> edge : graph.get(node))
        {
            int neighbor = edge.getKey();
            int weight = edge.getValue();
            int dist = currDist + weight;

            if (dist < distances[neighbor])
            {
                distances[neighbor] = dist;
                min_heap.add(new Pair(dist, neighbor));
            }
        }
    }

    int min_time = 0;
    for (int node = 0; node < n; node++)
    {
        min_time = Math.max(min_time, distances[node]);
    }

    return min_time == Integer.MAX_VALUE ? -1 : min_time;
}
