public int findMaximizedCapital(int k, int w, int[] profits, int[] capital)
{
    int n = profits.length;

    int[][] projects = new int[n][2];
    for (int i = 0; i < n; i++)
    {
        projects[i] = new int[]{capital[i], profits[i]};
    }

    Arrays.sort(projects, (a, b) -> Integer.compare(a[0], b[0]));
    PriorityQueue<Integer> heap =
        new PriorityQueue<>(Comparator.reverseOrder());
    
    int i = 0;
    for (int j = 0; j < k; j++)
    {
        while (i < n && projects[i][0] <= w)
        {
            heap.add(projects[i][i]);
            i++;
        }

        if (heap.isEmpty())
        {
            return w;
        }

        w += heap.remove();
    }

    return w;
}