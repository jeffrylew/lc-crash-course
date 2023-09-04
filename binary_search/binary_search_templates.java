public int binarySearch(int[] arr, int target)
{
    int left = 0;
    int right = arr.length - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            // Do something
            return mid;
        }

        if (arr[mid] > target)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    // Target is not in arr but left is at the insertion point
    return left;
}