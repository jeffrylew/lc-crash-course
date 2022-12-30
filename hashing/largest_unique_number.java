public int largestUniqueNumber(int[] nums)
{
    Map<Integer, Integer> counts = new HashMap<>();
    for (int num : nums)
    {
        counts.put(num, counts.getOrDefault(num, 0) + 1);
    }

    int result = -1;
    /*
    for (int num : counts.keySet())
    {
        if (counts.get(num) == 1)
        {
            result = Math.max(result, num);
        }
    }
     */
    
    for (Map.Entry<Integer, Integer> entry : counts.entrySet())
    {
        if (entry.getValue() == 1)
        {
            result = Math.max(result, entry.getKey());
        }
    }

    return result;
}