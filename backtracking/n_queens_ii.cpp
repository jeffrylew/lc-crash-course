#include <gtest/gtest.h>

#include <functional>
#include <unordered_set>

//! @brief Get number of distinct solutions to the N-Queens puzzle
//! @param[in] n Number of queens placed on an n x n chessboard
//! @return Number of distinct solutions where no two queens attack each other
static int totalNQueens(int n)
{
    //! @details https://leetcode.com/problems/n-queens-ii/
    //!
    //!          Time complexity isn't actually known but is approximately O(n!)
    //!          The first call will consider n options, the next call will
    //!          consider n - 2 options because one square will occupy the same
    //!          column and at least one square will occupy a diagonal and
    //!          anti diagonal. The pattern continues - the next call afterwards
    //!          will consider n - 4 squares and so on.
    //!          Space complexity is O(n) due to sets and recursion call stack.

    std::unordered_set<int> diagonals;
    std::unordered_set<int> antiDiagonals;
    std::unordered_set<int> cols;

    std::function<int(int)> backtrack = [&](int row) {
        //! Base case: N queens have been placed
        if (row == n)
        {
            return 1;
        }

        int solutions {};
        for (int col = 0; col < n; ++col)
        {
            const int currDiagonal {row - col};
            const int currAntiDiagonal {row + col};

            //! If the queen is not placeable
            if (cols.count(col) > 0
                || diagonals.count(currDiagonal) > 0
                || antiDiagonals.count(currAntiDiagonal) > 0)
            {
                continue;
            }

            //! "Add" the queen to the board
            cols.insert(col);
            diagonals.insert(currDiagonal);
            antiDiagonals.insert(currAntiDiagonal);

            //! Move onto the next row with the updated board state
            solutions += backtrack(row + 1);

            //! "Remove" the queen from the board since we have already
            //! explored all valid paths using the above function call
            cols.erase(col);
            diagonals.erase(currDiagonal);
            antiDiagonals.erase(currAntiDiagonal);
        }

        return solutions;
    };

    return backtrack(0);
}

TEST(TotalNQueensTest, SampleTest1)
{
    EXPECT_EQ(2, totalNQueens(4));

    EXPECT_EQ(1, totalNQueens(1));
}
