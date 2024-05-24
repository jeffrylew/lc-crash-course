public boolean canAttendMeetings(int[][] intervals)
{
    Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));

    for (int idx = 1; idx < intervals.length; idx++)
    {
        if (intervals[idx][0] < intervals[idx - 1][1])
        {
            return false;
        }
    }

    return true;
}
