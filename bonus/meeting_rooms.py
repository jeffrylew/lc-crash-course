def canAttendMeetings(intervals):
    # Time complexity O(N * log N) due to the sort, N = len(intervals)
    # Python implements timsort which uses up to O(N) space

    intervals.sort()

    for idx in range(1, len(intervals)):
        if intervals[idx][0] < intervals[idx - 1][1]:
            return False

    return True
