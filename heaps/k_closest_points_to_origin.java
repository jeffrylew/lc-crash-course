import java.util.concurrent.ThreadLocalRandom;

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

class Solution
{
    int[][] points;

    public int[][] kClosestDS2(int[][] points, int k)
    {
        this.points = points;
        sort(0, points.length - 1, k);
        return Arrays.copyOfRange(points, 0, k);
    }

    public void sort(int i, int j, int k)
    {
        if (i >= j)
        {
            return;
        }

        int idx = ThreadLocalRandom.current().nextInt(i, j);
        swap(i, idx);

        int mid = partition(i, j);
        int leftLength = mid - i + 1;

        if (k < leftLength)
        {
            sort(i, mid - 1, k);
        }
        else if (k > leftLength)
        {
            sort(mid + 1, j, k - leftLength);
        }
    }

    public int partition(int i, int j)
    {
        int oi = i;
        int pivot = dist(i);
        i++;

        while (true)
        {
            while (i < j && dist(i) < pivot)
            {
                i++;
            }

            // Note: dist(j) >= pivot in python solution
            while (i <= j && dist(j) > pivot)
            {
                j--;
            }

            if (i >= j)
            {
                break;
            }

            swap(i, j);
        }

        swap(oi, j);
        return j;
    }

    public int dist(int i)
    {
        return points[i][0] * points[i][0] + points[i][1] * points[i][1];
    }

    public void swap(int i, int j)
    {
        int t0 = points[i][0];
        int t1 = points[i][1];

        points[i][0] = points[j][0];
        points[i][1] = points[j][1];

        points[j][0] = t0;
        points[j][1] = t1;
    }
}