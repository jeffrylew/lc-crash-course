#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <vector>

//! @brief First attempt solution to find players with zero or one losses
//! @param[in] matches Vector of matches
//! @return List of players who have not lost and list of players that lost once
static std::vector<std::vector<int>> findWinnersFA(
    std::vector<std::vector<int>> matches)
{
    std::vector<std::vector<int>> ans(2ULL, std::vector<int>{});
    std::unordered_map<int, int>  losses {};
    
    for (const auto& vec : matches)
    {
        const auto& winner = vec.front();
        const auto& loser  = vec.back();
        
        losses[winner] += 0;
        ++losses[loser];
    }
    
    for (const auto& kv : losses)
    {
        if (kv.second == 0)
        {
            ans.front().emplace_back(kv.first);
        }
        else if (kv.second == 1)
        {
            ans.back().emplace_back(kv.first);
        }
    }
    
    std::sort(ans.front().begin(), ans.front().end());
    std::sort(ans.back().begin(), ans.back().end());
    return ans;

} // static std::vector<std::vector<int>> findWinnersFA( ...

TEST(FindWinnersTest, SampleTest)
{
    const std::vector<std::vector<int>> input {{1, 3},
                                               {2, 3},
                                               {3, 6},
                                               {5, 6},
                                               {5, 7},
                                               {4, 5},
                                               {4, 8},
                                               {4, 9},
                                               {10, 4},
                                               {10, 9}};

    const std::vector<int> expected_output1 {1, 2, 10};
    const std::vector<int> expected_output2 {4, 5, 7, 8};
    
    const auto resultFA = findWinnersFA(input);

    EXPECT_TRUE(std::equal(expected_output1.cbegin(),
                           expected_output1.cend(),
                           resultFA.front().cbegin()));
    EXPECT_TRUE(std::equal(expected_output2.cbegin(),
                           expected_output2.cend(),
                           resultFA.back().cbegin()));
}