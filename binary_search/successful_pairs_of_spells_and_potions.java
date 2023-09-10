public int binarySearch(int[] arr, double target)
{
    int left = 0;
    int right = arr.length - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return left;
}

public int[] successfulPairs(int[] spells, int[] potions, long success)
{
    Arrays.sort(potions);

    int[] ans = new int[spells.length]; // = n
    int npotions = potions.length; // = m

    for (int i = 0; i < spells.length; i++)
    {
        int insert_idx = binarySearch(potions, success / (double) spells[i]);
        ans[i] = npotions - insert_idx;
    }

    return ans;
}