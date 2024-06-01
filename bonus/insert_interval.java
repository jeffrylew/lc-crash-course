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

public int[][] insertDS2(int[][] interals, int[] newInterval)
{
    // If intervals array is empty, return array containing newInterval
    if (intervals.length == 0)
    {
        return new int[][] { newInterval };
    }

    int num_intervals = intervals.length;
    int left = 0;
    int right = num_intervals - 1;

    // Binary search to find the position to insert newInterval
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (intervals[mid][0] < newInterval[0])
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    // Insert newInterval at the found position
    List<int[]> intervals_copy = new ArrayList<>();
    for (int idx = 0; idx < left; idx++)
    {
        intervals_copy.add(intervals[idx]);
    }
    intervals_copy.add(newInterval);
    for (int idx = left; idx < num_intervals; idx++)
    {
        intervals_copy.add(intervals[idx]);
    }

    // Merge overlapping intervals
    List<int[]> res = new ArrayList<>();
    for (int[] interval : intervals_copy)
    {
        // If res is empty or there is no overlap, add interval to result
        if (res.isEmpty() || res.get(res.size() - 1)[1] < interval[0])
        {
            res.add(interval);
        }
        else
        {
            // If there is overlap, update end of last interval in res to merge
            res.get(res.size() - 1)[1] =
                Math.max(res.get(res.size() - 1)[1], interval[1]);
        }
    }

    // Discussion solution has merged.toArray(new int[0][]), which also works
    return res.toArray(new int[res.size()][]);
}
