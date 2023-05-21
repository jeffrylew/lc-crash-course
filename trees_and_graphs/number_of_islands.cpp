#include <gtest/gtest.h>

#include <stack>
#include <vector>

//! @brief Helper function to check if location is in bounds and if node is land
//! @param[in] row   Current row
//! @param[in] col   Current column
//! @param[in] nrows Total rows in input grid
//! @param[in] ncols Total columns in input grid
//! @param[in] grid  Reference to input m x n map of 1 (land) and 0 (water)
//! @return True if current node at (row, col) is in bounds and is land
static bool isValid(int                                  row,
                    int                                  col,
                    int                                  nrows,
                    int                                  ncols,
                    const std::vector<std::vector<int>>& grid)
{
    return 0 <= row
        && row < nrows
        && 0 <= col
        && col < ncols
        && grid.at(row).at(col) == 1;
}

//! @brief Recursive dfs helper to find connected adjacent lands in an island
//! @param[in]     row   Current row
//! @param[in]     col   Current column
//! @param[in]     nrows Total rows in input grid
//! @param[in]     ncols Total columns in input grid
//! @param[in,out] seen  Reference to matrix of nodes in grid that were visited
//! @param[in]     grid  Reference to input m x n map of 1 (land) and 0 (water)
static void dfsRecursive(int                                  row,
                         int                                  col,
                         int                                  nrows,
                         int                                  ncols,
                         std::vector<std::vector<bool>>&      seen,
                         const std::vector<std::vector<int>>& grid)
{
    static const std::vector<std::vector<int>> directions {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    for (const auto& direction : directions)
    {
        const int nextRow = row + direction[0];
        const int nextCol = col + direction[1];

        if (isValid(nextRow, nextCol, nrows, ncols, grid)
            && not seen[nextRow][nextCol])
        {
            seen[nextRow][nextCol] = true;
            dfsRecursive(nextRow, nextCol, nrows, ncols, grid);
        }
    }
}

//! @brief Iterative dfs helper to find connected adjacent lands in an island
//! @param[in]     srow  Current row to start dfs from
//! @param[in]     scol  Current column to start dfs from
//! @param[in]     nrows Total rows in input grid
//! @param[in]     ncols Total columns in input grid
//! @param[in,out] seen  Reference to matrix of nodes in grid that were visited
//! @param[in]     grid  Reference to input m x n map of 1 (land) and 0 (water)
static void dfsIterative(int                                  srow,
                         int                                  scol,
                         int                                  nrows,
                         int                                  ncols,
                         std::vector<std::vector<bool>>&      seen,
                         const std::vector<std::vector<int>>& grid)
{
    static const std::vector<std::vector<int>> directions {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    std::stack<std::pair<int, int>> stack {};
    stack.emplace(srow, scol);

    while (not stack.empty())
    {
        const auto [row, col] = stack.top();
        stack.pop();

        for (const auto& direction : directions)
        {
            const int nextRow = row + direction[0];
            const int nextCol = col + direction[1];

            if (isValid(nextRow, nextCol, nrows, ncols, grid)
                && not seen[nextRow][nextCol])
            {
                seen[nextRow][nextCol] = true;
                stack.emplace(nextRow, nextCol);
            }
        }
    }
}

//! @brief Get number of islands from m x n grid of 1 (land) and 0 (water)
//! @param[in] grid m x n 2D grid containing map of 1 (land) and 0 (water)
//! @return Number of islands (adjacent lands horizontally or vertically)
static int numIslands(const std::vector<std::vector<int>>& grid)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /707/traversals-trees-graphs/4626/
    //!
    //!          Time complexity O(nrows * ncols). DFS on a graph has a time
    //!          complexity of O(nodes + edges) when we don't know how many
    //!          edges a node can have. However, this problem defines a node can
    //!          have at most 4 edges so the work done at each node is O(1). We
    //!          only visit each node once so the time complexity is equal to
    //!          the number of nodes, which is O(nrows * ncols)
    //!
    //!          Space complexity O(nrows * ncols) for seen matrix

    const auto nrows = static_cast<int>(grid.size());
    const auto ncols = static_cast<int>(grid[0].size()); // Assume nrows >= 1

    std::vector<std::vector<bool>> seen(
        grid.size(), std::vector<bool>(grid[0].size(), false));

    int ans {};

    for (int row = 0; row < nrows; ++row)
    {
        for (int col = 0; col < ncols; ++col)
        {
            if (grid[row][col] == 1 && not seen[row][col])
            {
                ++ans;
                seen[row][col] = true;
                dfsRecursive(row, col, nrows, ncols, seen, grid);
                // dfsIterative(row, col, nrows, ncols, seen, grid);
            }
        }
    }

    return ans;
}

TEST(NumIslandsTest, SampleTest)
{
    const std::vector<std::vector<int>> grid {
        {1, 1, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0, 1}};
    
    EXPECT_EQ(4, numIslands(grid));
}