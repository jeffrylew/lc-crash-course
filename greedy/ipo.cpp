#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

//! @struct Project
//! @brief Keep track of capital and profit for a project
struct Project
{
    int capital {};
    int profit {};

    Project(int capital_in, int profit_in)
        : capital {capital}
        , profit {profit_in}
    {
    }

    friend bool operator<(const Project& lhs, const Project& rhs)
    {
        return std::tie(lhs.capital, lhs.profit)
            < std::tie(rhs.capital, rhs.profit);
    }
};

//! @brief Get max capital after finishing k projects
//! @param[in] k       Max number of distinct projects to maximize capital
//! @param[in] w       Initial capital
//! @param[in] profits Vector of profits[i] upon completing a project
//! @param[in] capital Vector of minimum capital[i] to do a project
//! @return Maximum capital after finishing k projects
static int findMaximizedCapital(
    int k, int w, std::vector<int> profits, std::vector<int> capital)
{
    //! @details https://leetcode.com/problems/ipo/
    //!
    //!          Time complexity O((k + N) * log N) where N = number of projects
    //!          Heap's max size is N so its operations are log N in the worst
    //!          case. Perform k + N operations (k pop and n push operations).
    //!          Initial sort costs O(N * log N) which doesn't change complexity
    //!          Space complexity O(N) due to heap
    
    const auto N = static_cast<int>(profits.size());

    //! Vector of <capital, profit>
    // std::vector<std::pair<int, int>> projects {};
    std::vector<Project> projects {};
    for (int i = 0; i < N; ++i)
    {
        projects.emplace_back(capital[i], profits[i]);
    }

    //! Sort by capital then profits
    std::sort(projects.begin(), projects.end());

    //! Max heap to get max profit project
    std::priority_queue<int> heap {};

    //! Index of most expensive project that we can afford
    //! After completing a project and adding profit to w, move i forward until
    //! i points to a project that costs more than w
    int i {};

    for (int j = 0; j < k; ++j)
    {
        // while (i < N && projects[i].first <= w)
        while (i < N && projects[i].capital <= w)
        {
            // heap.push(projects[i].second);
            heap.push(projects[i].profit);
            ++i;
        }

        if (heap.empty())
        {
            return w;
        }

        w += heap.top();
        heap.pop();
    }

    return w;

} // static int findMaximizedCapital( ...

TEST(FindMaximizedCapitalTest, SampleTest)
{
    EXPECT_EQ(4, findMaximizedCapital(2, 0, {1, 2, 3}, {0, 1, 1}));

    EXPECT_EQ(6, findMaximizedCapital(3, 0, {1, 2, 3}, {0, 1, 2}));
}