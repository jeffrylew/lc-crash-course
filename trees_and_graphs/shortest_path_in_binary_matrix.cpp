#include <gtest/gtest.h>

#include <queue>
#include <vector>

//! @brief Helper function to determine if location (row, col) is 0 and in grid
//! @param[in] row Current row
//! @param[in] col Current column
//! @param[in] grid Reference to n x n binary matrix grid
//! @return True if (row, col) is a valid location within grid and equals 0
static bool valid(int                                  row,
                  int                                  col,
                  const std::vector<std::vector<int>>& grid)
{
    const auto grid_size = static_cast<int>(grid.size());

    return 0 <= row        //
        && row < grid_size //
        && 0 <= col        //
        && col < grid_size //
        && grid.at(row).at(col) == 0;
}

//! @brief Get length of shortest path from (0, 0) to (n - 1, n - 1) of zeros
//! @param[in] grid Reference to n x n binary matrix grid
//! @return Shortest clear path, else -1 if no clear path exists
static int shortestPathBinaryMatrix(const std::vector<std::vector<int>>& grid)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /707/traversals-trees-graphs/4631/
    //!
    //!          Time complexity O(N^2). If queue implementation is efficient
    //!          then removing from the left is O(1) and the work at each node
    //!          is O(1). Then the time complexity is equal to the number of
    //!          nodes.
    //!          Space complexity O(N^2) for seen.

    if (grid.at(0).at(0) == 1)
    {
        return -1;
    }

    const auto n = static_cast<int>(grid.size());

    std::vector<std::vector<bool>> seen(
        grid.size(), std::vector<bool>(grid.front().size(), false));
    seen[0][0] = true;
    
    std::queue<std::vector<int>> queue {};
    queue.push({0, 0, 1}); // row, col, steps

    static const std::vector<std::vector<int>> directions {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    while (not queue.empty())
    {
        const auto [row, col, steps] = queue.front();
        queue.pop();

        if (row == n - 1 && col == n - 1)
        {
            return steps;
        }

        for (const auto& direction : directions)
        {
            const int nextRow {row + direction.front()};
            const int nextCol {col + direction.back()};

            if (valid(nextRow, nextCol, grid) && not seen[nextRow][nextCol])
            {
                seen[nextRow][nextCol] = true;
                queue.push({nextRow, nextCol, steps + 1});
            }
        }
    }

    return -1;

} // static int shortestPathBinaryMatrix( ...

TEST(ShortestPathBinaryMatrixTest, SampleTest)
{
    const std::vector<std::vector<int>> grid {
        {0, 0, 1, 1, 1, 1},
        {0, 1, 0, 1, 1, 1},
        {0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 0}};
    
    EXPECT_EQ(7, shortestPathBinaryMatrix(grid));
}