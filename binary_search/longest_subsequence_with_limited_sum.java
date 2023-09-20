public int[] answerQueriesDS1(int[] nums, int[] queries)
{
    // Sort nums
    Arrays.sort(nums);
    int n = nums.length;
    int m = queries.length;
    int answer[] = new int[m];

    // For each query, collect numbers from lowest to highest
    // If their sum exceeds the limit query, move on to the next query
    for (int i = 0; i < m; ++i)
    {
        int count = 0;
        int query = queries[i];

        for (int num : nums)
        {
            if (query >= num)
            {
                count++;
                query -= num;
            }
            else
            {
                break;
            }
        }

        answer[i] = count;
    }

    return answer;
}

public int binarySearch(int[] nums, int target)
{
    // Different from discussion solution implementation (commented out below)
    // See binarySearchLastIndex in binary_search_templates.java

    int left = 0;
    int right = nums.length;

    while (left < right)
    {
        int mid = left + (right - left) / 2;

        if (nums[mid] > target)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left;

    /*
    int left = 0;
    int right = nums.length - 1;
    
    while (left < right)
    {
        int mid = (left + right) / 2;

        if (nums[mid] == target)
        {
            return mid + 1;
        }

        if (nums[mid] > target)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return nums[left] > target ? left : left + 1;
     */
}

public int[] answerQueriesDS2(int[] nums, int[] queries)
{
    // Get the prefix sum array of the sorted nums
    Arrays.sort(nums);

    for (int i = 1; i < nums.length; ++i)
    {
        nums[i] += nums[i - 1];
    }

    // For each query, find its insertion index in the prefix sum array
    int n = queries.length;
    int answer[] = new int[n];

    for (int i = 0; i < n; ++i)
    {
        int index = binarySearch(nums, queries[i]);
        answer[i] = index;
    }

    return answer;
}