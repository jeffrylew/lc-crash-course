#include <gtest/gtest.h>

#include <unordered_set>
#include <vector>

static std::vector<int> findNumbers(std::vector<int> nums)
{
    /*
    std::vector<int>        output;
    std::unordered_set<int> seen;
    for (const auto num : nums)
    {
        if (seen.emplace(num + 1).second && seen.emplace(num - 1).second)
        {
            output.push_back(num);
        }
    }

    return output;
    */
    
    std::vector<int>        ans;
    std::unordered_set<int> numsSet(nums.begin(), nums.end());

    for (const int num : nums)
    {
        if (numsSet.find(num + 1) == numsSet.end()
            && numsSet.find(num - 1) == numsSet.end())
        {
            ans.push_back(num);
        }
    }

    return ans;
}