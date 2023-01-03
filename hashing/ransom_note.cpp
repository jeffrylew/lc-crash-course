#include <gtest/gtest.h>

#include <string>
#include <unordered_map>

static bool canConstruct(std::string ransomNote, std::string magazine)
{
    std::unordered_map<char, int> magazine_dic {};
    for (const char c : magazine)
    {
        ++magazine_dic[c];
    }

    for (const char c : ransomNote)
    {
        if (magazine_dic.count(c) == 0)
        {
            return false;
        }

        if (magazine_dic[c] == 0)
        {
            return false;
        }
        --magazine_dic[c];
    }

    return true;

} // static bool canConstruct( ...

TEST(CanConstructTest, SampleTest)
{
    EXPECT_FALSE(canConstruct("a", "b"));
}