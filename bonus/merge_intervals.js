/**
 * @param {number[][]} intervals
 * @returns {number[][]}
 */
var merge = function(intervals)
{
    intervals.sort((a, b) => a[0] - b[0]);

    let merged_intervals = [];
    for (const [start, end] of intervals)
    {
        if (merged_intervals.length
            && start <= merged_intervals[merged_intervals.length - 1][1])
        {
            merged_intervals[merged_intervals.length - 1][1] =
                Math.max(merged_intervals[merged_intervals.length - 1][1], end);
        }
        else
        {
            merged_intervals.push([start, end]);
        }
    }

    return merged_intervals;
};
