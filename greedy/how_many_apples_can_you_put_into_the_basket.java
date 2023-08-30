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