#include <gtest/gtest.h>

#include <algorithm>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
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

//! @brief First discussion solution to find players with zero or one losses
//! @param[in] matches Vector of matches
//! @return List of players who have not lost and list of players that lost once
static std::vector<std::vector<int>> findWinnersDS1(
    std::vector<std::vector<int>> matches)
{
    //! @details https://leetcode.com/problems/
    //!          find-players-with-zero-or-one-losses/solutions/2655744/
    //!          find-players-with-zero-or-one-losses/
    //!
    //!          Time complexity O(N log N), N = matches.size(). Iteration over
    //!          matches takes O(N) and need to store/sort players in two arrays
    //!          where worst case is O(N) players in them.
    //!          Space complexity O(N) for hash set/map with O(N) players

    std::unordered_set<int> seen {};
    std::unordered_map<int, int> lossesCount {};

    for (const auto& match : matches)
    {
        const int winner = match[0];
        const int loser  = match[1];
        std::ignore = seen.insert(winner);
        std::ignore = seen.insert(loser);
        ++lossesCount[loser];
    }

    //! Add players with 0 or 1 loss to corresponding list
    std::vector<std::vector<int>> answer(2ULL, std::vector<int>{});
    for (const auto player : seen)
    {
        if (lossesCount.find(player) == lossesCount.end())
        {
            answer[0].push_back(player);
        }
        else if (lossesCount[player] == 1)
        {
            answer[1].push_back(player);
        }
    }

    std::sort(answer[0].begin(), answer[0].end());
    std::sort(answer[1].begin(), answer[1].end());
    return answer;

} // static std::vector<std::vector<int>> findWinnersDS1( ...

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
    
    const auto resultDS1 = findWinnersDS1(input);

    EXPECT_TRUE(std::equal(expected_output1.cbegin(),
                           expected_output1.cend(),
                           resultDS1.front().cbegin()));
    EXPECT_TRUE(std::equal(expected_output2.cbegin(),
                           expected_output2.cend(),
                           resultDS1.back().cbegin()));
}