/**
 * @param {number[][]} intervals
 * @returns {boolean}
 */
var canAttendMeetings = function(intervals)
{
    intervals.sort((a, b) => a[0] - b[0]);

    for (let idx = 1; idx < intervals.length; idx++)
    {
        if (intervals[idx][0] < intervals[idx - 1][1])
        {
            return false;
        }
    }

    return true;
};
