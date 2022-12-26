#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <vector>

//! @brief Return sorted vector with all numbers that appear in all n vectors
//! @param[in] nums 2D vector containing n vectors of distinct integers
//! @return Sorted vector containing all numbers appearing in all n vectors
static std::vector<int> intersection(std::vector<std::vector<int>> nums)
{
    //! @details Time complexity O(M * (N + log M)) for N lists with each having
    //!          an average of M elements. To populate the hash map, it costs
    //!          O(N * M). Then, there can be at most M elements inside ans so
    //!          in the worst case the sort will cost O(M log M). Thus, we have
    //!          O(N * M + M log M) = O(M * (N + log M))
    //!          Space complexity O(N * M) for hash map size if every element
    //!          in input is unique

    std::unordered_map<int, int> counts {};
    for (const auto& arr : nums)
    {
        for (int x : arr)
        {
            ++counts[x];
        }
    }

    const auto       n = static_cast<int>(nums.size());
    std::vector<int> ans {};
    /*
    for (auto [key, val] : counts)
    {
        if (val == n)
        {
            ans.push_back(key);
        }
    }
    */
    for (const auto& kv : counts)
    {
        if (kv.second == n)
        {
            ans.push_back(kv.first);
        }
    }

    std::sort(ans.begin(), ans.end());
    return ans;

} // static std::vector<int> intersection( ...

TEST(IntersectionTest, SampleTest)
{
    const std::vector<int> expected_output {3, 4};

    const auto result = intersection({{3, 1, 2, 4, 5},
                                      {1, 2, 3, 4},
                                      {3, 4, 5, 6}});
                                      
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
}