public int reachableNodesBFS(int n, int[][] edges, int[] restricted)
{
    // Store all edges in neighbors
    Map<Integer, List<Integer>> neighbors = new HashMap<>();
    for (int[] edge : edges)
    {
        int a = edge[0];
        int b = edge[1];

        neighbors.computeIfAbsent(a, value -> new ArrayList<Integer>()).add(b);
        neighbors.computeIfAbsent(b, value -> new ArrayList<Integer>()).add(a);
    }

    // Mark the nodes in restricted as visited
    Set<Integer> seen = new HashSet<>();
    for (int node : restricted)
    {
        seen.add(node);
    }

    // Store all the nodes to be visited in queue
    int ans = 0;
    seen.add(0);

    Queue<Integer> queue = new LinkedList<>(Arrays.asList(0));

    while (!queue.isEmpty())
    {
        int currNode = queue.poll();
        ans++;

        for (int nextNode : neighbors.get(currNode))
        {
            if (!seen.contains(nextNode))
            {
                seen.add(nextNode);
                queue.offer(nextNode);
            }
        }
    }

    return ans;
}