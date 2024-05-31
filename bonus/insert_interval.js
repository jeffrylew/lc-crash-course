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
