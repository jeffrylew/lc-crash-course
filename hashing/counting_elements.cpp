#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_set>
#include <vector>

//! @brief First attempt solution to count elements x where x + 1 exists in arr
//! @param[in] arr Vector of integers
//! @return Number of elements x where x + 1 is also in arr
static int countElementsFA(std::vector<int> arr)
{
    //! @details Time complexity O(N). Creating set takes O(N) time and looping
    //!          over N integers to check if x + 1 is in the set takes N * O(1).
    //!          Overall, O(N) + N * O(1) = O(N) + O(N) = O(N)
    //!          Space complexity O(N) for storing each unique integer from arr.
    //!          In the worst case, all integers are unique. O(N) is an upper
    //!          bound - if U is the number of unique integers in arr then the
    //!          space complexity could be more accurately represented as O(U)

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

//! @brief Discussion solution using search with sorted array
//! @param[in] arr Vector of integers
//! @return Number of elements x where x + 1 is also in arr
static int countElementsDS(std::vector<int> arr)
{
    //! @details Time complexity O(N log N) for std::sort. Single pass through
    //!          arr has cost of O(N) so O(N log N) + O(N) = O(N log N)
    //!          Space complexity O(1)

    std::sort(arr.begin(), arr.end());

    int count {};
    int runLength {1};

    for (int i = 1; i < static_cast<int>(arr.size()); ++i)
    {
        if (arr[i - 1] != arr[i])
        {
            if (arr[i - 1] + 1 == arr[i])
            {
                count += runLength;
            }
            runLength = 0;
        }
        ++runLength;
    }

    return count;

} // static int countElementsDS( ...

TEST(CountElementsTest, SampleTest)
{
    EXPECT_EQ(2, countElementsFA({1, 2, 3}));
    EXPECT_EQ(2, countElementsDS({1, 2, 3}));
}
