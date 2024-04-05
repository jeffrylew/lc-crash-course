#include <gtest/gtest.h>

#include <functional>
#include <vector>

//! @brief First attempt to get number of unique paths to bottom right corner
//! @param[in] obstacleGrid Reference to m x n int grid with obstacle = 1
//! @return Number of unique paths from top left to bottom right corner
static int uniquePathsWithObstaclesFA(
    const std::vector<std::vector<int>>& obstacleGrid)
{
    //! If (0, 0) is an obstacle then cannot reach bottom right corner
    if (obstacleGrid[0][0] == 1)
    {
        return 0;
    }

    //! Keep track of number of unique paths for each (row, col) in obstacleGrid
    std::vector<std::vector<int>> memo_num_paths(
        obstacleGrid.size(), std::vector<int>(obstacleGrid[0].size(), -1));

    const auto num_rows = static_cast<int>(obstacleGrid.size());
    const auto num_cols = static_cast<int>(obstacleGrid[0].size());

    //! Get number of unique paths to (row, col)
    std::function<int(int, int)> get_num_paths = [&](int row, int col) {
        //! One valid path from (0, 0) to (0, 0)
        if (row + col == 0)
        {
            return 1;
        }

        //! No valid paths if obstacle at (row, col)
        if (obstacleGrid[row][col] == 1)
        {
            return 0;
        }

        if (memo_num_paths[row][col] != -1)
        {
            return memo_num_paths[row][col];
        }

        int num_paths {};
        if (row > 0)
        {
            num_paths += get_num_paths(row - 1, col);
        }

        if (col > 0)
        {
            num_paths += get_num_paths(row, col - 1);
        }

        return memo_num_paths[row][col] = num_paths;
    };

    return get_num_paths(num_rows - 1, num_cols - 1);

} // static int uniquePathsWithObstaclesFA( ...

//! @brief Dynamic programming discussion solution
//! @param[in] obstacleGrid Reference to m x n int grid with obstacle = 1
//! @return Number of unique paths from top left to bottom right corner
static int uniquePathsWithObstaclesDS(
    const std::vector<std::vector<int>>& obstacleGrid)
{
    //! @details https://leetcode.com/problems/unique-paths-ii/editorial/
    //!
    //!          Time complexity O(m * n). The grid has size m * n and process
    //!          each cell once.
    //!          Space complexity O(m * n), assuming the input cannot be edited.
    //!          If the input can be edited then can use obstacledGrid to keep
    //!          track of the number of unique paths at each (row, col) for a
    //!          space complexity of O(1).

    //! If starting cell has an obstacle then return
    //! since there are no paths to the destination
    if (obstacleGrid[0][0] == 1)
    {
        return 0;
    }

    //! Assuming cannot modify input, create a copy
    auto grid = obstacleGrid;

    //! Number of ways of reaching the starting cell is 1
    grid[0][0] = 1;

    const auto num_rows = static_cast<int>(grid.size());
    const auto num_cols = static_cast<int>(grid[0].size());

    //! Fill values for first column
    for (int row = 1; row < num_rows; ++row)
    {
        grid[row][0] = (grid[row][0] == 0 && grid[row - 1][0] == 1) ? 1 : 0;
    }

    //! Fill values for first row
    for (int col = 1; col < num_cols; ++col)
    {
        grid[0][col] = (grid[0][col] == 0 && grid[0][col - 1] == 1) ? 1 : 0;
    }

    //! Fill values starting from (1, 1)
    //! Number of ways of reaching cell[row][col] is
    //! cell[row - 1][col] + cell[row][col - 1]
    for (int row = 1; row < num_rows; ++row)
    {
        for (int col = 1; col < num_cols; ++col)
        {
            if (grid[row][col] == 0)
            {
                grid[row][col] = grid[row - 1][col] + grid[row][col - 1];
            }
            else
            {
                grid[row][col] = 0;
            }
        }
    }

    //! Return value stored in bottom right corner
    return grid[num_rows - 1][num_cols - 1];

} // static int uniquePathsWithObstaclesDS( ...

TEST(UniquePathsWithObstaclesTest, SampleTest1)
{
    const std::vector<std::vector<int>> obstacleGrid {
        {0, 0, 0}, {0, 1, 0}, {0, 0, 0}};

    EXPECT_EQ(2, uniquePathsWithObstaclesFA(obstacleGrid));
    EXPECT_EQ(2, uniquePathsWithObstaclesDS(obstacleGrid));
}

TEST(UniquePathsWithObstaclesTest, SampleTest2)
{
    const std::vector<std::vector<int>> obstacleGrid {
        {0, 1}, {0, 0}};

    EXPECT_EQ(1, uniquePathsWithObstaclesFA(obstacleGrid));
    EXPECT_EQ(1, uniquePathsWithObstaclesDS(obstacleGrid));
}
