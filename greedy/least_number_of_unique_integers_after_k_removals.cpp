#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

//! @brief Find least number of unique ints after removing exactly k elements
//! @param[in] arr Vector of ints
//! @param[in] k   Number of elements to remove
//! @return Least number of unique integers after removing exactly k elements
static int findLeastNumOfUniqueInts(std::vector<int> arr, int k)
{
    //! @details https://leetcode.com/problems/
    //!          least-number-of-unique-integers-after-k-removals/
    //!
    //!          Time complexity O(N * log N) where N = arr.size(). In the worst
    //!          case scenario where all elements are unique, there will be n
    //!          keys in the hash map so sorting costs O(N * log N). Each while
    //!          loop iteration runs in O(1) and it can run N times at most,
    //!          giving a final time complexity of O(N * log N).
    //!          Space complexity is O(N) due to the hash map.
    
    std::unordered_map<int, int> counts {};
    for (const int num : arr)
    {
        ++counts[num];
    }

    std::vector<int> ordered {};
    for (const auto& kv : counts)
    {
        ordered.push_back(kv.second);
    }

    std::sort(ordered.begin(), ordered.end(), std::greater<int>());
    while (k > 0)
    {
        const int val {ordered.back()};
        if (val <= k)
        {
            k -= val;
            ordered.pop_back();
        }
        else
        {
            break;
        }
    }

    return static_cast<int>(ordered.size());
}