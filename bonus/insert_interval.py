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


def insertDS2(
    intervals: list[list[int]], newInterval: list[int]
) -> list[list[int]]:
    # If intervals is empty, return a list containing newInterval
    if not intervals:
        return [newInterval]

    num_intervals = len(intervals)
    left, right = 0, num_intervals - 1

    # Binary search to find the position to insert newInterval
    while left <= right:
        mid = (left + right) // 2

        if intervals[mid][0] < newInterval[0]:
            left = mid + 1
        else:
            right = mid - 1

    # Insert newInterval at the found position
    intervals.insert(left, newInterval)

    # Merge overlapping intervals
    res = []
    for interval in intervals:
        # If res is empty or there is no overlap, add interval to result
        if not res or res[-1][1] < interval[0]:
            res.append(interval)
        # If there is overlap, update end of last interval in res to merge
        else:
            res[-1][1] = max(res[-1][1], interval[1])

    return res
