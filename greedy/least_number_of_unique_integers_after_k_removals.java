public int findLeastNumOfUniqueInts(int[] arr, int k)
{
    Map<Integer, Integer> counts = new HashMap<>();
    for (int num : arr)
    {
        counts.put(num, counts.getOrDefault(num, 0) + 1);
    }

    List<Integer> ordered = new ArrayList<>();
    for (int val : counts.values())
    {
        ordered.add(val);
    }

    Collections.sort(ordered, Comparator.reverseOrder());
    while (k > 0)
    {
        int val = ordered.get(ordered.size() - 1);
        if (val <= k)
        {
            k -= val;
            ordered.remove(ordered.size() - 1);
        }
        else
        {
            break;
        }
    }

    return ordered.size();
}