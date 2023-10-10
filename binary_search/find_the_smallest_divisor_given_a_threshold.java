public int smallestDivisorDS1(int[] nums, int threshold)
{
    int maxElement = nums[0];
    for (int num : nums)
    {
        maxElement = Math.max(maxElement, num);
    }

    // Iterate on all divisors
    for (int divisor = 1; divisor <= maxElement; ++divisor)
    {
        int sumOfDivisionResults = 0;
        boolean thresholdExceeded = false;

        // Divide all numbers of array and sum the result
        for (int num : nums)
        {
            sumOfDivisionResults += Math.ceil((1.0 * num) / divisor);
            if (sumOfDivisionResults > threshold)
            {
                thresholdExceeded = true;
                break;
            }
        }

        // If the threshold was not exceeded then return current divisor
        if (!thresholdExceeded)
        {
            return divisor;
        }
    }

    return -1;
}

// Return the sum of division results with divisor
public int findDivisionSum(int[] nums, int divisor)
{
    int result = 0;
    for (int num : nums)
    {
        result += Math.ceil((1.0 * num) / divisor);
    }
    return result;
}

public int smallestDivisorDS2(int[] nums, int threshold)
{
    int ans = -1;

    int low = 1;
    int high = nums[0];
    for (int num : nums)
    {
        high = Math.max(high, num);
    }

    // Iterate using binary search on all divisors
    while (low <= high)
    {
        int mid = (low + high) / 2;
        int result = findDivisionSum(nums, mid);

        // If current divisor does not exceed threshold then it can be answer
        // Also try smaller divisors so change search space to left half
        if (result <= threshold)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            // Otherwise need a bigger divisor to reduce the result sum
            // so change search space to right half
            low = mid + 1;
        }
    }

    return ans;
}
