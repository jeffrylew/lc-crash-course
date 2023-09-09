#include <gtest/gtest.h>

#include <vector>

//! @brief Determine if target is in matrix
//! @param[in] matrix Rows in non-decreasing order, top to bottom
//! @return True if target is in matrix, else false
static bool searchMatrix(
    const std::vector<std::vector<int>>& matrix, int target)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /710/binary-search/4532/
    //!
    //!          Time complexity O(M * N) where M = nrows and N = ncols
    //!          Space complexity O(1)

    const auto nrows = static_cast<int>(matrix.size());    // = m
    const auto ncols = static_cast<int>(matrix[0].size()); // = n

    int left {};
    int right {nrows * ncols - 1};

    while (left <= right)
    {
        const int mid {left + (right - left) / 2};
        const int row {mid / ncols};
        const int col {mid % ncols};
        const int num {matrix[row][col]};

        if (num == target)
        {
            return true;
        }

        if (num < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return false;

} // static bool searchMatrix( ...

TEST(SearchMatrixTest, SampleTest)
{
    const std::vector<std::vector<int>> input {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}};
    
    EXPECT_TRUE(searchMatrix(input, 3));
}