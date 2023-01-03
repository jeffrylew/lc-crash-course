#include <gtest/gtest.h>

#include <string>
#include <unordered_map>

static bool canConstruct(std::string ransomNote, std::string magazine)
{
    //! @details https://leetcode.com/problems/ransom-note/solutions/540284/
    //!          official-solution/
    //!
    //!          Let M = magazine.size() and N = ransomNote.size()
    //!          Let K = number of unique characters across the ransom note and
    //!          magazine (won't be more than 26)
    //!          Time complexity O(M), if M < N then return false. The worst
    //!          case occurs when M >= N. Creating hash map of counts for
    //!          magazine is O(M). Iterating over ransom note is O(N) but M >= N
    //!          so this simplifies to O(M)
    //!          Space complexity O(K) or O(1). K is never more than 26, which
    //!          is a constant.

    if (ransomNote.size() > magazine.size())
    {
        return false;
    }

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