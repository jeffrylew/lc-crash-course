#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <string>

static bool checkIfPangramFA(std::string sentence)
{
    std::array<bool, 26> char_in_sentence {{}};

    for (const auto c : sentence)
    {
        const auto idx = static_cast<std::size_t>(c - 'a');
        char_in_sentence[idx] = true;
    }

    return std::none_of(char_in_sentence.cbegin(),
                        char_in_sentence.cend(),
                        [](bool ele) -> bool { return ele == false; });
}

TEST(CheckIfPangramTest, SampleTest)
{
    EXPECT_TRUE(checkIfPangramFA("thequickbrownfoxjumpsoverthelazydog"));
}