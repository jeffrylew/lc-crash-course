#include <gtest/gtest.h>

#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

//! @brief Check if all characters have equal number of occurrences
//! @param[in] s Input string
//! @return True if all characters have equal number of occurrences, else false
static bool areOccurrencesEqual(std::string s)
{
    //! @details Time complexity O(N) where N = s.size(). Costs O(N) to populate
    //!          hash map and O(N) to convert hash map's values to a set.
    //!          Space complexity O(N) for both the hash map and set

    std::unordered_map<char, int> counts {};
    for (char c : s)
    {
        ++counts[c];
    }

    std::unordered_set<int> frequencies {};
    /*
    for (auto [key, val] : counts)
    {
        frequencies.insert(val);
    }
    */
    for (const auto& kv : counts)
    {
        std::ignore = frequencies.emplace(kv.second);
    }

    return frequencies.size() == 1ULL;

} // static bool areOccurrencesEqual( ...

TEST(AreOccurrencesEqualTest, SampleTest)
{
    EXPECT_TRUE(areOccurrencesEqual("abacbc"));
    EXPECT_FALSE(areOccurrencesEqual("aaabb"));
}