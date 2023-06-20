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
    //! @details Still does not pass sample test

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

        const int currRow {currState.row};
        const int currCol {currState.col};
        const int currLabel {currState.label};
        const int currSteps {currState.steps};

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
                std::min(currLabel + 6, endLabel) - (currLabel + 1) + 1};
            
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

    // Not possible to reach square n^2
    return -1;

} // static int snakesAndLaddersFA( ...

//! @brief BFS discussion solution to get least moves to reach square n^2
//! @param[in] board Reference to n x n integer matrix board
//! @return Least number of moves to reach square n^2, else -1 if not possible
static int snakesAndLaddersBFS(const std::vector<std::vector<int>>& board)
{
    //! @details https://leetcode.com/problems/snakes-and-ladders/editorial/
    //!
    //!          BFS finds shortest path in unweighted graphs.
    //!
    //!          Time complexity O(N^2) where N = number of rows and columns.
    //!          BFS takes O(|V| + |E|) where |V| is number of vertices and |E|
    //!          is the number of edges. The vertices are board cells O(N^2) and
    //!          the edges are moves between them, no more than 6N^2 = O(N^2).
    //!          The total time complexity is O(7N^2) = O(N^2). Associating each
    //!          (row, col) with a label also costs O(N^2).
    //!          Space complexity O(N^2). We maintain cells for each label from
    //!          1 to N^2, dist for all cells, and a queue for BFS. The columns
    //!          array only takes O(N) space.

    const auto n = static_cast<int>(board.size());

    std::vector<std::pair<int, int>> cells(n * n + 1);

    //! Maintain order of columns and reverse it after each row
    int              label {1};
    std::vector<int> columns(n);
    std::iota(columns.begin(), columns.end(), 0);

    for (int row = n - 1; row >= 0; --row)
    {
        for (const int column : columns)
        {
            cells[label++] = {row, column};
        }

        std::reverse(columns.begin(), columns.end());
    }

    //! Vector of distances (least moves) to all cells from the first one
    //! Distance from first cell to itself is 0
    //! Unreachable cells are denoted with -1 (initially)
    std::vector<int> dist(n * n + 1, -1);
    dist[1] = 0;

    //! Queue of cells (labels)
    std::queue<int> queue {};
    queue.push(1);

    while (not queue.empty())
    {
        const int curr = queue.front();
        queue.pop();

        for (int next = curr + 1; next <= std::min(curr + 6, n * n); ++next)
        {
            const auto [row, col] = cells[next];

            const int destination {
                board.at(row).at(col) != -1 ? board.at(row).at(col) : next};
            
            if (dist[destination] == -1)
            {
                dist[destination] = dist[curr] + 1;
                queue.push(destination);
            }
        }
    }

    return dist[n * n];

} // static int snakesAndLaddersBFS( ...

//! @brief Dijkstra's algorithm solution to get least moves to reach square n^2
//! @param[in] board Reference to n x n integer matrix board
//! @return Least number of moves to reach square n^2, else -1 if not possible
static int snakesAndLaddersDijkstra(const std::vector<std::vector<int>>& board)
{
    //! @details https://leetcode.com/problems/snakes-and-ladders/editorial/
    //!
    //!          Dijkstra's algorithm solves shortest path problem for weighted
    //!          graphs. Can treat an unweighted graph where all weights are
    //!          equal to 1.
    //!
    //!          Time complexity O(N^2 * log N) where N = number of columns and
    //!          rows of the board. Dijkstra's algorithm with a binary heap
    //!          works in O(|V| + |E|*log|V|) where |V| is number of vertices
    //!          and |E| is the number of edges. We have |V| = N^2, |E| < 6N^2
    //!          Space complexity O(N^2). Space complexity of Dijkstra's
    //!          algorithm is O(|V|) = O(N^2) to store |V| vertices in our
    //!          data structure (priority queue and vector of distances). Also
    //!          have cells of size O(N^2) and columns of size O(N).

    const auto n = static_cast<int>(board.size());

    std::vector<std::pair<int, int>> cells(n * n + 1);

    //! Maintain order of columns and reverse it after each row
    int              label {1};
    std::vector<int> columns(n);
    std::iota(columns.begin(), columns.end(), 0);

    for (int row = n - 1; row >= 0; --row)
    {
        for (const int column : columns)
        {
            cells[label++] = {row, column};
        }

        std::reverse(columns.begin(), columns.end());
    }

    //! Vector of distances (least moves) to all cells from the first one
    //! Distance from first cell to itself is 0
    //! Unreachable cells are denoted with -1 (initially)
    std::vector<int> dist(n * n + 1, -1);
    dist[1] = 0;

    //! Priority queue of cells as pairs <distance, label>
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> queue;
    queue.emplace(0, 1);

    while (not queue.empty())
    {
        const auto [distance, curr] = queue.top();
        queue.pop();

        //! If not equal, the value distance is outdated so move on
        if (distance != dist[curr])
        {
            continue;
        }

        for (int next = curr + 1; next <= std::min(curr + 6, n * n); ++next)
        {
            const auto [row, col] = cells[next];

            const int destination {
                board.at(row).at(col) != -1 ? board.at(row).at(col) : next};
            
            //! If haven't found a path to destination yet (-1) or we've just
            //! found a shorter path then push pair to priority queue
            if (dist[destination] == -1 || dist[curr] + 1 < dist[destination])
            {
                dist[destination] = dist[curr] + 1;
                queue.emplace(dist[destination], destination);
            }
        }
    }

    return dist[n * n];

} // static int snakesAndLaddersDijkstra( ...

TEST(SnakesAndLaddersTest, SampleTest)
{
    const std::vector<std::vector<int>> board {
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, 35, -1, -1, 13, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, 15, -1, -1, -1, -1}};

    EXPECT_NE(4, snakesAndLaddersFA(board));
    EXPECT_EQ(5, snakesAndLaddersFA(board));

    EXPECT_EQ(4, snakesAndLaddersBFS(board));
    EXPECT_EQ(4, snakesAndLaddersDijkstra(board));
}