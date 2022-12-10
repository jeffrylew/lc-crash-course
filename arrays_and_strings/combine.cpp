#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

static std::vector<int> combine(std::vector<int> arr1, std::vector<int> arr2)
{
    //! @details Time and space complexity O(arr1.size() + arr2.size())
    //!          Space complexity constant if don't count output as extra space
    
    std::vector<int> ans {};

    int i = 0, j = 0;

    while (i < arr1.size() && j < arr2.size())
    {
        if (arr1[i] < arr2[j])
        {
            ans.push_back(arr1[i]);
            ++i;
        }
        else
        {
            ans.push_back(arr2[j]);
            ++j;
        }
    }
    
    while (i < arr1.size())
    {
        ans.push_back(arr1[i]);
        ++i;
    }
    
    while (j < arr2.size())
    {
        ans.push_back(arr2[j]);
        ++j;
    }

    return ans;

} // static std::vector<int> combine( ...

TEST(CombineTest, SampleTest)
{
    const std::vector<int> expected_output {1, 3, 4, 5, 6, 7, 20};

    const auto result = combine({1, 4, 7, 20}, {3, 5, 6});

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
}