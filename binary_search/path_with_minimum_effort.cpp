#include <gtest/gtest.h>

#include <algorithm>
#include <stack>
#include <utility>
#include <vector>

//! @brief Determine if (row, col) is a valid location in a grid (nrows, ncols)
//! @param[in] row   Current row to validate
//! @param[in] col   Current col to validate
//! @param[in] nrows Number of rows (= heights.size())
//! @param[in] ncols Number of cols (= heights[0].size())
//! @return True if (row, col) is a valid location, else false
static bool valid(int row, int col, int nrows, int ncols)
{
    return 0 <= row && row < nrows && 0 <= col && col < ncols;
}

//! @brief Check if top left-bottom right path can be traveled with effort
//! @param[in] effort  Largest absolute difference between two consecutive cells
//! @param[in] heights Positive 2D grid of size m x n, heights[r][c] = height
//! @return True if can travel from top left to bottom right with effort
static bool check(int effort, const std::vector<std::vector<int>>& heights)
{
    std::vector<std::vector<bool>> seen(
        heights.size(), std::vector<bool>(heights.front().size(), false));
    seen[0][0] = true;

    std::stack<std::pair<int, int>> stack({{0, 0}});

    static const std::vector<std::pair<int, int>> directions {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    const auto nrows = static_cast<int>(heights.size());
    const auto ncols = static_cast<int>(heights.front().size());
    
    while (not stack.empty())
    {
        const auto [row, col] = stack.top();
        stack.pop();

        if (row == nrows - 1 && col == ncols - 1)
        {
            return true;
        }

        for (const auto& direction : directions)
        {
            const int nextRow {row + direction.first};
            const int nextCol {col + direction.second};

            if (valid(nextRow, nextCol, nrows, ncols)
                && not seen[nextRow][nextCol])
            {
                if (std::abs(heights[nextRow][nextCol] - heights[row][col])
                    <= effort)
                {
                    seen[nextRow][nextCol] = true;
                    stack.emplace(nextRow, nextCol);
                }
            }
        }
    }

    return false;

} // static bool check( ...

//! @brief Get minimum effort required to travel from top left to bottom right
//! @param[in] heights Positive 2D vector of size m x n (nrows x ncols)
//! @return Minimum effort to travel from top left to bottom right of heights
static int minimumEffortPath(const std::vector<std::vector<int>>& heights)
{
    //! @details leetcode.com/problems/path-with-minimum-effort/description
    //!
    //!          Time complexity O(m * n * log k). DFS runs in O(m * n) and the
    //!          binary search runs in O(log k).
    //!          Space complexity O(m * n) for stack and seen to perform DFS.

    int left {};
    int right {};

    for (const auto& row : heights)
    {
        right = std::max(right, *std::max_element(row.cbegin(), row.cend()));
    }

    while (left <= right)
    {
        const int mid {left + (right - left) / 2};

        if (check(mid, heights))
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left;

} // static int minimumEffortPath( ...

TEST(MinimumEffortPathTest, SampleTest)
{
    const std::vector<std::vector<int>> heights {
        {1, 2, 2}, {3, 8, 2}, {5, 3, 5}};

    EXPECT_EQ(2, minimumEffortPath(heights));
}