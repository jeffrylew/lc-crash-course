class Solution
{
    // Variables for DS1
    private int target;
    private int[][] graph;
    private List<List<Integer>> results;

    // Variables for DS2
    private int target2;
    private int[][] graph2;
    private HashMap<Integer, List<List<Integer>>> memo;

    protected void backtrack(int currNode, LinkedList<Integer> path)
    {
        if (currNode == this.target)
        {
            // Make a deep copy of the path
            this.results.add(new ArrayList<Integer>(path));
            return;
        }

        // Explore the neighbor nodes
        for (int nextNode : this.graph[currNode])
        {
            path.addLast(nextNode);
            this.backtrack(nextNode, path);
            path.removeLast();
        }
    }

    public List<List<Integer>> allPathsSourceTargetDS1(int[][] graph)
    {
        this.target = graph.length - 1;
        this.graph = graph;
        this.results = new ArrayList<List<Integer>>;
    
        // Use LinkedList for fast access to tail element
        LinkedList<Integer> path = new LinkedList<Integer>();
        path.addLast(0);
        this.backtrack(0, path);
        return this.results;
    }

    protected List<List<Integer>> allPathsToTarget(int currNode)
    {
        // Memoization, check the result in the cache first
        if (memo.containsKey(currNode))
        {
            return memo.get(currNode);
        }

        List<List<Integer>> results = new ArrayList<>();

        // Base case
        if (currNode == this.target2)
        {
            ArrayList<Integer> path = new ArrayList<>();
            path.add(this.target2);
            results.add(path);
            return results;
        }

        // Iterate through the paths starting from each neighbor
        for (int nextNode : this.graph2[currNode])
        {
            for (List<Integer> path : allPathsToTarget(nextNode))
            {
                ArrayList<Integer> newPath = new ArrayList<>();
                newPath.add(currNode);
                newPath.addAll(path);
                results.add(newPath);
            }
        }

        memo.put(currNode, results);
        return results;
    }

    public List<List<Integer>> allPathsSourceTargetDS2(int[][] graph)
    {
        this.target2 = graph.length - 1;
        this.graph2 = graph;
        this.memo = new HashMap<>();

        return this.allPathsToTarget(0);
    }
}
