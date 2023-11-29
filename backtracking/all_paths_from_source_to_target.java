class Solution
{
    private int target;
    private int[][] graph;
    private List<List<Integer>> results;

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
}