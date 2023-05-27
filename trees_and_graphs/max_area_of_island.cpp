#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Helper function to check if current location is within the grid
static bool inGridFA(int                                  curr_row,
                     int                                  curr_col,
                     const std::vector<std::vector<int>>& grid)
{
    return curr_row >= 0 && curr_row < static_cast<int>(grid.size())
        && curr_col >= 0 && curr_col < static_cast<int>(grid.front().size());
}

//! @brief Recursive DFS helper to get area of island surrounding input location
//! @param[in]     curr_row Row of current location in grid
//! @param[in]     curr_col Col of current location in grid
//! @param[in]     grid     Reference to m x n binary matrix of land and water
//! @param[in,out] seen     Reference to m x n matrix of visited locations
//! @return Area of island 
static int dfsRecursiveFA(int                                  curr_row,
                          int                                  curr_col,
                          const std::vector<std::vector<int>>& grid,
                          std::vector<std::vector<bool>>&      seen)
{
    int curr_area {};

    seen[curr_row][curr_col] = true;

    static const std::vector<std::pair<int, int>> directions {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
    for (const auto& dir : directions)
    {
        const int neighbor_row {curr_row + dir.first};
        const int neighbor_col {curr_col + dir.second};

        if (inGridFA(neighbor_row, neighbor_col, grid)
            && not seen[neighbor_row][neighbor_col]
            && grid.at(neighbor_row).at(neighbor_col) == 1)
        {
            curr_area +=
                1 + dfsRecursiveFA(neighbor_row, neighbor_col, grid, seen);
        }
    }

    return curr_area;

} // static int dfsRecursiveFA( ...

//! @brief First attempt solution to get max area of an island in m x n grid
//! @param[in] grid m x n binary matrix where 1s represent land
//! @return Max area of an island in grid
static int maxAreaOfIslandFA(const std::vector<std::vector<int>>& grid)
{
    int max_area {};

    std::vector<std::vector<bool>> seen(
        grid.size(), std::vector<bool>(grid[0].size(), false));

    const auto nrows = static_cast<int>(grid.size());
    const auto ncols = static_cast<int>(grid.front().size());

    for (int row = 0; row < nrows; ++row)
    {
        for (int col = 0; col < ncols; ++col)
        {
            if (seen[row][col] || grid.at(row).at(col) == 0)
            {
                continue;
            }

            max_area =
                std::max(max_area, 1 + dfsRecursiveFA(row, col, grid, seen));
        }
    }

    return max_area;

} // static int maxAreaOfIslandFA( ...

TEST(MaxAreaOfIslandTest, SampleTest1)
{
    const std::vector<std::vector<int>> grid {
        {0,0,1,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,1,1,0,1,0,0,0,0,0,0,0,0},
        {0,1,0,0,1,1,0,0,1,0,1,0,0},
        {0,1,0,0,1,1,0,0,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0}};

    EXPECT_EQ(6, maxAreaOfIslandFA(grid));
}

TEST(MaxAreaOfIslandTest, SampleTest2)
{
    const std::vector<std::vector<int>> grid {{0,0,0,0,0,0,0,0}};

    EXPECT_EQ(0, maxAreaOfIslandFA(grid));
}