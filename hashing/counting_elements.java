public int countElements(int[] arr)
{
    Set<Integer> numSet = new HashSet<>();
    for (int x : arr)
    {
        numSet.add(x);
    }

    int count = 0;
    for (int x : arr)
    {
        if (numSet.contains(x + 1))
        {
            count++;
        }
    }

    return count;
}