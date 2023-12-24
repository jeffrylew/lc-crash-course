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

//! @brief Discussion solution to find combinations of k numbers that sum to n
//! @param[in] k Number of numbers, only 1 through 9 are used at most once
//! @param[in] n Sum of combinations of k numbers
//! @return Vector of all possible combinations
static std::vector<std::vector<int>> combinationSum3DS1(int k, int n)
{
    //! @details https://leetcode.com/problems/combination-sum-iii/editorial/
    //!
    //!          Time complexity O(9! * k / (9 - k)!) where k = number of digits
    //!          In the worst case scenario, need to explore all potential
    //!          combinations when the sum n is large. At the first step, have 9
    //!          choices while at the second step, have 8 choices, etc.
    //!          The number of explorations in the worse case is P(9, k) =
    //!          9! / (9 - k)!, assuming k <= 9. Each exploration takes constant
    //!          time to process except the last step where it takes O(k) to
    //!          copy the combination.
    //!          The latter is from the editorial. However, the comment section
    //!          disagrees and says time complexity is O(9! / (k! * (9 - k)!))
    //!          since the order of numbers doesn't matter.
    //!          Space complexity O(k). During backtracking, used a list to keep
    //!          the current combination which holds up to k elements. Recursion
    //!          call stack could pile up to k consecutive invocations so the
    //!          overall space complexity would be O(k).

    std::vector<std::vector<int>> results {};
    std::vector<int>              comb {};

    std::function<void(int, int)> backtrack = [&](int remain, int next_start) {
        if (remain == 0 && static_cast<int>(comb.size()) == k)
        {
            //! @note It's important to make a deep copy here, otherwise the
            //! combination would be reverted in another backtracking branch
            results.push_back(comb);
            return;
        }
        else if (remain < 0 || static_cast<int>(comb.size()) == k)
        {
            //! Exceeded the scope, no need to explore further
            return;
        }

        //! Iterate through the reduced list of candidates
        for (int i = next_start; i < 9; ++i)
        {
            comb.push_back(i + 1);
            backtrack(remain - i - 1, i + 1);
            comb.pop_back();
        }
    };

    backtrack(n, 0);
    return results;

} // static std::vector<std::vector<int>> combinationSum3DS1( ...

TEST(CombinationSum3Test, SampleTest1)
{
    const std::vector<std::vector<int>> expected_output {{1, 2, 4}};

    EXPECT_EQ(expected_output, combinationSum3FA(3, 7));
    EXPECT_EQ(expected_output, combinationSum3DS1(3, 7));
}

TEST(combinationSum3Test, SampleTest2)
{
    const std::vector<std::vector<int>> expected_output {
        {1, 2, 6}, {1, 3, 5}, {2, 3, 4}};

    EXPECT_EQ(expected_output, combinationSum3FA(3, 9));
    EXPECT_EQ(expected_output, combinationSum3DS1(3, 9));
}

TEST(CombinationSum3Test, SampleTest3)
{
    EXPECT_TRUE(combinationSum3FA(4, 1).empty());
    EXPECT_TRUE(combinationSum3DS1(4, 1).empty());
}
