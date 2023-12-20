#include <gtest/gtest.h>

#include <functional>
#include <queue>
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

//! @brief Brute force discussion solution
//! @param[in] n Number of pairs of parentheses
//! @return Vector of all combinations of well-formed parentheses
static std::vector<std::string> generateParenthesesDS1(int n)
{
    //! @details https://leetcode.com/problems/generate-parentheses/editorial/
    //!
    //!          Time complexity O(2 ^ (2n) * n). We generate all possible
    //!          strings of length 2n. At each character, there are two choices
    //!          '(' or ')', which means there are a total of 2 ^ (2n) unique
    //!          strings. For each string of length 2n, need to iterate through
    //!          to verify it is a valid combination, which takes O(n) average.
    //!          Space complexity O(2 ^ (2n) * n). Before dequeueing the first
    //!          string of length 2n, it has stored 2^(2n - 1) strings of length
    //!          n - 1, which takes O(2 ^ (2n) * n).

    std::vector<std::string> answer {};
    std::queue<std::string>  queue {""};

    std::function<bool(const std::string&)> isValid =
        [&](const std::string& pString) {
            int leftCount {};

            for (const char p : pString)
            {
                if (p == '(')
                {
                    ++leftCount;
                }
                else
                {
                    --leftCount;
                }

                if (leftCount < 0)
                {
                    return false;
                }
            }

            return leftCount == 0;
        };

    while (!queue.empty())
    {
        const auto curString = queue.front();
        queue.pop();

        //! If the length of curString is 2 * n,
        //! add it to 'answer' if it is valid
        if (static_cast<int>(curString.size()) == 2 * n)
        {
            if (isValid(curString))
            {
                answer.push_back(curString);
            }
            continue;
        }

        queue.push(curString + ")");
        queue.push(curString + "(");
    }

    return answer;

} // static std::vector<std::string> generateParenthesesDS1( ...

//! @brief Backtracking discussion solution
//! @param[in] n Number of pairs of parentheses
//! @return Vector of all combinations of well-formed parentheses
static std::vector<std::string> generateParenthesesDS2(int n)
{
    //! @details https://leetcode.com/problems/generate-parentheses/editorial/
    //!
    //!          Time complexity O(4 ^ n / sqrt(n)). The total number of valid
    //!          parentheses strings is O(4 ^ n / (n * sqrt(n))), see asymptotic
    //!          limit of nth Catalan num, en.wikipedia.org/wiki/Catalan_number.
    //!          Each string is copied into the answer vector, bringing
    //!          an additional n factor into the time complexity.
    //!          Space complexity O(n). Max depth of recursive call stack is 2n
    //!          and the total number of parentheses is 2n. At most O(n) levels
    //!          of recursion are created and each level consumes a constant
    //!          amount of space.

    std::vector<std::string> answer {};
    std::string              curString {};

    std::function<void(int, int)> backtrack =
        [&](int leftCount, int rightCount) {
            if (static_cast<int>(curString.size()) == 2 * n)
            {
                answer.push_back(curString);
                return;
            }

            if (leftCount < n)
            {
                curString += "(";
                backtrack(leftCount + 1, rightCount);
                curString.pop_back();
            }

            if (rightCount < leftCount)
            {
                curString += ")";
                backtrack(leftCount, rightCount + 1);
                curString.pop_back();
            }
        };

    backtrack(0, 0);
    return answer;

} // static std::vector<std::string> generateParenthesesDS2( ...

TEST(GenerateParenthesesTest, SampleTest1)
{
    const std::vector<std::string> expected_output {
        "((()))", "(()())", "(())()", "()(())", "()()()"};

    EXPECT_NE(expected_output, generateParenthesesFA(3));
    EXPECT_EQ(expected_output, generateParenthesesDS1(3));
    EXPECT_EQ(expected_output, generateParenthesesDS2(3));
}

TEST(generateParenthesesTest, SampleTest2)
{
    const std::vector<std::string> expected_output {"()"};

    EXPECT_NE(expected_output, generateParenthesesFA(1));
    EXPECT_EQ(expected_output, generateParenthesesDS1(1));
    EXPECT_EQ(expected_output, generateParenthesesDS2(1));
}
