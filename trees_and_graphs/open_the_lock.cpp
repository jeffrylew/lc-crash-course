#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

//! @brief Helper function generates all strings that differ in one position by
//!        a value of one from node
//! @param[in] node std::string representation of a number in [0, 9999] 
//! @return Vector of strings for numbers that differ by one in one position
static std::vector<std::string> neighbors(std::string node)
{
    std::vector<std::string> ans {};

    for (int i = 0; i < 4; ++i)
    {
        const auto num = static_cast<int>(node[i]);
        for (const int change : {-1, 1})
        {
            //! Handle wrap-around case
            //! decrement(x) = (x - 1) % 10, decrement(0) = 9
            //! increment(x) = (x + 1) % 10, increment(9) = 0
            const int x {
                (num - static_cast<int>('0') + change) % 10
                + static_cast<int>('0')};
            std::string neighbor = node;
            neighbor[i]          = x;
            ans.push_back(std::move(neighbor));
        }
    }

    return ans;
}

//! @brief Get min moves to make lock read target
//! @param[in] deadends Vector of blocked codes - lock can no longer turn
//! @param[in] target   Target combination
//! @return Minimum number of moves to make lock read target
static int openLock(
    const std::vector<std::string>& deadends, std::string target)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /707/traversals-trees-graphs/4635/
    //!
    //!          Time complexity O(d) where d = deadends.length for converting
    //!          deadends into a set. Everything else in the problem is constant
    //!          (4 slots, 10 digits). However, if the lock had N slots then the
    //!          time complexity would be generally be O(10^N * N^2 + d). There
    //!          are 10^N different states because each slot has 10 options.
    //!          At each state, we generally perform O(N^2) work because we loop
    //!          over the N slots while performing string concatenation, which
    //!          is O(N) for immutable strings. However, for the C++ solution
    //!          below, the time complexity is O(10^N * N + d) since the string
    //!          concatenation is avoided.
    //!          Space complexity O(d) for deadends set

    if (std::find(deadends.cbegin(), deadends.cend(), "0000")
        != deadends.cend())
    {
        return -1;
    }

    std::queue<std::pair<std::string, int>> queue {};
    queue.emplace("0000", 0);
    std::unordered_set<std::string> seen(deadends.begin(), deadends.end());

    while (!queue.empty())
    {
        const auto [node, steps] = queue.front();
        queue.pop();

        if (node == target)
        {
            return steps;
        }

        for (const auto& neighbor : neighbors(node))
        {
            if (seen.find(neighbor) == seen.end())
            {
                seen.insert(neighbor);
                queue.emplace(neighbor, steps + 1);
            }
        }
    }

    return -1;
}

TEST(OpenLockTest, SampleTest1)
{
    EXPECT_EQ(6, openLock({"0201", "0101", "0102", "1212", "2002"}, "0202"));
}