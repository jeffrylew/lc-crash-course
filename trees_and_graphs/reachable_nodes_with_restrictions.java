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

class Solution
{
    private int ans = 0;

    private void dfsRecursive(int                         currNode,
                              Map<Integer, List<Integer>> neighbors,
                              Set<Integer>                seen)
    {
        // Mark currNode as visited and increment ans by 1
        ans++;
        seen.add(currNode);

        // Go for unvisited neighbors of currNode
        for (int nextNode : neighbors.get(currNode))
        {
            if (!seen.contains(nextNode))
            {
                dfsRecursive(nextNode, neighbors, seen);
            }
        }
    }

    public int reachableNodesRecursive(int n, int[][] edges, int[] restricted)
    {
        // Store all edges according to nodes in neighbors
        Map<Integer, List<Integer>> neighbors = new HashMap<>();

        for (int[] edge : edges)
        {
            int a = edge[0];
            int b = edge[1];

            neighbors.computeIfAbsent(a, value -> new ArrayList<Integer>()).add(b);
            neighbors.computeIfAbsent(b, value -> new ArrayList<Integer>()).add(a);
        }

        // Mark nodes in restricted as visited
        Set<Integer> seen = new HashSet<>();
        for (int node : restricted)
        {
            seen.add(node);
        }

        dfsRecursive(0, neighbors, seen);
        return ans;
    }
}

public int reachableNodesIterative(int n, int[][] edges, int[] restricted)
{
    // Store all edges according to nodes in neighbors
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

    // Use stack to store all nodes to be visited
    int ans = 0;
    seen.add(0);
    Stack<Integer> stack = new Stack<>();
    stack.add(0);

    while (!stack.isEmpty())
    {
        int currNode = stack.pop();
        ans++;

        // Add all unvisited neighbors of current node to stack
        // and mark it as visited
        for (int nextNode : neighbors.get(curNode))
        {
            if (!seen.contains(nextNode))
            {
                seen.add(nextNode);
                stack.add(nextNode);
            }
        }
    }

    return ans;
}