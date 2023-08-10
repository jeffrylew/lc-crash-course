public int dist(int[] point)
{
    return point[0] * point[0] + point[1] * point[1];
}

public int[][] kClosestDS1(int[][] points, int k)
{
    int N = points.length;
    int[] dists = new int[N];

    for (int i = 0; i < N; ++i)
    {
        dists[i] = dist(points[i]);
    }

    Arrays.sort(dists);
    int distK = dists[k - 1];

    int[][] ans = new int[k][2];
    int t = 0;

    for (int i = 0; i < N; ++i)
    {
        if (dist(points[i]) <= distK)
        {
            ans[t++] = points[i];
        }
    }

    return ans;
}