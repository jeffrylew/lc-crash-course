#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <string>
#include <unordered_set>

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

static bool checkIfPangramDS1(std::string sentence)
{
    //! @details Time complexity O(N) where N = sentence.size()
    //!          Space complexity O(1) since there are 26 lowercase letters

    //! Add every letter of sentence to hash set seen
    std::unordered_set<char> seen(sentence.begin(), sentence.end());

    //! If the size of seen is 26 then sentence is a pangram
    return seen.size() == 26ULL;
}

static bool checkIfPangramDS2(std::string sentence)
{
    //! @details Map alphabet to bits, e.g. seen = 23 = (10111)_2 for a, b, c, e
    //!          1 0 1 1 1
    //!          e   c b a
    //!          To indicate presence of e.g. 'f', get ASCII index 'f' - 'a' = 5
    //!          Then left shift 1 by 5 bits: 1 << 5 = 32 = (100000)_2
    //!          Use OR to combine:
    //!                       0 1 0 1 1 1
    //!                     + 1 0 0 0 0 0
    //!          seen = 55 = (1 1 0 1 1 1)_2
    //!          Finally, if all 26 letters are present then will have 26 bits
    //!          of 1 in seen = [111...111]. seen + 1 = 1[000...000] = (1 << 26)
    //!
    //!          Time complexity O(N) to traverse over sentence once
    //           Space complexity O(1) to update one number seen

    //! Initialize seen = 0 since start with no letter
    int seen {};

    //! Iterate over sentence
    for (const auto currChar : sentence)
    {
        //! Map each currChar to its index using its ASCII code
        const auto mappedIndex = static_cast<int>(currChar - 'a');

        //! currBit represents the bit for currChar
        //! Left shifting by 1 equals multiplying by 2
        const int currBit = 1 << mappedIndex;

        //! Use OR operation
        seen |= currBit;
    }

    //! Once finish iterating, check if seen contains 26 bits of 1
    return seen + 1 == (1 << 26);
}

TEST(CheckIfPangramTest, SampleTest)
{
    EXPECT_TRUE(checkIfPangramFA("thequickbrownfoxjumpsoverthelazydog"));
    EXPECT_TRUE(checkIfPangramDS1("thequickbrownfoxjumpsoverthelazydog"));
    EXPECT_TRUE(checkIfPangramDS2("thequickbrownfoxjumpsoverthelazydog"));
}