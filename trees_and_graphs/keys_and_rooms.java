class Solution
{
    Set<Integer> seen = new HashSet<>();

    public void dfsRecursive(int node, List<List<Integer>> rooms)
    {
        for (int neighbor : rooms.get(node))
        {
            if (!seen.contains(neighbor))
            {
                seen.add(neighbor);
                dfsRecursive(neighbor, room);
            }
        }
    }

    public void dfsIterative(int node, List<List<Integer>> rooms)
    {
        Stack<Integer> stack = new Stack<>();
        stack.push(0);

        while (!stack.empty())
        {
            int node = stack.pop();
            for (int neighbor : rooms.get(node))
            {
                if (!seen.contains(neighbor))
                {
                    seen.add(neighbor);
                    stack.push(neighbor);
                }
            }
        }
    }

    public boolean canVisitAllRooms(List<List<Integer>> rooms)
    {
        seen.add(0);
        dfsRecursive(0, rooms);
        // dfsIterative(0, rooms);
        return seen.size() == rooms.size();
    }
}