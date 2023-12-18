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

    std::function<void(int, int)> backtrack = [&](int total_left_braces,
                                                  int total_right_braces) {
        //! @details This solution does not give the correct answer

        if (total_left_braces + total_right_braces == 2 * n)
        {
            combinations.push_back(curr);
            return;
        }

        /*
        if (total_left_braces < n)
        {
            curr += "(";
            ++total_left_braces;
        }
        else
        {
            return;
        }

        backtrack(total_left_braces, total_right_braces);

        if (total_right_braces < total_left_braces)
        {
            curr += ")";
            ++total_right_braces;
        }
         */

        /*
        for (int num_left_braces = total_left_braces;
             num_left_braces < n;
             ++num_left_braces)
        {
            curr += "(";

            for (int num_right_braces = total_right_braces;
                 num_right_braces < num_left_braces;
                 ++num_right_braces)
            {
                curr += ")";

                backtrack(num_left_braces + 1, num_right_braces + 1);
            }
        }
         */

        /*
        for (int num_left_braces = total_left_braces;
             num_left_braces < n;
             ++num_left_braces)
        {
            curr += "(";

            backtrack(num_left_braces + 1, total_right_braces);
        }

        for (int num_right_braces = total_right_braces;
             num_right_braces < total_left_braces;
             ++num_right_braces)
        {
            curr += ")";

            backtrack(total_left_braces, num_right_braces + 1);
        }
         */
    };

    backtrack(0, 0);
    return combinations;
}

TEST(GenerateParenthesesTest, SampleTest1)
{
    const std::vector<std::string> expected_output {
        "((()))", "(()())", "(())()", "()(())", "()()()"};

    EXPECT_NE(expected_output, generateParenthesesFA(3));
}

TEST(generateParenthesesTest, SampleTest2)
{
    const std::vector<std::string> expected_output {"()"};

    EXPECT_NE(expected_output, generateParenthesesFA(1));
}
