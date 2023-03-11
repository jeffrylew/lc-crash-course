#include <gtest/gtest.h>

#include <queue>
#include <vector>

//! @brief First attempt to get next greater element from nums2 for nums1[i]
//! @param[in] nums1 Vector of integers that is a subset of nums2
//! @param[in] nums2 Vector of integers
//! @return Vector of length nums1 containing next greater elements
static std::vector<int> nextGreaterElementFA(std::vector<int> nums1,
                                             std::vector<int> nums2)
{
    //! @details I know this is incorrect, need to use queue2 somehow...

    std::queue<int> queue2 {};

    int idx1 {};
    int idx2 {};

    while (idx1 < nums1.size())
    {
        while (idx2 < nums2.size() && nums2[idx2] <= nums1[idx1])
        {
            queue2.push(nums2[idx2++]);
        }

        nums1[idx1++] = (idx2 == nums2.size()) ? -1 : nums2[idx2];
    }

    return nums1;

} // static std::vector<int> nextGreaterElementFA( ...

TEST(NextGreaterElementTest, SampleTest)
{
    const std::vector<int> expected_output {-1, 3, -1};
    EXPECT_NE(expected_output, nextGreaterElementFA({4, 1, 2}, {1, 3, 4, 2}));
}