#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Helper function to find insertion index for element >= target
//! @param[in] arr    Reference to sorted std::vector of ints (i.e. potions)
//! @param[in] target Insertion point is for element >= target as a double
//! @return Insertion index of element >= target
static int binarySearch(const std::vector<int>& arr, double target)
{
    int left {};
    int right {static_cast<int>(arr.size()) - 1};

    while (left <= right)
    {
        const int mid {left + (right - left) / 2};

        if (static_cast<double>(arr[mid]) < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return left;
}

//! @brief Get num of potions each spell can pair with to be successful
//! @param[in] spells  Vector where spells[i] = strength of ith spell
//! @param[in] potions Vector where potions[j] = strength of jth potion
//! @param[in] success Spell and potion pair is successful if product >= success
//! @return Vector of spells where ith element has num potions can pair with
static std::vector<int> successfulPairs(
    std::vector<int> spells, std::vector<int> potions, long long success)
{
    //! @details leetcode.com/problems/successful-pairs-of-spells-and-potions
    //!
    //!          Time complexity O((npotions * nspells) * log npotions).
    //!          Sorting potions costs O(npotions * log npotions). We iterate
    //!          nspells times, performing O(log npotions) binary search on each
    //!          iteration.
    //!          Space complexity O(log npotions) for C++ std::sort quicksort
    //!          variation.

    std::sort(portions.begin(), potions.end());
    const auto npotions = static_cast<int>(potions.size()); // = m

    std::vector<int> ans {};
    ans.reserve(spells.size()); // = n

    for (const int spell : spells)
    {
        const int insert_idx {
            binarySearch(potions, success / static_cast<double>(spell))};
        
        //! Final index is npotions - 1. If insertion index is insert_idx then
        //! the range [insert_idx, npotions - 1] has size
        //! (npotions - 1) - insert_idx + 1 = npotions - insert_idx
        ans.push_back(npotions - insert_idx);
    }

    return ans;
}

TEST(SuccessfulPairsTest, SampleTest1)
{
    const std::vector<int> expected_out {4, 0, 3};

    EXPECT_EQ(expected_out, successfulPairs({5, 1, 3}, {1, 2, 3, 4, 5}, 7LL));
}

TEST(SuccessfulPairsTest, SampleTest2)
{
    const std::vector<int> expected_output {2, 0, 2};

    EXPECT_EQ(expected_output, successfulPairs({3, 1, 2}, {8, 5, 8}, 16LL));
}