def merge(intervals: list[list[int]]) -> list[list[int]]:
    intervals.sort()

    merged_intervals = []
    for start, end in intervals:
        if merged_intervals and start <= merged_intervals[-1][1]:
            merged_intervals[-1][1] = max(merged_intervals[-1][1], end)
        else:
            merged_intervals.append([start, end])

    return merged_intervals
