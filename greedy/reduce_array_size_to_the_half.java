public int minSetSizeDS1(int[] arr)
{
    // Sort the input numbers
    Arrays.sort(arr);

    // Make the List of Counts
    List<Integer> counts = new ArrayList<>();
    int currentRun = 1;
    for (int i = 1; i < arr.length; i++)
    {
        if (arr[i] == arr[i - 1])
        {
            currentRun++;
            continue;
        }

        counts.add(currentRun);
        currentRun = 1;
    }
    counts.add(currentRun);

    Collections.sort(counts);
    Collections.reverse(counts);

    // Remove numbers until at least half are removed
    int numbersRemovedFromArr = 0;
    int setSize = 0;
    for (int count : counts)
    {
        numbersRemovedFromArr += count;
        setSize++;

        if (numbersRemovedFromArr >= arr.length / 2)
        {
            break;
        }
    }

    return setSize;
}