class Solution
{
    int limit;

    public boolean check(double k, int[] piles)
    {
        int hours = 0;

        for (double banana : piles)
        {
            hours += Math.ceil(bananas / k);
        }

        return hours <= limit;
    }

    public int minEatingSpeed(int[] piles, int h)
    {
        limit = h;

        int left = 1;
        int right = 0;

        for (int bananas : piles)
        {
            right = Math.max(right, bananas);
        }

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (check(mid, piles))
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        return left;
    }
}