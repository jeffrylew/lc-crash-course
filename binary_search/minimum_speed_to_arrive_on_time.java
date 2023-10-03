class Solution
{
    double limit;

    public boolean check(int k, int[] dist)
    {
        double t = 0;

        for (double d : dist)
        {
            t = Math.ceil(t);
            t += d / k;
        }

        return t <= limit;
    }

    public int minSpeedOnTime(int[] dist, double hour)
    {
        if (dist.length > Math.ceil(hour))
        {
            return -1;
        }

        limit = hour;

        int left = 1;
        int right = (int) Math.pow(10, 7);

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (check(mid, dist))
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