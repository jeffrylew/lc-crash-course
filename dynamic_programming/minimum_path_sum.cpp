#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <limits>
#include <vector>

//! @brief Get top left to bottom right path that minimizes sum of numbers
//! @param[in] grid Reference to 2D vector for m x n grid of non-negative ints
//! @return Minimum path sum
static int minPathSumDS1(const std::vector<std::vector<int>>& grid)
{
    //! @details https://leetcode.com/problems/minimum-path-sum/
    //!
    //!          Time complexity O(m * n)
    //!          Space complexity O(m * n)

    const auto num_rows = static_cast<int>(grid.size());
    const auto num_cols = static_cast<int>(grid[0].size());

    std::vector<std::vector<int>> memo(
        grid.size(), std::vector(grid[0].size(), -1));

    std::function<int(int, int)> dp = [&](int row, int col) {
        if (row + col == 0)
        {
            //! Base case
            return grid[row][col];
        }

        if (memo[row][col] != -1)
        {
            return memo[row][col];
        }

        int min_sum {std::numeric_limits<int>::max()};
        if (row > 0)
        {
            min_sum = std::min(min_sum, dp(row - 1, col));
        }

        if (col > 0)
        {
            min_sum = std::min(min_sum, dp(row, col - 1));
        }

        return memo[row][col] = grid[row][col] + min_sum;
    };

    return dp(num_rows - 1, num_cols - 1);

} // static int minPathSumDS1( ...

//! @brief Bottom up dynamic programming solution that minimizes sum of numbers
//! @param[in] grid Reference to 2D vector for m x n grid of non-negative ints
//! @return Minimum path sum from top left to bottom right
static int minPathSumDS2(const std::vector<std::vector<int>>& grid)
{
    const auto num_rows = static_cast<int>(grid.size());
    const auto num_cols = static_cast<int>(grid[0].size());

    std::vector<std::vector<int>> dp(num_rows, std::vector(num_cols, 0));
    dp[0][0] = grid[0][0];

    for (int row = 0; row < num_rows; ++row)
    {
        for (int col = 0; col < num_cols; ++col)
        {
            if (row + col == 0)
            {
                continue;
            }

            int min_sum {std::numeric_limits<int>::max()};
            if (row > 0)
            {
                min_sum = std::min(min_sum, dp[row - 1][col]);
            }

            if (col > 0)
            {
                min_sum = std::min(min_sum, dp[row][col - 1]);
            }

            dp[row][col] = grid[row][col] + min_sum;
        }
    }

    return dp[num_rows - 1][num_cols - 1];

} // static int minPathSumDS2( ...

TEST(MinPathSumTest, SampleTest1)
{
    const std::vector<std::vector<int>> grid {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};

    EXPECT_EQ(7, minPathSumDS1(grid));
    EXPECT_EQ(7, minPathSumDS2(grid));
}

TEST(MinPathSumTest, SampleTest2)
{
    const std::vector<std::vector<int>> grid {{1, 2, 3}, {4, 5, 6}};

    EXPECT_EQ(12, minPathSumDS1(grid));
    EXPECT_EQ(12, minPathSumDS2(grid));
}
