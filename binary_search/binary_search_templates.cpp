#include <gtest/gtest.h>

#include <vector>

//! @brief Binary search template
//! @param[in] arr Sorted vector of integers
//! @return Index of target if in arr, else insertion index to maintain sorted
static int binarySearch(std::vector<int> arr, int target)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /710/binary-search/4696/
    //!
    //!          Time complexity O(log N) where N = arr.size()
    //!          Space complexity O(1)

    int left {};
    int right {static_cast<int>(arr.size()) - 1};

    while (left <= right)
    {
        const int mid {left + (right - left) / 2};

        if (arr[mid] == target)
        {
            //! Do something
            return mid;
        }

        if (arr[mid] > target)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    //! Target is not in arr but left is at the insertion point
    return left;

} // static int binarySearch( ...

//! @brief Get left-most index of target appearing multiple times in arr
//! @param[in] arr Sorted vector of integers containing duplicates
//! @return Left-most index of target if it appears multiple times
static int binarySearchFirstIndex(std::vector<int> arr, int target)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /710/binary-search/4696/

    int  left {};
    auto right = static_cast<int>(arr.size());

    while (left < right)
    {
        const int mid {left + (right - left) / 2};

        if (arr[mid] >= target)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left;

} // static int binarySearchFirstIndex( ...

TEST(BinarySearchTest, SampleTest)
{
    EXPECT_EQ(2, binarySearch({1, 2, 3, 4, 5}, 3));

    EXPECT_EQ(1, binarySearch({1, 3, 4, 5, 6}, 2));
}

TEST(BinarySearchFirstIndexTest, SampleTest)
{
    EXPECT_EQ(3, binarySearchFirstIndex({1, 2, 3, 4, 4}, 4));
}