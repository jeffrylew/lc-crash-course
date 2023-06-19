#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

//! @struct State
//! @brief Keeps track of location, cell label, and number of steps to get there
struct State
{
    int row {};
    int col {};
    int label {};
    int steps {};

    State(int row_in, int col_in, int label_in, int steps_in)
        : row {row_in}
        , col {col_in}
        , label {label_in}
        , steps {steps_in}
    {
    }
};

//! @brief Helper function to convert square number to (row, col)
//! @param[in] square_num Cell label in range [1, n^2]
//! @param[in] board_size One dimension of n x n board
//! @return pair<row, col> corresponding to cell label/square number in board
static std::pair<int, int> get_loc(int square_num, int board_size)
{
    //! Subtract 1 from square_num for formula ease
    const int num {square_num - 1};

    //! Starting row
    int row {board_size - 1};

    //! Determine row offset via quotient
    const int quotient {num / board_size};
    row -= quotient;

    //! Determine col offset using quotient evenness and remainder
    const int remainder {num % board_size};
    if (quotient % 2 == 0)
    {
        //! Even quotient, col starts at 0 and increments by remainder offset
        return {row, remainder};
    }

    //! Odd quotient, col starts at board_size - 1 and decrements by remainder
    return {row, board_size - 1 - remainder};
}

//! @brief Get least number of moves required to reach square n^2
//! @param[in] board Reference to n x n integer matrix board
//! @return Least number of moves to reach square n^2, else -1 if not possible
static int snakesAndLaddersFA(const std::vector<std::vector<int>>& board)
{
    const auto n = static_cast<int>(board.size());

    const int     startRow {n - 1};
    constexpr int startCol {};
    constexpr int startLabel {1};
    const int     endLabel {n * n};

    std::vector<std::vector<bool>> seen(
        board.size(), std::vector<bool>(board.size(), false));
    seen[startRow][startCol] = true;

    std::queue<State> queue {};
    queue.emplace(startRow, startCol, startLabel, 0);

    while (not queue.empty())
    {
        const auto currState = queue.front();
        queue.pop();

        const int  currRow {currState.row};
        const int  currCol {currState.col};
        const int  currLabel {currState.label};
        const int  currSteps {currState.steps};

        if (currLabel == endLabel)
        {
            //! Reached square n^2
            return currSteps;
        }

        if (-1 == board.at(currRow).at(currCol))
        {
            //! No snake or ladder at current position
            //! Add all cells with labels in [curr + 1, min(curr + 6, n ^ 2)]
            const int num_cells {
                std::min(currLabel + 1, endLabel) - (currLabel + 1) + 1};
            
            std::vector<int> neighbors(num_cells);
            std::iota(neighbors.begin(), neighbors.end(), currLabel + 1);

            for (const int nextLabel : neighbors)
            {
                const auto [nextRow, nextCol] = get_loc(nextLabel, n);

                if (not seen[nextRow][nextCol])
                {
                    seen[nextRow][nextCol] = true;
                    queue.emplace(nextRow, nextCol, nextLabel, currSteps + 1);
                }
            }
        }
        else
        {
            //! There is a snake or ladder at current position
            //! Add destination of snake or ladder to queue
            const int nextLabel {board.at(currRow).at(currCol)};

            const auto [nextRow, nextCol] = get_loc(nextLabel, n);

            if (not seen[nextRow][nextCol])
            {
                seen[nextRow][nextCol] = true;
                queue.emplace(nextRow, nextCol, nextLabel, currSteps + 1);
            }
        }
    }

    // Not possible to reach square n ^ 2
    return -1;

} // static int snakesAndLaddersFA( ...

TEST(SnakesAndLaddersTest, SampleTest)
{
    // Todo, currently not passing tests
}