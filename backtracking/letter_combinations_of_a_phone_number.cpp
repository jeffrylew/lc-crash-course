#include <gtest/gtest.h>

#include <string>
#include <unordered_map>
#include <vector>

//! @brief Get all possible letter combinations of a string containing 2 - 9
//! @param[in] digits std::string mapping digits to letters like on a telephone
//! @return Vector of all possible letter combinations
static std::vector<std::string> letterCombinationsFA(std::string digits)
{
    if (digits.empty())
    {
        return {};
    }

    const std::unordered_map<char, std::vector<char>> graph {
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}}};

    std::vector<std::string> combinations {};
    std::string              curr_combination {};
    const auto               digits_size = static_cast<int>(digits.size());

    std::function<void(const std::string&, int)> backtrack =
        [&](const std::string& nums, int d_idx) {
            if (static_cast<int>(curr_combination.size()) == digits_size)
            {
                combinations.push_back(curr_combination);
                return;
            }

            for (int curr_idx = d_idx; curr_idx < digits_size; ++curr_idx)
            {
                for (const char letter : graph.at(nums[curr_idx]))
                {
                    curr_combination += letter;
                    backtrack(nums, curr_idx + 1);
                    curr_combination.pop_back();
                }
            }
        };

    backtrack(digits, 0);
    return combinations;
}

TEST(LetterCombinationsTest, SampleTest1)
{
    const std::vector<std::string> expected_output {
        "ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"
    };

    EXPECT_EQ(expected_output, letterCombinationsFA("23"));
}

TEST(LetterCombinationsTest, SampleTest2)
{
    EXPECT_TRUE(letterCombinationsFA("").empty());
}

TEST(LetterCombinationsTest, SampleTest3)
{
    const std::vector<std::string> expected_output {"a", "b", "c"};

    EXPECT_EQ(expected_output, letterCombinationsFA("2"));
}
