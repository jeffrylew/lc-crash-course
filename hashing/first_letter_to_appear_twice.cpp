#include <gtest/gtest.h>

#include <string>
#include <unordered_set>

static char repeatedCharacter(std::string s)
{
    //! @details Time complexity O(N), each loop iteration runs in constant time
    //!          Space complexity is O(M) where M is number of allowable chars
    //!          in input. Could be O(1) if input only has chars from English
    //!          alphabet (constant 26).

    std::unordered_set<char> seen {};
    for (char c : s)
    {
        if (not seen.emplace(c).second)
        {
            return c;
        }
    }

    return ' ';

} // static char repeatedCharacter( ...

TEST(RepeatedCharacterTest, SampleTest)
{
    EXPECT_EQ('d', repeatedCharacter("abcdeda"));
}