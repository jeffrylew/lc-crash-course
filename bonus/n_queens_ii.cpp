#include <gtest/gtest.h>

#include <functional>
#include <unordered_set>

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
                if ((cols & currCol) != 0              // currCol occupied
                    || (diagonals & currDiagonal) != 0 // currDiagonal occupied
                    || (antiDiagonals & currAntiDiagonal) != 0) // Occupied
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

//! @brief Discussion solution but with visited location ints declared outside
//! @param[in] n Number of queens to place on an n x n chessboard
//! @return Number of distinct solutions to the n-queens puzzle
static int totalNQueensDS2(int n)
{
    //! @details https://leetcode.com/problems/n-queens-ii/description/

    //! diagonals: Top left to bottom right. Values in diagonal share row - col
    //! antiDiagonals: Top right to bottom left. Values share row + col
    //! cols: Stores the columns in [0, n) already occupied. One queen per col
    int diagonals {};
    int antiDiagonals {};
    int cols {};

    //! row: Consider one row per backtrack call. When row = n, found valid soln
    const std::function<int(int)> backtrack = [&](int row) {
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
            if ((cols & currCol) != 0              // currCol occupied
                || (diagonals & currDiagonal) != 0 // currDiagonal occupied
                || (antiDiagonals & currAntiDiagonal) != 0) // Occupied
            {
                continue;
            }

            //! "Add" the queen to the board
            cols ^= currCol;
            diagonals ^= currDiagonal;
            antiDiagonals ^= currAntiDiagonal;

            //! Move onto the next row with the updated board state
            num_solutions += backtrack(row + 1);

            //! "Remove" the queen from the board since we have already
            //! explored all valid paths using the above function call
            cols ^= currCol;
            diagonals ^= currDiagonal;
            antiDiagonals ^= currAntiDiagonal;
        }

        return num_solutions;
    };

    return backtrack(0);

} // static int totalNQueensDS2( ...

//! @brief Discussion solution copied from backtracking/n_queens_ii.cpp
//! @param[in] n Number of queens to place on an n x n chessboard
//! @return Number of distinct solutions to the n-queens puzzle
static int totalNQueensDS3(int n)
{
    std::unordered_set<int> diagonals;
    std::unordered_set<int> antiDiagonals;
    std::unordered_set<int> cols;

    const std::function<int(int)> backtrack = [&](int row) {
        //! Base case: N queens have been placed
        if (row == n)
        {
            return 1;
        }

        int num_solutions {};
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
            num_solutions += backtrack(row + 1);

            //! "Remove" the queen from the board since we have already
            //! explored all valid paths using the above function call
            cols.erase(col);
            diagonals.erase(currDiagonal);
            antiDiagonals.erase(currAntiDiagonal);
        }

        return num_solutions;
    };

    return backtrack(0);

} // static int totalNQueensDS3( ...

TEST(TotalNQueensTest, SampleTest1)
{
    EXPECT_EQ(2, totalNQueensDS1(4));
    EXPECT_EQ(2, totalNQueensDS2(4));
    EXPECT_EQ(2, totalNQueensDS3(4));
}
