public int maximumUnitsDS1(int[][] boxTypes, int truckSize)
{
    Arrays.sort(boxTypes, (a, b) -> b[1] - a[1]);

    int unitCount = 0;
    for (int[] boxType : boxTypes)
    {
        int boxCount = Math.min(truckSize, boxType[0]);
        unitCount += boxCount * boxType[1];
        truckSize -= boxCount;
        if (truckSize == 0)
        {
            break;
        }
    }

    return unitCount;
}

public int maximumUnitsDS2(int[][] boxTypes, int truckSize)
{
    PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b)->b[1] - a[1]);
    maxHeap.addAll(Arrays.asList(boxTypes));

    int unitCount = 0;
    while (!maxHeap.isEmpty())
    {
        int[] top = queue.poll();
        int boxCount = Math.min(truckSize, top[0]);
        unitCount += boxCount * top[1];
        truckSize -= boxCount;

        if (truckSize == 0)
        {
            break;
        }
    }

    return unitCount;
}
