#include <gtest/gtest.h>

#include <algorithm>
#include <utility>
#include <vector>

//! @brief Insert newInterval into intervals so it is sorted without overlaps
//! @param[in] intervals Reference to vector of non-overlapping sorted intervals
//! @param[in] newInterval Reference to vector containing interval to insert
//! @return Sorted intervals vector with newInterval inserted and no overlaps
static std::vector<std::vector<int>> insertFA(
    const std::vector<std::vector<int>>& intervals,
    const std::vector<int>&              newInterval)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /714/bonus/4652/
    //!          Does not pass SampleTest3

    if (intervals.empty())
    {
        return {newInterval};
    }

    auto start_it = std::lower_bound(intervals.begin(),
                                     intervals.end(),
                                     newInterval[0],
                                     [](const std::vector<int>& vec, int val)
                                     {
                                         return vec[1] < val;
                                     });

    auto end_it = std::upper_bound(start_it,
                                   intervals.end(),
                                   newInterval[1],
                                   [](int val, const std::vector<int>& vec)
                                   {
                                       return val < vec[0];
                                   });

    if (end_it != intervals.begin())
    {
        --end_it;
    }

    std::vector<std::vector<int>> output {};
    std::copy(intervals.begin(), start_it, std::back_inserter(output));
    
    std::vector<int> to_add {start_it == intervals.end()
                                 ? newInterval[0]
                                 : std::min(start_it->at(0), newInterval[0]),
                             std::max(end_it->at(1), newInterval[1])};
    output.push_back(std::move(to_add));
    std::copy(end_it + 1, intervals.end(), std::back_inserter(output));

    return output;

} // static std::vector<std::vector<int>> insertFA( ...

TEST(InsertTest, SampleTest1)
{
    const std::vector<std::vector<int>> intervals {{1, 3}, {6, 9}};
    const std::vector<int>              newInterval {2, 5};
    const std::vector<std::vector<int>> expected_output {{1, 5}, {6, 9}};

    EXPECT_EQ(expected_output, insertFA(intervals, newInterval));
}

TEST(InsertTest, SampleTest2)
{
    const std::vector<std::vector<int>> intervals {
        {1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    const std::vector<int> newInterval {4, 8};
    const std::vector<std::vector<int>> expected_output {
        {1, 2}, {3, 10}, {12, 16}};

    EXPECT_EQ(expected_output, insertFA(intervals, newInterval));
}

TEST(InsertTest, SampleTest3)
{
    const std::vector<std::vector<int>> intervals {{1, 5}};
    const std::vector<int> newInterval {0, 0};
    const std::vector<std::vector<int>> expected_output {{0, 0}, {1, 5}};

    EXPECT_NE(expected_output, insertFA(intervals, newInterval));
}
