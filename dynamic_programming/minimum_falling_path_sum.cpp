#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <vector>

//! @brief First attempt solution to get min sum of falling paths through matrix
//! @param[in] matrix Reference to n x n vector of ints
//! @return Minimum sum of any falling path through matrix
static int minFallingPathSumFA(const std::vector<std::vector<int>>& matrix)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /712/dynamic-programming/4586/
    //!
    //!          Time complexity O(n * n) where n = matrix.size()
    //!          Space complexity O(n) for dp_row_min_sum and curr_row_min_sum

    const auto num_rows = static_cast<int>(matrix.size());
    const auto num_cols = static_cast<int>(matrix[0].size());

    //! Minimum sum for each element in row
    auto dp_row_min_sum = matrix[0];

    for (int row = 1; row < num_rows; ++row)
    {
        //! Minimum sum for each element in current row
        auto curr_row_min_sum = matrix[row];

        for (int col = 0; col < num_cols; ++col)
        {
            //! Minimum value in previous row for current position (row, col)
            int prev_min {std::numeric_limits<int>::max()};

            if (col > 0)
            {
                prev_min = std::min(prev_min, dp_row_min_sum[col - 1]);
            }
            prev_min = std::min(prev_min, dp_row_min_sum[col]);
            if (col < num_cols - 1)
            {
                prev_min = std::min(prev_min, dp_row_min_sum[col + 1]);
            }

            curr_row_min_sum[col] += prev_min;
        }

        dp_row_min_sum = curr_row_min_sum;
    }

    return *std::min_element(dp_row_min_sum.begin(), dp_row_min_sum.end());

} // static int minFallingPathSumFA( ...

TEST(MinFallingPathSumTest, SampleTest1)
{
    const std::vector<std::vector<int>> matrix {
        {2, 1, 3}, {6, 5, 4}, {7, 8, 9}};

    EXPECT_EQ(13, minFallingPathSumFA(matrix));
}

TEST(MinFallingPathSumTest, SampleTest2)
{
    const std::vector<std::vector<int>> matrix {{-19, 57}, {-40, -5}};

    EXPECT_EQ(-59, minFallingPathSumFA(matrix));
}
