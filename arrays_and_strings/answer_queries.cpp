#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

static std::vector<bool> answerQueries(std::vector<int>              nums,
                                       std::vector<std::vector<int>> queries,
                                       int                           limit)
{
    //! @details Time complexity O(N + M) where N = nums.size() and M = queries
    //!          size. With prefix sum, costs O(N) to build but answering each
    //!          query is O(1). Without prefix sum, each query would be O(N * M)
    //!          in the worst case.
    //!          Space complexity O(N) to build prefix sum

    std::vector<int> prefix = {nums[0]};
    for (int i = 1; i < static_cast<int>(nums.size()); ++i)
    {
        prefix.push_back(prefix.back() + nums[i]);
    }

    std::vector<bool> ans {};
    for (const auto& query : queries)
    {
        int x {query[0]};
        int y {query[1]};
        int curr {prefix[y] - prefix[x] + nums[x]};
        ans.push_back(curr < limit);
    }

    return ans;

} // static std::vector<bool> answerQueries( ...

TEST(AnswerQueriesTest, SampleTest)
{
    const std::vector<bool> expected_output {true, false, true};

    const auto result = answerQueries({1, 6, 3, 2, 7, 2},
                                      {{0, 3},
                                       {2, 5},
                                       {2, 4}},
                                      13);
    
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
}