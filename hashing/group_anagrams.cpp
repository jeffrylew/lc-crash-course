#include <gtest/gtest.h>

#include <string>
#include <unordered_map>
#include <vector>

//! @brief Group anagrams together
//! @param[in] strs Vecor of strings to group
//! @return Vector of grouped anagrams
static std::vector<std::vector<std::string>> groupAnagrams(
    std::vector<std::string> strs)
{
    //! @details Let N = strs.size() and M = Average string length
    //!          Time complexity O(N * M * log M) to iterate over each string
    //!          and sort it, costing O(N * M * log M). Iterating over the keys
    //!          costs O(N) in the worst case of N groups with no anagrams.
    //!          Space complexity O(N * M) for each string in an array in map

    std::unordered_map<std::string, std::vector<std::string>> groups {};
    for (const auto& s : strs)
    {
        auto sorted_s = s;
        std::sort(sorted_s.begin(), sorted_s.end());
        groups[sorted_s].push_back(s);
    }

    std::vector<std::vector<std::string>> ans {};
    /*
    for (auto [key, val] : groups)
    */
    for (const auto& kv : groups)
    {
        ans.push_back(kv.second);
    }

    return ans;

} // static std::vector<std::vector<std::string>> groupAnagrams( ...

TEST(GroupAnagramsTest, SampleTest)
{
    const std::vector<std::string> input {
        "eat", "tea", "tan", "ate", "nat", "bat"};
    
    /*
    const std::vector<std::vector<std::string>> expected_output {
        {"eat", "tea", "ate"},
        {"tan", "nat"},
        {"bat"}};
    */
    
    const auto result = groupAnagrams(input);
    EXPECT_EQ(3ULL, result.size());
}