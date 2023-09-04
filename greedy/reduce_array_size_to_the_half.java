import java.util.Arrays;

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

public int minSetSizeDS2(int[] arr)
{
    // Sort the input numbers
    Arrays.sort(arr);

    // Write element counts directly into input arr
    int currentRun = 1;
    int currentRunIdx = 0;
    for (int i = 1; i < arr.length; i++)
    {
        if (arr[i] == arr[i - 1])
        {
            currentRun++;
            continue;
        }

        arr[currentRunIdx++] = currentRun;
        currentRun = 1;
    }
    arr[currentRunIdx++] = currentRun;

    for (int i = currentRunIdx; i < arr.length; i++)
    {
        arr[i] = 0;
    }

    // Collections.reverseOrder() does not work for primitive Types and would
    // require creation of an Integer[], which defeats the optimization
    Arrays.sort(arr);

    // In-place reversal of array
    for (int i = 0; i < arr.length / 2; i++)
    {
        // Swapping the elements
        int temp = arr[i];
        arr[i] = arr[arr.length - i - 1];
        arr[arr.length - i - 1] = temp;
    }

    // Remove numbers until at least half are removed
    int numbersRemovedFromArr = 0;
    int setSize = 0;
    for (int count : arr)
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

public int minSetSizeDS3(int[] arr)
{
    // Do the counting with a HashMap
    Map<Integer, Integer> countsMap = new HashMap<>();
    for (int num : arr)
    {
        if (!countsMap.containsKey(num))
        {
            countsMap.put(num, 1);
            continue;
        }

        countsMap.put(num, countsMap.get(num) + 1);
    }

    // Reverse sort a list of the Map values
    List<Integer> counts = new ArrayList<>(countsMap.values());
    Collections.sort(counts, Collections.reverseOrder());

    // Remove numbers until at least half are removed
    int numbersRemovedFromArr = 0;
    int setSize = 0;

    for (int count : counts)
    {
        numbersRemovedFromArr += count;
        setSize += 1;

        if (numbersRemovedFromArr >= arr.length / 2)
        {
            break;
        }
    }

    return setSize;
}

public int minSetSizeDS4(int[] arr)
{
    Map<Integer, Integer> countsMap = new HashMap<>();
    int maxCount = 1; // Different from discussion solution
    for (int num : arr)
    {
        if (!countsMap.containsKey(num))
        {
            countsMap.put(num, 1);
            continue;
        }

        countsMap.put(num, countsMap.get(num) + 1);
        maxCount = Math.max(maxCount, countsMap.get(num));
    }

    // Put the counts into buckets
    int[] buckets = new int[maxCount + 1];
    for (int count : countsMap.values())
    {
        buckets[count]++;
    }

    // Determine setSize
    int setSize = 0;
    int numbersToRemoveFromArr = arr.length / 2;
    int bucket = maxCount;

    while (numbersToRemoveFromArr > 0)
    {
        int maxNeededFromBucket = numbersToRemoveFromArr / bucket;
        if (numbersToRemoveFromArr % bucket != 0)
        {
            maxNeededFromBucket++;
        }

        int setSizeIncrease = Math.min(buckets[bucket], maxNeededFromBucket);
        setSize += setSizeIncrease;
        numbersToRemoveFromArr -= setSizeIncrease * bucket;
        bucket--;
    }

    return setSize;
}