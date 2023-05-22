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

    public boolean canVisitAllRooms(List<List<Integer>> rooms)
    {
        seen.add(0);
        dfsRecursive(0, rooms);
        return seen.size() == rooms.size();
    }
}