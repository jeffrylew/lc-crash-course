#include <gtest/gtest.h>

#include <queue>
#include <vector>

static bool valid(int row, int col, int m, int n)
{
    return 0 <= row && row < m && 0 <= col && col < n;
}

struct State
{
    int row {};
    int col {};

    //! Number of removals remaining on current path
    int remain {};

    //! Number of steps taken
    int steps {};

    State(int row_in, int col_in, int remain_in, int steps_in)
        : row {row_in}
        , col {col_in}
        , remain {remain_in}
        , steps {steps_in}
    {
    }
};

//! @brief Min number of steps from (0, 0) to (m-1, n-1) eliminating k obstacles
//! @param[in] grid Reference to m x n grid where 0 = empty and 1 = obstacle
//! @param[in] k    Number of obstacles that can be eliminated
//! @return Minimum number of steps to walk from (0, 0) to (m - 1, n - 1)
static int shortestPath(const std::vector<std::vector<int>>& grid, int k)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /707/traversals-trees-graphs/4631/
    //!
    //!          Time complexity O(m * n * k). In general, the time complexity
    //!          for graph algorithms in O(Nodes + Edges) when a node isn't
    //!          visited more than once. In this problem, s = number of states
    //!          is used instead of nodes. There are two variables representing
    //!          the state - (node, remain). There are m * n values for node and
    //!          k values for remain so there are m * n * k states. The work
    //!          done at each state is O(1).
    //!          Space complexity O(m * n) instead of O(m * n * k) since seen
    //!          stores the removals at each node (instead of having another
    //!          dimension for k removal states).

    const auto m = static_cast<int>(grid.size());
    const auto n = static_cast<int>(grid.front().size());

    std::queue<State> queue {};
    
    //! Can save one dimension for "remain"
    //! There's no point in returning to a square we already
    //! visited but with fewer remaining removals
    std::vector<std::vector<int>> seen(
        grid.size(), std::vector<int>(grid.front().size(), -1));
    
    queue.emplace(0, 0, k, 0);

    static const std::vector<std::vector<int>> directions {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (not queue.empty())
    {
        const auto curr_state = queue.front();
        queue.pop();

        const int row {curr_state.row};
        const int col {curr_state.col};
        const int steps {curr_state.steps};

        int remain {curr_state.remain};

        if (row == m - 1 && col == n - 1)
        {
            return steps;
        }

        //! If current square is an obstacle,
        //! need to spend one of the removals
        if (grid[row][col] == 1)
        {
            if (remain == 0)
            {
                continue;
            }
            else
            {
                remain--;
            }
        }

        //! If the square has already been visited with more removals,
        //! then the current path is pointless since more removals is better
        if (seen[row][col] >= remain)
        {
            continue;
        }

        seen[row][col] = remain;
        for (const auto& direction : directions)
        {
            const int nextRow {row + direction.front()};
            const int nextCol {col + direction.back()};

            if (valid(nextRow, nextCol, m, n))
            {
                queue.emplace(nextRow, nextCol, remain, steps + 1);
            }
        }

    } // while (not queue.empty())

    return -1;

} // static int shortestPath( ...

TEST(ShortestPathTest, SampleTest)
{
    const std::vector<std::vector<int>> input {
        {0, 0, 0}, {1, 1, 0}, {0, 0, 0}, {0, 1, 1}, {0, 0, 0}};

    EXPECT_EQ(6, shortestPath(input, 1));
}