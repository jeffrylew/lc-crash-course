#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Merge all overlapping intervals intervals[i] = [start, end]
//! @param[in] intervals Reference to vector of intervals
//! @return Vector of non-overlapping intervals that cover all input intervals
static std::vector<std::vector<int>> merge(
    const std::vector<std::vector<int>>& intervals)
{
    //! @details https://leetcode.com/problems/merge-intervals/description/
    //!
    //!          Time complexity O(N * log N) where N = intervals.size() for
    //!          sorting the number of intervals.
    //!          Space complexity O(log N) for C++ quicksort

    std::sort(intervals.begin(), intervals.end());

    std::vector<std::vector<int>> merged_intervals {};
    for (const auto& interval : intervals)
    {
        const int start {interval[0]};
        const int end {interval[1]};

        if (not merged_intervals.empty() && start <= merged_intervals.back()[1])
        {
            auto& last_merged_end = merged_intervals.back()[1];
            last_merged_end       = std::max(last_merged_end, end);
        }
        else
        {
            merged_intervals.push_back(interval);
        }
    }

    return merged_intervals;
}

TEST(MergeTest, SampleTest1)
{
    const std::vector<std::vector<int>> intervals {
        {1, 3}, {2, 6}, {8, 10}, {15, 18}};

    const std::vector<std::vector<int>> expected_output {
        {1, 6}, {8, 10}, {15, 18}};

    EXPECT_EQ(expected_output, merge(intervals));
}

TEST(MergeTest, SampleTest2)
{
    const std::vector<std::vector<int>> intervals {{1, 4}, {4, 5}};
    const std::vector<std::vector<int>> expected_output {{1, 5}};

    EXPECT_EQ(expected_output, merge(intervals));
}
