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
