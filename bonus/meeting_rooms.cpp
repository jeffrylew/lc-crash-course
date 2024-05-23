#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Determine if a person could attend all meetings in vector of times
//! @param[in] intervals Reference to vector of meeting times [start_i, end_i]
//! @return True if a person could attend all meetings, else false
static bool canAttendMeetings(const std::vector<std::vector<int>>& intervals)
{
    //! @details https://leetcode.com/problems/meeting-rooms/description/
    //!
    //!          Time complexity O(N * log N) where N = intervals.size()
    //!          Space complexity O(log N) on average for C++ quicksort

    std::sort(intervals.begin(), intervals.end());

    for (int idx = 1; idx < static_cast<int>(intervals.size()); ++idx)
    {
        //! If meeting at idx (intervals[idx][0]) starts before the idx - 1
        //! meeting ends (intervals[idx - 1[1]]) then there is a conflict
        if (intervals[idx][0] < intervals[idx - 1][1])
        {
            return false;
        }
    }

    return true;
}

TEST(CanAttendMeetingsTest, SampleTest1)
{
    const std::vector<std::vector<int>> intervals {{0, 30}, {5, 10}, {15, 20}};

    EXPECT_FALSE(canAttendMeetings(intervals));
}

TEST(CanAttendMeetingsTest, SampleTest2)
{
    const std::vector<std::vector<int>> intervals {{7, 10}, {2, 4}};

    EXPECT_TRUE(canAttendMeetings(intervals));
}
