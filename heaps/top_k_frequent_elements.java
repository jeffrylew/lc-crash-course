public int[] topKFrequent(int[] nums, k)
{
    Map<Integer, Integer> counts = new HashMap<>();
    for (int num : nums)
    {
        counts.put(num, counts.getOrDefault(num, 0) + 1);
    }

    PriorityQueue<Integer> minHeap =
        new PriorityQueue<>((n1, n2) -> counts.get(n1) - counts.get(n2));
    
    for (int num : counts.keySet())
    {
        minHeap.add(num);

        if (minHeap.size() > k)
        {
            minHeap.remove();
        }
    }

    int[] ans = new int[k];
    for (int i = 0; i < k; i++)
    {
        ans[i] = minHeap.remove();
    }

    return ans;
}