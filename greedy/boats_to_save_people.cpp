#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Get fewest number of boats to carry everyone
//! @param[in] people Vector of weights for each person
//! @param[in] limit  Boat weight limit for two people
//! @return Fewest number of boats to carry everyone
static int numRescueBoats(std::vector<int> people, int limit)
{
    //! @details https://leetcode.com/problems/boats-to-save-people/
    //!
    //!          Time complexity O(N * log N) where N = people.size() for sort.
    //!          Two pointer implementation runs in O(N).
    //!          Space complexity O(log N) most likely due to stack space for
    //!          recursively implemented quick sort.

    int ans {};
    int lightest_idx {};
    int heaviest_idx {static_cast<int>(people.size()) - 1};
    std::sort(people.begin(), people.end());

    while (lightest_idx <= heaviest_idx)
    {
        if (people[lightest_idx] + people[heaviest_idx] <= limit)
        {
            ++lightest_idx;
        }
        
        --heaviest_idx;
        ++ans;
    }

    return ans;
}

TEST(NumRescueBoatsTest, SampleTest)
{
    EXPECT_EQ(1, numRescueBoats({1, 2}, 3));

    EXPECT_EQ(3, numRescueBoats({3, 2, 2, 1}, 3));

    EXPECT_EQ(4, numRescueBoats({3, 5, 3, 4}, 5));
}