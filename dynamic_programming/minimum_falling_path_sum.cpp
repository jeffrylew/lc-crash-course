#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <utility>
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

//! @brief Brute force discussion solution to get min sum of falling paths
//! @param[in] matrix Reference to n x n vector of ints
//! @return Minimum sum of any falling path through matrix
static int minFallingPathSumDS1(const std::vector<std::vector<int>>& matrix)
{
    //! @details leetcode.com/problems/minimum-falling-path-sum/editorial
    //!
    //!          Time complexity O(N * 3 ^ N) where N = matrix.size(). Solution
    //!          takes form of a 3-ary recursion tree where there are three
    //!          possibilities for every node in the tree. The max depth of the
    //!          recursion tree is equal to num rows in the matrix (= N). Each
    //!          level of the recursion tree contains approximately 3 ^ level
    //!          nodes so the max number of nodes at level N is ~3 ^ N. Thus the
    //!          time complexity is roughly O(N * 3 ^ N).
    //!          Space complexity O(N) for recursion stack space. The max depth
    //!          of the tree is N so will not have more than N recursive calls
    //!          on the call stack at any time.

    const auto num_rows = static_cast<int>(matrix.size());
    const auto num_cols = static_cast<int>(matrix[0].size());

    std::function<int(int, int)> findMinFallingPathSum = [&](int row, int col) {
        //! Check if outside the left or right matrix boundary
        if (col < 0 || col == num_cols)
        {
            return std::numeric_limits<int>::max();
        }

        //! Check if reached last row
        if (row == num_rows - 1)
        {
            return matrix[row][col];
        }

        //! Calculate min falling path sum starting from each possible next step
        const int left {findMinFallingPathSum(row + 1, col - 1)};
        const int middle {findMinFallingPathSum(row + 1, col)};
        const int right {findMinFallingPathSum(row + 1, col + 1)};

        return std::min({left, middle, right}) + matrix[row][col];
    };

    int minFallingSum {std::numeric_limits<int>::max()};
    for (int col = 0; col < num_cols; ++col)
    {
        minFallingSum = std::min(minFallingSum, findMinFallingPathSum(0, col));
    }

    return minFallingSum;

} // static int minFallingPathSumDS1( ...

//! @brief Top down dynamic programming discussion solution
//! @param[in] matrix Reference to n x n vector of ints
//! @return Minimum sum of any falling path through matrix
static int minFallingPathSumDS2(const std::vector<std::vector<int>>& matrix)
{
    //! @details leetcode.com/problems/minimum-falling-path-sum/editorial
    //!
    //!          Time complexity O(N ^ 2). For every cell in the matrix, compute
    //!          the result once and update memo. For subsequent calls, using
    //!          the stored results takes O(1). There are N^2 cells in matrix
    //!          and thus N^2 dp states.
    //!          Space complexity O(N ^ 2). The max depth of the tree is N so
    //!          can't have more than N recursive calls on the stack at any time
    //!          The 2D matrix memo uses O(N ^ 2) space.

    int minFallingSum {std::numeric_limits<int>::max()};

    std::vector<std::vector<std::optional<int>>> memo(
        matrix.size(),
        std::vector<std::optional<int>>(matrix[0].size(), std::nullopt));

    const auto num_rows = static_cast<int>(matrix.size());
    const auto num_cols = static_cast<int>(matrix[0].size());

    std::function<int(int, int)> findMinFallingPathSum = [&](int row, int col) {
        //! Base cases
        if (col < 0 || col == num_cols)
        {
            return std::numeric_limits<int>::max();
        }

        //! Check if reached last row
        if (row == num_rows - 1)
        {
            return matrix[row][col];
        }

        //! Check if results have been calculated before
        if (memo[row][col] != std::nullopt)
        {
            return memo[row][col].value_or(0);
        }

        //! Calculate min falling path sum starting from each possible next step
        const int left {findMinFallingPathSum(row + 1, col - 1)};
        const int middle {findMinFallingPathSum(row + 1, col)};
        const int right {findMinFallingPathSum(row + 1, col + 1)};

        const int minSum {std::min({left, middle, right}) + matrix[row][col]};
        return memo[row][col] = minSum;
    };

    //! Start DFS with memoization from each cell in top row
    for (int col = 0; col < num_cols; col++)
    {
        minFallingSum = std::min(minFallingSum, findMinFallingPathSum(0, col));
    }

    return minFallingSum;

} // static int minFallingPathSumDS2( ...

