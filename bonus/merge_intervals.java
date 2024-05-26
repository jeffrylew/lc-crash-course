public int[][] merge(int[][] intervals)
{
    Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));

    LinkedList<int[]> merged_intervals = new LinkedList<>();
    for (int[] interval : intervals)
    {
        int start = interval[0];
        int end = interval[1];

        if (!merged_intervals.isEmpty()
            && start <= merged_intervals.getLast()[1])
        {
            merged_intervals.getLast()[1] =
                Math.max(merged_intervals.getLast()[1], end);
        }
        else
        {
            merged_intervals.add(interval);
        }
    }

    return merged_intervals.toArray(new int[merged_intervals.size()][]);
}
