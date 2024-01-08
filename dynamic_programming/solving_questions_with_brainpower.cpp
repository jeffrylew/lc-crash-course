#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <vector>

//! @brief Solve i to earn points[i] but skip next brainpower[i] or skip i
//! @param[in] questions Reference to 2D vector of {points[i], brainpower[i]}
//! @return Max points can score
static long long mostPointsTopDown(
    const std::vector<std::vector<int>>& questions)
{
    //! @details https://leetcode.com/problems/solving-questions-with-brainpower
    //!
    //!          Time complexity O(n) where n = questions.size(). There are O(n)
    //!          states and each state costs O(1) to compute.
    //!          Space complexity O(n).

    std::vector<long long> memo(questions.size());

    //! Returns max score, index i indicates current question we are on
    std::function<long long(int, std::vector<long long>&)> dp =
        [&](int i, std::vector<long long>& memo) {
            //! Base case at end since moving forward through array
            if (i >= static_cast<int>(questions.size()))
            {
                //! When exam is over, cannot score any more points
                return 0;
            }

            if (memo[i] != 0)
            {
                return memo[i];
            }

            const int next_idx {i + questions[i][1] + 1};

            //! Two options
            //! - Solve question and gain questions[i][0] points. Next question
            //!   can solve is at index (i + questions[i][1] + 1)
            //! - Skip question so can move to next question. Score is dp(i + 1)
            return memo[i] =
                std::max(questions[i][0] + dp(next_idx, memo), dp(i + 1, memo));
        };

    return dp(0, memo);

} // static long long mostPointsTopDown( ...

//! @brief Solve i to earn points[i] but skip next brainpower[i] or skip i
//! @param[in] questions Reference to 2D vector of {points[i], brainpower[i]}
//! @return Max points can score
static long long mostPointsBottomUp(
    const std::vector<std::vector<int>>& questions)
{
    const auto questions_size = static_cast<int>(questions.size());

    //! questions_size + 1 to avoid out of bounds
    std::vector<long long> dp(questions.size() + 1U);

    for (int i = questions_size - 1; i >= 0; --i)
    {
        const int next_idx {i + questions[i][1] + 1};

        //! Make sure we don't go out of bounds
        dp[i] = std::max(
            questions[i][0] + dp[std::min(next_idx, questions_size)],
            dp[i + 1]);
    }

    return dp[0];
}

TEST(MostPointsTest, SampleTest1)
{
    const std::vector<std::vector<int>> questions {
        {3, 2}, {4, 3}, {4, 4}, {2, 5}};

    EXPECT_EQ(5, mostPointsTopDown(questions));
    EXPECT_EQ(5, mostPointsBottomUp(questions));
}

TEST(MostPointsTest, SampleTest2)
{
    const std::vector<std::vector<int>> questions {
        {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

    EXPECT_EQ(7, mostPointsTopDown(questions));
    EXPECT_EQ(7, mostPointsBottomUp(questions));
}
