#include <gtest/gtest.h>

#include <unordered_set>
#include <vector>

//! @brief First attempt solution to count elements x where x + 1 exists in arr
//! @param[in] arr Vector of integers
//! @return Number of elements x where x + 1 is also in arr
static int countElementsFA(std::vector<int> arr)
{
    int num_elements {};

    const std::unordered_set<int> unique_nums(arr.begin(), arr.end());

    for (const auto num : arr)
    {
        if (unique_nums.count(num + 1) > 0)
        {
            ++num_elements;
        }
    }

    return num_elements;

} // static int countElementsFA( ...

TEST(CountElementsTest, SampleTest)
{
    EXPECT_EQ(2, countElementsFA({1, 2, 3}));
}
