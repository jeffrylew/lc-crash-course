public List<Integer> intersection(int[][] nums)
{
    Map<Integer, Integer> counts = new HashMap<>();
    for (int[] arr : nums)
    {
        for (int x : arr)
        {
            counts.put(x, counts.getOrDefault(x, 0) + 1);
        }
    }
    
    int n = nums.length;
    List<Integer> ans = new ArrayList<>();
    for (int key : counts.keySet())
    {
        if (counts.get(key) == n)
        {
            ans.add(key);
        }
    }

    Collections.sort(ans);
    return ans;
}