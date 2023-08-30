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