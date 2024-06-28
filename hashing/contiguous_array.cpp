#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <vector>

//! @brief Get max length of a contiguous subarray with an equal number of 0, 1
//! @param[in] nums Vector of binary integers 0 and 1
//! @return Max length of a contiguous subarray with an equal number of 0 and 1
static int findMaxLengthFA(std::vector<int> nums)
{
    //! @details First attempt solution does not pass SampleTest3

    const auto       nums_size = static_cast<int>(nums.size());
    std::vector<int> prefix(nums.size() + 1U);
    for (int idx = 0; idx < nums_size; ++idx)
    {
        prefix[idx + 1] = prefix[idx] + nums[idx];
    }

    int max_len {};
    int right_bound {};
    for (int left_bound = 0; left_bound < nums_size; ++left_bound)
    {
        int window_sum {prefix[left_bound + 1] - prefix[right_bound]};
        int window_size {left_bound - right_bound + 1};

        if (window_sum * 2 == window_size)
        {
            max_len = std::max(max_len, window_size);
            continue;
        }

        while (window_sum * 2 > window_size)
        {
            window_sum  = prefix[left_bound + 1] - prefix[++right_bound];
            window_size = left_bound - right_bound + 1;

            if (window_sum * 2 == window_size)
            {
                max_len = std::max(max_len, window_size);
                break;
            }
        }
    }

    return max_len;

} // static int findMaxLengthFA( ...

//! @brief Brute force discussion solution
//! @param[in] nums Vector of binary integers 0 and 1
//! @return Max length of a contiguous subarray with an equal number of 0 and 1
static int findMaxLengthDS1(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/contiguous-array/editorial/
    //!
    //!          Time complexity O(N ^ 2) where N = nums.size(). Consider every
    //!          possible subarray by traversing over the complete vector for
    //!          every possible starting point.
    //!          Space complexity O(1) for zeros and ones.

    int max_len {};

    const auto nums_size = static_cast<int>(nums.size());

    for (int start = 0; start < nums_size; ++start)
    {
        int zeros {};
        int ones {};

        for (int end = start; end < nums_size; ++end)
        {
            if (nums[end] == 0)
            {
                ++zeros;
            }
            else
            {
                ++ones;
            }

            if (zeros == ones)
            {
                max_len = std::max(max_len, end - start + 1);
            }
        }
    }

    return max_len;

} // static int findMaxLengthDS1( ...

//! @brief Extra vector discussion solution
//! @param[in] nums Vector of binary integers 0 and 1
//! @return Max length of a contiguous subarray with an equal number of 0 and 1
static int findMaxLengthDS2(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/contiguous-array/editorial/
    //!
    //!          Comments say this solution is hard to understand and I agree.
    //!          Makes no sense, I won't implement this for the other languages.
    //!          Time complexity O(N) where N = nums.size(). The complete vector
    //!          is traversed only once.
    //!          Space complexity O(N) for vector arr_of_counts sized 2N + 1.

    const auto nums_size = static_cast<int>(nums.size());

    //! Initialize with -2 except at index nums_size, which is initialized to -1
    //! Discussion solution doesn't explain why
    std::vector<int> arr_of_counts(2U * nums.size() + 1U, -2);
    arr_of_counts[nums_size] = -1;

    int max_len {};
    int count {};

    for (int idx = 0; idx < nums_size; ++idx)
    {
        count += (nums[idx] == 0 ? -1 : 1);

        const int idx_in_2n_plus_1 {count + nums_size};
        if (arr_of_counts[idx_in_2n_plus_1] >= -1)
        {
            max_len = std::max(max_len, idx - arr_of_counts[idx_in_2n_plus_1]);
        }
        else
        {
            arr_of_counts[idx_in_2n_plus_1] = idx;
        }
    }

    return max_len;

} // static int findMaxLengthDS2( ...

//! @brief Hashmap discussion solution
//! @param[in] nums Vector of binary integers 0 and 1
//! @return Max length of a contiguous subarray with an equal number of 0 and 1
static int findMaxLengthDS3(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/contiguous-array/editorial/
    //!
    //!          Time complexity O(N) where N = nums.size(). The entire vector
    //!          is traversed only once.
    //!          Space complexity O(N). The max size of map count_idx will be N
    //!          if all elements are either 0 or 1.

    //! Map of <count, index>. <0, -1> implies sum is 0 before index 0
    //! It stores the first index when count is encountered
    std::unordered_map<int, int> count_idx {};
    count_idx.emplace(0, -1);

    int max_len {};
    int count {};

    for (int idx = 0; idx < static_cast<int>(nums.size()); ++idx)
    {
        count += (nums[idx] == 0 ? -1 : 1);

        //! Add <count, idx> if count is not in the map.
        //! Else, ret is a pair<iterator, bool> to retrieve the index at count
        auto [it, inserted_new_idx] = count_idx.try_emplace(count, idx);
        if (!inserted_new_idx)
        {
            //! (idx - it->second) is the number of elements between the first
            //! index when "count" is observed and the current index idx.
            //! Encountering count twice means the number of zeros and ones are
            //! equal between the indices.
            max_len = std::max(max_len, idx - it->second);
        }
    }

    return max_len;

} // static int findMaxLengthDS3( ...

TEST(FindMaxLengthTest, SampleTest1)
{
    EXPECT_EQ(2, findMaxLengthFA({0, 1}));
    EXPECT_EQ(2, findMaxLengthDS1({0, 1}));
    EXPECT_EQ(2, findMaxLengthDS2({0, 1}));
    EXPECT_EQ(2, findMaxLengthDS3({0, 1}));
}

TEST(FindMaxLengthTest, SampleTest2)
{
    EXPECT_EQ(2, findMaxLengthFA({0, 1, 0}));
    EXPECT_EQ(2, findMaxLengthDS1({0, 1, 0}));
    EXPECT_EQ(2, findMaxLengthDS2({0, 1, 0}));
    EXPECT_EQ(2, findMaxLengthDS3({0, 1, 0}));
}

TEST(FindMaxLengthTest, SampleTest3)
{
    const std::vector<int> nums {0, 0, 1, 0, 0, 0, 1, 1};

    EXPECT_EQ(0, findMaxLengthFA(nums));
    EXPECT_NE(6, findMaxLengthFA(nums));
    EXPECT_EQ(6, findMaxLengthDS1(nums));
    EXPECT_EQ(6, findMaxLengthDS2(nums));
    EXPECT_EQ(6, findMaxLengthDS3(nums));
}
