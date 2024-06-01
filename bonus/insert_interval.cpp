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

//! @brief Linear search discussion solution
//! @param[in] intervals Reference to vector of non-overlapping sorted intervals
//! @param[in] newInterval Reference to vector containing interval to insert
//! @return Sorted intervals vector with newInterval inserted and no overlaps
static std::vector<std::vector<int>> insertDS1(
    const std::vector<std::vector<int>>& intervals,
    const std::vector<int>&              newInterval)
{
    //! @details https://leetcode.com/problems/insert-interval/editorial/
    //!
    //!          Time complexity O(N) where N = number of intervals. Iterate
    //!          through intervals once and each interval is considered and
    //!          processed only once.
    //!          Space complexity O(1) to create to_add vector, which has a
    //!          constant size of 2 elements. If the input newInterval can be
    //!          modified, then the space complexity remains O(1). Only use
    //!          result vector to store output.

    const auto num_intervals = static_cast<int>(intervals.size());
    int        idx {};

    std::vector<std::vector<int>> res {};

    //! Case 1: No overlapping before merging intervals
    //! Compare ending point of intervals to starting point of newInterval
    while (idx < num_intervals && intervals[idx][1] < newInterval[0])
    {
        res.push_back(intervals[idx++]);
    }

    //! Case 2: Overlapping and merging intervals
    auto to_add = newInterval
    while (idx < num_intervals && to_add[1] >= intervals[idx][0])
    {
        to_add[0] = std::min(to_add[0], intervals[idx][0]);
        to_add[1] = std::max(to_add[1], intervals[idx][1]);
        ++idx;
    }
    res.push_back(std::move(to_add));

    //! Case 3: No overlapping after merging newInterval
    while (idx < num_intervals)
    {
        res.push_back(intervals[idx++]);
    }

    return res;

} // static std::vector<std::vector<int>> insertDS1( ...

//! @brief Binary search discussion solution
//! @param[in] intervals Reference to vector of non-overlapping sorted intervals
//! @param[in] newInterval Reference to vector containing interval to insert
//! @return Sorted intervals vector with newInterval inserted and no overlaps
static std::vector<std::vector<int>> insertDS2(
    const std::vector<std::vector<int>>& intervals,
    const std::vector<int>&              newInterval)
{
    //! @details https://leetcode.com/problems/insert-interval/editorial/
    //!
    //!          Time complexity O(N), where N = number of intervals. Binary
    //!          search to find insert position of newInterval takes O(log N).
    //!          However, insertion of newInterval can take O(N) in the worst
    //!          case, as it could involve shifting elements within the vector.
    //!          The overall time complexity is O(N + log N), or O(N).
    //!          Space complexity O(N). Needed to store the result res and for
    //!          the intervals_copy vector.

    //! If intervals is empty, return a vector containing newInterval
    if (intervals.empty())
    {
        return {newInterval};
    }

    const auto num_intervals = static_cast<int>(intervals.size());

    int left {};
    int right {num_intervals - 1};

    //! Binary search to find the position to insert newInterval
    while (left <= right)
    {
        const int mid {left + (right - left) / 2};

        if (intervals[mid][0] < newInterval[0])
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    //! Insert newInterval at the found position
    auto intervals_copy = intervals;
    intervals_copy.insert(intervals_copy.begin() + left, newInterval);

    //! Merge overlapping intervals
    std::vector<std::vector<int>> res {};
    for (auto& interval : intervals_copy)
    {
        //! If res is empty or there is no overlap, add interval to result
        if (res.empty() || res.back()[1] < interval[0])
        {
            res.push_back(std::move(interval));
        }
        else
        {
            //! If there is overlap, update end of last interval in res to merge
            res.back()[1] = std::max(res.back()[1], interval[1]);
        }
    }

    return res;

} // static std::vector<std::vector<int>> insertDS2( ...

TEST(InsertTest, SampleTest1)
{
    const std::vector<std::vector<int>> intervals {{1, 3}, {6, 9}};
    const std::vector<int>              newInterval {2, 5};
    const std::vector<std::vector<int>> expected_output {{1, 5}, {6, 9}};

    EXPECT_EQ(expected_output, insertFA(intervals, newInterval));
    EXPECT_EQ(expected_output, insertDS1(intervals, newInterval));
    EXPECT_EQ(expected_output, insertDS2(intervals, newInterval));
}

TEST(InsertTest, SampleTest2)
{
    const std::vector<std::vector<int>> intervals {
        {1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    const std::vector<int> newInterval {4, 8};
    const std::vector<std::vector<int>> expected_output {
        {1, 2}, {3, 10}, {12, 16}};

    EXPECT_EQ(expected_output, insertFA(intervals, newInterval));
    EXPECT_EQ(expected_output, insertDS1(intervals, newInterval));
    EXPECT_EQ(expected_output, insertDS2(intervals, newInterval));
}

TEST(InsertTest, SampleTest3)
{
    const std::vector<std::vector<int>> intervals {{1, 5}};
    const std::vector<int> newInterval {0, 0};
    const std::vector<std::vector<int>> expected_output {{0, 0}, {1, 5}};

    EXPECT_NE(expected_output, insertFA(intervals, newInterval));
    EXPECT_EQ(expected_output, insertDS1(intervals, newInterval));
    EXPECT_EQ(expected_output, insertDS2(intervals, newInterval));
}
