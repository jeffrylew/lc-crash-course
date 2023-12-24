#include <gtest/gtest.h>

#include <functional>
#include <vector>

//! @brief First attempt to find combinations of k numbers that sum to n
//! @param[in] k Number of numbers, only 1 through 9 are used at most once
//! @param[in] n Sum of combinations of k numbers
//! @return Vector of all possible combinations
static std::vector<std::vector<int>> combinationSum3FA(int k, int n)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /711/backtracking/4683/
    //!
    //!          Time complexity O(9! / (9 - k)! * 2 ^ k)?
    //!          Space complexity O(k)

    std::vector<std::vector<int>> all_combos {};
    std::vector<int>              curr_combo {};

    std::function<void(int, int)> backtrack = [&](int curr_num, int curr_sum) {
        if (curr_sum == n && static_cast<int>(curr_combo.size()) == k)
        {
            all_combos.push_back(curr_combo);
            return;
        }

        for (int num = curr_num; num < 10; ++num)
        {
            const int next_sum {curr_sum + num};
            if (next_sum > n || static_cast<int>(curr_combo.size()) > k)
            {
                break;
            }

            curr_combo.push_back(num);
            backtrack(num + 1, next_sum);
            curr_combo.pop_back();
        }
    };

    backtrack(1, 0);
    return all_combos;

} // static std::vector<std::vector<int>> combinationSum3FA( ...

TEST(CombinationSum3Test, SampleTest1)
{
    const std::vector<std::vector<int>> expected_output {{1, 2, 4}};

    EXPECT_EQ(expected_output, combinationSum3FA(3, 7));
}

TEST(combinationSum3Test, SampleTest2)
{
    const std::vector<std::vector<int>> expected_output {
        {1, 2, 6}, {1, 3, 5}, {2, 3, 4}};

    EXPECT_EQ(expected_output, combinationSum3FA(3, 9));
}

TEST(CombinationSum3Test, SampleTest3)
{
    EXPECT_TRUE(combinationSum3FA(4, 1).empty());
}
