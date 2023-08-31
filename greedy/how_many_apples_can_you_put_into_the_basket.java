public int maxNumberOfApplesDS1(int[] weight)
{
    Arrays.sort(weight);

    int apples = 0;
    int units = 0;

    for (int i = 0; i < weight.length && units + weight[i] <= 5000; i++)
    {
        apples++;
        units += weight[i];
    }

    return apples;
}

public int maxNumberOfApplesDS2(int[] weight)
{
    List<Integer> weights = Arrays.stream(arr).boxed().collect(Collectors.toList());
    Queue<Integer> minHeap = new PriorityQueue<>(weights);

    int apples = 0;
    int units = 0;

    while (!minHeap.isEmpty() && units + minHeap.peek() <= 5000)
    {
        units += minHeap.remove();
        apples++;
    }

    return apples;
}

public int maxNumberOfApplesDS3(int[] weight)
{
    // Initialize the bucket to store all elements
    int size = -1;
    for (Integer ele : weight)
    {
        size = Math.max(size, ele);
    }

    int[] bucket = new int[size + 1];
    for (Integer ele : weight)
    {
        bucket[ele]++;
    }

    int apples = 0;
    int units = 0;
    for (int i = 0; i < size + 1; i++)
    {
        // If we have apples of i units of weight
        if (bucket[i] != 0)
        {
            // We need to make sure that:
            // 1. We do not take more apples than those provided
            // 2. We do not exceed 5000 units of weight
            int take = Math.min(bucket[i], (5000 - units) / i);

            if (take == 0)
            {
                break;
            }

            units += take * i;
            apples += take;
        }
    }

    return apples;
}