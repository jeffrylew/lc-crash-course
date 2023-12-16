#include <gtest/gtest.h>

#include <functional>
#include <string>
#include <vector>

//! @brief Generate all combinations of well-formed parentheses given n pairs
//! @param[in] n Number of pairs of parentheses
//! @return Vector of all combinations of well-formed parentheses
static std::vector<std::string> generateParenthesesFA(int n)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /711/backtracking/4578/

    std::vector<std::string> combinations {};
    std::string              curr {};

    std::function(void(int)) backtrack = [&](int left_brace_pos) {
        if (num_right_braces == n)
        {
            combinations.push_back(curr);
            return;
        }

        for (int num_left_braces = 0; num_left_braces < n; ++num_left_braces)
        {
            curr += "(";

            backtrack();

            curr += ")";
        }
    };

    backtrack(0);
    return combinations;
}

TEST(GenerateParenthesesTest, SampleTest1)
{
    const std::vector<std::string> expected_output {
        "((()))", "(()())", "(())()", "()(())", "()()()"};

    EXPECT_EQ(expected_output, generateParenthesesFA(3));
}

TEST(generateParenthesesTest, SampleTest2)
{
    const std::vector<std::string> expected_output {"()"};

    EXPECT_EQ(expected_output, generateParenthesesFA(1));
}
