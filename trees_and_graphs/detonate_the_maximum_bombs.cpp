#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>

//! @brief Get max number of bombs that can be detonated from only one bomb
//! @param[in] bombs Reference to vector of [x_i, y_i, r_i] for bombs[i]
//! @return Max number of bombs that can be detonated from only one bomb
static int maximumDetonationFA(const std::vector<std::vector<int>>& bombs)
{
    //! <vector of neighboring bomb indices that are in range of ith bomb>
    std::vector<std::vector<int>> neighbors(bombs.size());

    const auto nbombs = static_cast<int>(bombs.size());

    for (int j = 0; j < nbombs; ++j)
    {
        const auto& xyr1 = bombs.at(j);

        for (int i = j + 1; i < nbombs; ++i)
        {
            const auto& xyr2 = bombs.at(i);
            const auto  dx   = static_cast<double>(xyr2.at(0) - xyr1.at(0));
            const auto  dy   = static_cast<double>(xyr2.at(1) - xyr1.at(1));

            const double dist {
                std::sqrt(std::pow(dx, 2.0) + std::pow(dy, 2.0))};
            
            if (dist <= xyr1.back())
            {
                neighbors[j].push_back(i);
            }

            if (dist <= xyr2.back())
            {
                neighbors[i].push_back(j);
            }
        }
    }

    int max_bombs {};

    for (int i = 0; i < nbombs; ++i)
    {
        int curr_bombs {};

        std::queue<int> queue({i});

        std::vector<bool> seen(bombs.size());
        seen[i] = true;

        while (not queue.empty())
        {
            const auto bomb_idx = queue.front();
            queue.pop();

            max_bombs = std::max(max_bombs, ++curr_bombs);

            for (const auto neighbor : neighbors[bomb_idx])
            {
                if (not seen[neighbor])
                {
                    seen[neighbor] = true;

                    queue.push(neighbor);
                }
            }
        }
    }

    return max_bombs;

} // static int maximumDetonationFA( ...

TEST(MaximumDetonationTest, SampleTest1)
{
    const std::vector<std::vector<int>> bombs {{2, 1, 3}, {6, 1, 4}};

    EXPECT_EQ(2, maximumDetonationFA(bombs));
}

TEST(MaximumDetonationTest, SampleTest2)
{
    const std::vector<std::vector<int>> bombs {{1, 1, 5}, {10, 10, 5}};

    EXPECT_EQ(1, maximumDetonationFA(bombs));
}

TEST(MaximumDetonationTest, SampleTest3)
{
    const std::vector<std::vector<int>> bombs {
        {1, 2, 3}, {2, 3, 1}, {3, 4, 2}, {4, 5, 3}, {5, 6, 4}};

    EXPECT_EQ(5, maximumDetonationFA(bombs));
}
