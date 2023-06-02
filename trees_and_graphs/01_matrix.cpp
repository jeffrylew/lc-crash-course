#include <gtest/gtest.h>

#include <queue>
#include <vector>

//! @brief Helper function to determine if (row, col) is within mat
//! @param[in] row Current row
//! @param[in] col Current col
//! @param[in] mat Reference to m x n binary matrix
//! @return True if (row, col) is a valid location within mat and has value of 1
static bool valid(int row, int col, const std::vector<std::vector<int>>& mat)
{
    return 0 <= row
        && row < static_cast<int>(mat.size())
        && 0 <= col
        && col < static_cast<int>(mat.front().size())
        && mat.at(row).at(col) == 1;
}

//! @brief Find distance of nearest 0 for each cell
//! @param[in] mat Reference to m x n binary matrix
//! @return m x n matrix of distances
static std::vector<std::vector<int>> updateMatrix(
    const std::vector<std::vector<int>>& mat)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /707/traversals-trees-graphs/4631/
    //!
    //!          Time complexity O(m * n). BFS visits each square once and does
    //!          a constant amount of work each time.
    //!          Space complexity O(m * n) for queue and seen.

    std::vector<std::vector<int>>  output_mat {mat};
    std::queue<std::vector<int>>   queue {};
    std::vector<std::vector<bool>> seen(
        mat.size(), std::vector<bool>(mat.front().size(), false));
    
    const auto m = static_cast<int>(mat.size())
    const auto n = static_cast<int>(mat.front().size());

    for (int row = 0; row < m; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            if (mat.at(row).at(col) == 0)
            {
                queue.emplace({row, col, 1});
                seen[row][col] = true;
            }
        }
    }

    static const std::vector<std::vector<int>> directions {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (not queue.empty())
    {
        const auto [row, col, steps] = queue.front();
        queue.pop();

        for (const auto& direction : directions)
        {
            const int nextRow {row + direction.front()};
            const int nextCol {col + direction.back()};

            if (valid(nextRow, nextCol, mat) && not seen[nextRow][nextCol])
            {
                seen[nextRow][nextCol] = true;
                queue.emplace({nextRow, nextCol, steps + 1});
                output_mat[nextRow][nextCol] = steps;
            }
        }
    }

    return output_mat;

} // static std::vector<std::vector<int>> updateMatrix( ...

TEST(UpdateMatrixTest, SampleTest)
{
    const std::vector<std::vector<int>> input {
        {0, 0, 0}, {0, 1, 0}, {1, 1, 1}};

    const std::vector<std::vector<int>> expected_output {
        {0, 0, 0}, {0, 1, 0}, {1, 2, 1}};

    EXPECT_EQ(expected_output, updateMatrix(input));
}