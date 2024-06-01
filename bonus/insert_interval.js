/**
 * @param {number[][]} intervals
 * @param {number[]} newInterval
 * @returns {number[][]}
 */
var insertDS1 = function(intervals, newInterval)
{
    const num_intervals = intervals.length;
    let idx = 0;

    let res = [];

    // Case 1: No overlapping before merging intervals
    while (idx < num_intervals && intervals[idx][1] < newInterval[0])
    {
        res.push(intervals[idx]);
        idx++;
    }

    // Case 2: Overlapping and merging intervals
    while (idx < num_intervals && newInterval[1] >= intervals[idx][0])
    {
        newInterval[0] = Math.min(newInterval[0], intervals[idx][0]);
        newInterval[1] = Math.max(newInterval[1], intervals[idx][1]);
        idx++;
    }
    res.push(newInterval);

    // Case 3: No overlapping after merging newInterval
    while (idx < num_intervals)
    {
        res.push(intervals[idx]);
        idx++;
    }

    return res;
};

/**
 * @param {number[][]} intervals
 * @param {number[]} newInterval
 * @returns {number[][]}
 */
var insertDS2 = function(intervals, newInterval)
{
    // If intervals is empty, return an array containing newInterval
    if (intervals.length === 0)
    {
        return [newInterval];
    }

    const num_intervals = intervals.length;
    let left = 0;
    let right = num_intervals - 1;

    // Binary search to find the position to insert newInterval
    while (left <= right)
    {
        const mid = Math.floor((left + right) / 2);
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
    intervals.splice(left, 0, newInterval);

    // Merge overlapping intervals
    let res = [];
    for (const interval of intervals)
    {
        // If res is empty or there is no overlap, add interval to result
        if (res.length === 0 || res[res.length - 1][1] < interval[0])
        {
            res.push(interval);
        }
        else
        {
            // If there is overlap, update end of last interval in res to merge
            res[res.length - 1][1] =
                Math.max(res[res.length - 1][1], interval[1]);
        }
    }

    return res;
};
