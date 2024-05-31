def insertDS1(
    intervals: list[list[int]], newInterval: list[int]
) -> list[list[int]]:
    num_intervals = len(intervals)
    idx = 0
    res = []

    # Case 1: No overlapping before merging intervals
    while idx < num_intervals and intervals[idx][1] < newInterval[0]:
        res.append(intervals[idx])
        idx += 1

    # Case 2: Overlapping and merging intervals
    while idx < num_intervals and newInterval[1] >= intervals[idx][0]:
        newInterval[0] = min(newInterval[0], intervals[idx][0])
        newInterval[1] = max(newInterval[1], intervals[idx][1])
        idx += 1
    res.append(newInterval)

    # Case 3: No overlapping after merging newInterval
    while idx < num_intervals:
        res.append(intervals[idx])
        idx += 1

    return res
