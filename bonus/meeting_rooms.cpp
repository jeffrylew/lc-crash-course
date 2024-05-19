#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

static bool canAttendMeetings(const std::vector<std::vector<int>>& intervals)
{
    std::sort(intervals.begin(), intervals.end());

    for (int idx = 1; idx < static_cast<int>(intervals.size()); ++idx)
    {
        if (intervals[idx][0] < intervals[idx - 1][1])
        {
            return false;
        }
    }

    return true;
}
