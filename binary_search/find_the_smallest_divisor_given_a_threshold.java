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
