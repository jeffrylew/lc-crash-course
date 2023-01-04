#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <tuple>
#include <unordered_set>

//! @brief Find number of jewels in stones
//! @param[in] jewels String representing types of stones that are jewels
//! @param[in] stones String representing stones
//! @return Number of jewels
static int numJewelsInStones(std::string jewels, std::string stones)
{
    //! @details https://leetcode.com/problems/jewels-and-stones/solutions/
    //!          127766/official-solution/
    //!
    //!          Let J = jewels.size() and S = stones.size()
    //!          Time complexity O(J + S)
    //!          Space complexity O(J)

    std::unordered_set<char> jewel_set {};
    for (const char c : jewels)
    {
        std::ignore = jewel_set.emplace(c);
    }

    return std::count_if(stones.cbegin(),
                         stones.cend(),
                         [&](char c) -> bool {
                            return jewel_set.count(c) > 0;
                         });

} // static int numJewelsInStones( ...

TEST(NumJewelsInStonesTest, SampleTest)
{
    EXPECT_EQ(3, numJewelsInStones("aA", "aAAbbbb"));
}