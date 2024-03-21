#include <gtest/gtest.h>

#include <functional>
#include <vector>

//! @brief Get number of unique paths from top left to bottom right corner
//! @param[in] m One dimension of an m x n grid
//! @param[in] n Another dimension of an m x n grid
//! @return Number of unique paths to bottom right by only moving down or right
static int uniquePathsTopDown(int m, int n)
{
    //! @details https://leetcode.com/problems/unique-paths/description/
    //!
    //!          Time complexity O(n * m) since work done at each state is O(1)
    //!          Space complexity O(n * m) for memo

    std::vector<std::vector<int>> memo(m, std::vector(n, -1));

    //! dp(row, col) gets number of unique paths from (0, 0) to (row, col)
    std::function<int(int, int)> dp = [&](int row, int col) {
        if (row + col == 0)
        {
            //! Base case: Only one way to get to (0, 0) - by starting there
            return 1;
        }

        if (memo[row][col] != -1)
        {
            return memo[row][col];
        }

        int num_ways {};
        if (row > 0)
        {
            //! Square above
            num_ways += dp(row - 1, col);
        }

        if (col > 0)
        {
            //! Square to the left
            num_ways += dp(row, col - 1);
        }

        return memo[row][col] = num_ways;
    };

    return dp(m - 1, n - 1);

} // static int uniquePathsTopDown( ...

//! @brief First bottom up dynamic programming discussion solution
//! @param[in] m One dimension of an m x n grid
//! @param[in] n Another dimension of an m x n grid
//! @return Number of unique paths to bottom right by only moving down or right
static int uniquePathsBottomUpDS1(int m, int n)
{
    //! @details https://leetcode.com/problems/unique-paths/description/
    //!
    //!          Time complexity O(n * m) since work done at each state is O(1)
    //!          Space complexity O(n * m) for memo

    std::vector<std::vector<int>> dp(m, std::vector(n, 0));
    dp[0][0] = 1;

    for (int row = 0; row < m; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            if (row > 0)
            {
                //! Square above
                dp[row][col] += dp[row - 1][col];
            }

            if (col > 0)
            {
                //! Square to the left
                dp[row][col] += dp[row][col - 1];
            }
        }
    }

    return dp[m - 1][n - 1];

} // static int uniquePathsBottomUpDS1( ...

//! @brief Space-optimized bottom up dynamic programming discussion solution
//! @param[in] m One dimension of an m x n grid
//! @param[in] n Another dimension of an m x n grid
//! @return Number of unique paths to bottom right by only moving down or right
static int uniquePathsBottomUpDS2(int m, int n)
{
    //! @details https://leetcode.com/problems/unique-paths/description/
    //!
    //!          Time complexity O(n * m) since work done at each state is O(1)
    //!          Space complexity O(n)

    std::vector<int> dp(n, 0);
    dp[0] = 1;

    for (int row = 0; row < m; ++row)
    {
        std::vector<int> next_row(n, 0);

        for (int col = 0; col < n; ++col)
        {
            next_row[col] += dp[col];

            if (col > 0)
            {
                next_row[col] += next_row[col - 1];
            }
        }

        dp = std::move(next_row);
    }

    return dp[n - 1];

} // static int uniquePathsBottomUpDS2( ...

TEST_CASE(UniquePathsTest, SampleTest1)
{
    EXPECT_EQ(28, uniquePathsTopDown(3, 7));
    EXPECT_EQ(28, uniquePathsBottomUpDS1(3, 7));
    EXPECT_EQ(28, uniquePathsBottomUpDS2(3, 7));
}

TEST_CASE(uniquePathsTest, SampleTest2)
{
    EXPECT_EQ(3, uniquePathsTopDown(3, 2));
    EXPECT_EQ(3, uniquePathsBottomUpDS1(3, 2));
    EXPECT_EQ(3, uniquePathsBottomUpDS2(3, 2));
}