//! @brief Bottom up dynamic programming discussion solution
//! @param[in] matrix Reference to n x n vector of ints
//! @return Minimum sum of any falling path through matrix
static int minFallingPathSumDS3(const std::vector<std::vector<int>>& matrix)
{
    //! @details leetcode.com/problems/minimum-falling-path-sum/editorial
    //!
    //!          Time complexity O(N ^ 2) where N = matrix.size(). The nested
    //!          for loop takes N^2 to fill dp. It takes O(N) to find the MFP.
    //!          Space complexity O(N ^ 2) for dp 2D vector

    std::vector<std::vector<int>> dp(
        matrix.size() + 1U, std::vector(matrix.size() + 1U, 0));

    const auto num_rows = static_cast<int>(matrix.size());
    const auto num_cols = static_cast<int>(matrix[0].size());

    for (int row = num_rows - 1; row >= 0; --row)
    {
        for (int col = 0; col < num_cols; ++col)
        {
            if (col == 0)
            {
                dp[row][col] = std::min(dp[row + 1][col], dp[row + 1][col + 1])
                             + matrix[row][col];
            }
            else if (col == num_cols - 1)
            {
                dp[row][col] = std::min(dp[row + 1][col], dp[row + 1][col - 1])
                               + matrix[row][col];
            }
            else
            {
                dp[row][col] = std::min({dp[row + 1][col - 1],
                                         dp[row + 1][col],
                                         dp[row + 1][col + 1]})
                               + matrix[row][col];
            }
        }
    }

    int minFallingSum {std::numeric_limits<int>::max()};
    for (int col = 0; col < num_cols; ++col)
    {
        minFallingSum = std::min(minFallingSum, dp[0][col]);
    }

    return minFallingSum;

} // static int minFallingPathSumDS3( ...

//! @brief Space optimized bottom up dynamic programming discussion solution
//! @param[in] matrix Reference to n x n vector of ints
//! @return Minimum sum of any falling path through matrix
static int minFallingPathSumDS4(const std::vector<std::vector<int>>& matrix)
{
    //! @details leetcode.com/problems/minimum-falling-path-sum/editorial
    //!
    //!          Time complexity O(N ^ 2) where N = matrix.size(). The nested
    //!          loop takes N^2 time and it takes O(N) to find min falling path.
    //!          Space complexity O(N) for two 1D vectors dp and currentRow

    const auto num_rows = static_cast<int>(matrix.size());
    const auto num_cols = static_cast<int>(matrix[0].size());

    std::vector<int> dp(matrix[0].size() + 1U, 0);
    
    for (int row = num_rows - 1; row >= 0; --row)
    {
        std::vector<int> currentRow(matrix[0].size() + 1U, 0);

        for (int col = 0; col < num_cols; ++col)
        {
            if (col == 0)
            {
                currentRow[col] =
                    std::min(dp[col], dp[col + 1]) + matrix[row][col];
            }
            else if (col == num_cols - 1)
            {
                currentRow[col] =
                    std::min(dp[col - 1], dp[col]) + matrix[row][col];
            }
            else
            {
                currentRow[col] = std::min({dp[col - 1], dp[col], dp[col + 1]})
                                  + matrix[row][col];
            }
        }

        dp = std::move(currentRow);
    }

    int minFallingSum {std::numeric_limits<int>::max()};
    for (int col = 0; col < num_cols; ++col)
    {
        minFallingSum = std::min(minFallingSum, dp[col]);
    }

    return minFallingSum;

} // static int minFallingPathSumDS4( ...

TEST(MinFallingPathSumTest, SampleTest1)
{
    const std::vector<std::vector<int>> matrix {
        {2, 1, 3}, {6, 5, 4}, {7, 8, 9}};

    EXPECT_EQ(13, minFallingPathSumFA(matrix));
    EXPECT_EQ(13, minFallingPathSumDS1(matrix));
    EXPECT_EQ(13, minFallingPathSumDS2(matrix));
    EXPECT_EQ(13, minFallingPathSumDS3(matrix));
    EXPECT_EQ(13, minFallingPathSumDS4(matrix));
}

TEST(MinFallingPathSumTest, SampleTest2)
{
    const std::vector<std::vector<int>> matrix {{-19, 57}, {-40, -5}};

    EXPECT_EQ(-59, minFallingPathSumFA(matrix));
    EXPECT_EQ(-59, minFallingPathSumDS1(matrix));
    EXPECT_EQ(-59, minFallingPathSumDS2(matrix));
    EXPECT_EQ(-59, minFallingPathSumDS3(matrix));
    EXPECT_EQ(-59, minFallingPathSumDS4(matrix));
}
