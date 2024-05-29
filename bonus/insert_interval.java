public int[][] insertDS1(int[][] intervals, int[] newInterval)
{
    int num_intervals = intervals.length;
    int idx = 0;

    List<int[]> res = new ArrayList<>();

    // Case 1: No overlapping before merging intervals
    while (idx < num_intervals && intervals[idx][1] < newInterval[0])
    {
        res.add(inervals[idx]);
        idx++;
    }

    // Case 2: Overlapping and merging intervals
    while (idx < num_intervals && newInterval[1] >= intervals[idx][0])
    {
        newInterval[0] = Math.min(newInterval[0], intervals[idx][0]);
        newInterval[1] = Math.max(newInterval[1], intervals[idx][1]);
        idx++;
    }
    res.add(newInterval);

    // Case 3: No overlapping after merging newInterval
    while (idx < num_intervals)
    {
        res.add(intervals[idx]);
        idx++;
    }

    // Convert List to array
    return res.toArray(new int[res.size()][]);
}
