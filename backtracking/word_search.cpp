#include <gtest/gtest.h>

#include <functional>
#include <string>
#include <vector>

//! @brief Determine if word exists in the m x n grid of characters
//! @param[in] board Reference to m x n grid of characters
//! @param[in] word  std::string for word to find
//! @return True if word exists in the grid, else false
static bool exist(const std::vector<std::vector<char>>& board, std::string word)
{
    //! @details https://leetcode.com/problems/word-search/description/
    //!
    //!          Time complexity O(n * m * 3 ^ L) where L = word.size(). Each
    //!          node in the solution space tree can have 3 children (not 4
    //!          because we don't consider the square where we came from, except
    //!          the first node). The max depth is L, giving us 3 ^ L nodes.
    //!          There are n * m squares that we can start from. This worst-case
    //!          time complexity would occur in a setup like WorstCaseTest below
    //!          where the grid only has one letter and the word has the same
    //!          letter except for the last character.
    //!          Space complexity O(n * m) for the boolean 2D vector seen.

    const auto nrows = static_cast<int>(board.size());
    const auto ncols = static_cast<int>(board[0].size());

    const std::vector<std::vector<int>> directions {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    std::vector<std::vector<bool>> seen(
        board.size(), std::vector<bool>(board[0].size(), false));

    auto valid = [nrows, ncols](int row, int col) -> bool {
        return 0 <= row && row < nrows && 0 <= col && col < ncols;
    };

    std::function<bool(int, int, int)> backtrack =
        [&](int row, int col, int i) -> bool {
            if (i == static_cast<int>(word.size()))
            {
                return true;
            }

            for (const auto& direction : directions)
            {
                const int nextRow {row + direction[0]};
                const int nextCol {col + direction[1]};

                if (valid(nextRow, nextCol) && not seen[nextRow][nextCol])
                {
                    if (board[nextRow][nextCol] == word[i])
                    {
                        seen[nextRow][nextCol] = true;

                        if (backtrack(nextRow, nextCol, i + 1))
                        {
                            return true;
                        }

                        seen[nextRow][nextCol] = false;
                    }
                }
            }

            return false;
        };

    for (int row = 0; row < nrows; ++row)
    {
        for (int col = 0; col < ncols; ++col)
        {
            if (board[row][col] == word[0])
            {
                seen[row][col] = true;

                if (backtrack(row, col, 1))
                {
                    return true;
                }

                seen[row][col] = false;
            }
        }
    }

    return false;

} // static bool exist( ...

TEST(ExistTest, SampleTest1)
{
    const std::vector<std::vector<char>> board {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}};

    EXPECT_TRUE(exist(board, "ABCCED"));
    EXPECT_TRUE(exist(board, "SEE"));
    EXPECT_FALSE(exist(board, "ABCB"));
}

TEST(ExistTest, WorstCaseTest)
{
    const std::vector<std::vector<char>> board {
        {'A', 'A', 'A'},
        {'A', 'A', 'A'},
        {'A', 'A', 'A'}};

    EXPECT_FALSE(exist(board, "AAAAAAAAZ"));
}
