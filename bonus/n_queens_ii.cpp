#include <gtest/gtest.h>

#include <functional>

//! @brief Get number of distinct solutions to the n-queens puzzle
//! @param[in] n Number of queens to place on an n x n chessboard
//! @return Number of distinct solutions to the n-queens puzzle
static int totalNQueensDS1(int n)
{
    //! @details https://leetcode.com/problems/n-queens-ii/description/
    //!
    //!          Time complexity isn't actually known but is approximately O(n!)
    //!          See explanation under backtracking/n_queens_ii.cpp
    //!          Space complexity is still O(n) due to recursion call stack.
    //!          Practically, have improved space usage since using 3 integers
    //!          instead of 3 sets.

    //! row: Consider one row per backtrack call. When row = n, found valid soln
    //! diagonals: Top left to bottom right. Values in diagonal share row - col
    //! antiDiagonals: Top right to bottom left. Values share row + col
    //! cols: Stores the columns in [0, n) already occupied. One queen per col
    //! @note Default capture by reference since [=] triggers address sanitizer
    const std::function<int(int, int, int, int)> backtrack =
        [&](int row, int diagonals, int antiDiagonals, int cols) {
            //! Base case: N queens have been placed
            if (row == n)
            {
                return 1;
            }

            int num_solutions {};
            for (int col = 0; col < n; ++col)
            {
                //! Bit masks. Add n to avoid negative bit shifting
                const int currDiagonal {1 << (row - col + n)};
                const int currAntiDiagonal {1 << (row + col)};
                const int currCol {1 << col};

                //! If the queen is not placeable
                if (cols & currCol              // col in cols already occupied
                    || diagonals & currDiagonal // currDiagonal already occupied
                    || antiDiagonals & currAntiDiagonal) // Already occupied
                {
                    continue;
                }

                //! "Add" the queen to the board
                cols ^= currCol;
                diagonals ^= currDiagonal;
                antiDiagonals ^= currAntiDiagonal;

                //! Move onto the next row with the updated board state
                num_solutions +=
                    backtrack(row + 1, diagonals, antiDiagonals, cols);

                //! "Remove" the queen from the board since we have already
                //! explored all valid paths using the above function call
                cols ^= currCol;
                diagonals ^= currDiagonal;
                antiDiagonals ^= currAntiDiagonal;
            }

            return num_solutions;
        };

    return backtrack(0, 0, 0, 0);

} // static int totalNQueensDS1( ...

TEST(TotalNQueensTest, SampleTest1)
{
    EXPECT_EQ(2, totalNQueensDS1(4));
}
