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
}

TEST(UniquePathsWithObstaclesTest, SampleTest1)
{
    const std::vector<std::vector<int>> obstacleGrid {
        {0, 0, 0}, {0, 1, 0}, {0, 0, 0}};

    EXPECT_EQ(2, uniquePathsWithObstaclesFA(obstacleGrid));
}

TEST(UniquePathsWithObstaclesTest, SampleTest2)
{
    const std::vector<std::vector<int>> obstacleGrid {
        {0, 1}, {0, 0}};

    EXPECT_EQ(1, uniquePathsWithObstaclesFA(obstacleGrid));
}
