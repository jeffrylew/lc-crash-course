#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <tuple>
#include <unordered_set>
#include <vector>

//! @brief First attempt solution using bit manipulation can't do 99+ shifts
//! @param[in] nums Vector of n distinct numbers in range [0, n]
//! @return The only number in the range that is missing from the input vector
static int missingNumberFA(std::vector<int> nums)
{
    //! Size of input
    const auto num_size = static_cast<std::uint64_t>(nums.size());
    
    //! Should consists of num_size ones in binary (111...111)_2
    const auto expected_bits = static_cast<std::uint64_t>((1ULL << num_size) - 1ULL);
    
    //! Tracks if numbers in [1, n] exist as binary
    std::uint64_t all_bits {};
    
    //! Flag tracking whether a zero exists or not
    bool has_zero {};
    
    for (const auto num : nums)
    {
        if (num == 0)
        {
            //! Zero int has been found
            has_zero = true;
        }
        else
        {
            //! Get binary representation of current int
            const auto curr_bit = static_cast<std::uint64_t>(1ULL << (num - 1ULL));

            //! Add current converted int to all_bits
            all_bits |= curr_bit;
        }
    }
    
    if (not has_zero)
    {
        //! 0 is missing, return it
        return 0;
    }
    else
    {
        //! Return missing number, add 1 since using 1-based index
        return 1 + static_cast<int>(std::log2(expected_bits - all_bits));
    }

} // static int missingNumberFA( ...

//! @brief Second attempt solution using sum of numbers in [1, n]
//! @param[in] nums Vector of n distinct numbers in range [0, n]
//! @return The only number in the range that is missing from the input vector
static int missingNumberSA(std::vector<int> nums)
{
    //! Size of input is max value of n
    const auto num_size = static_cast<int>(nums.size());

    //! Sum of numbers in [1, n] is
    //!     [1 +    2    + ... + (n - 1) + n]
    //!   + [n + (n - 1) + ... +    2    + 1]
    //!   = n * (n + 1)/2
    int sum_1_to_n {num_size * (num_size + 1) / 2};

    //! Flag tracking whether a zero exists or not
    bool has_zero {};

    for (const auto num : nums)
    {
        if (num == 0)
        {
            //! Zero int has been found
            has_zero = true;
        }
        else
        {
            //! Subtract current num from sum_1_to_n
            sum_1_to_n -= num;
        }
    }

    return !has_zero ? 0 : sum_1_to_n;

} // static int missingNumberSA( ...

//! @brief First discussion solution
//! @param[in] nums Vector of n distinct numbers in range [0, n]
//! @return The only number in the range that is missing from the input vector
static int missingNumberDS1(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/missing-number/solutions/127673/
    //!          official-solution/
    //!          Time complexity O(N)
    //!          Space complexity O(N)

    std::unordered_set<int> numSet {};

    for (const auto num : nums)
    {
        std::ignore = numSet.emplace(num);
    }

    const auto expectedNumCount = 1 + static_cast<int>(nums.size());
    for (int number = 0; number < expectedNumCount; ++number)
    {
        if (numSet.count(number) == 0)
        {
            return number;
        }
    }

    return -1;

} // static int missingNumberDS1( ...

//! @brief Second discussion solution using XOR bit manipulation
//! @param[in] nums Vector of n distinct numbers in range [0, n]
//! @return The only number in the range that is missing from the input vector
static int missingNumberDS2(std::vector<int> nums)
{
    //! @details Time complexity O(N)
    //!          Space complexity O(1)
    //!
    //!          Index: 0 1 2 3
    //!          Value: 0 1 3 4, nums.size() = 4
    //!          missing = 4 ^ (0 ^ 0) ^ (1 ^ 1) ^ (2 ^ 3) ^ (3 ^ 4)
    //!                  = (4 ^ 4) ^ (0 ^ 0) ^ (1 ^ 1) ^ (3 ^ 3) ^ 2
    //!                  =    0    ^    0    ^    0    ^    0    ^ 2
    //!                  = 2

    const auto nums_size = static_cast<int>(nums.size());
    int        missing {nums_size};
    for (int i = 0; i < nums_size; ++i)
    {
        missing ^= i ^ nums[i];
    }
    return missing;

} // static int missingNumberDS2( ...

TEST(MissingNumberTest, SampleTest)
{
    EXPECT_EQ(2, missingNumberFA({3, 0, 1}));
    EXPECT_EQ(2, missingNumberSA({3, 0, 1}));
    EXPECT_EQ(2, missingNumberDS1({3, 0, 1}));
    EXPECT_EQ(2, missingNumberDS2({3, 0, 1}));
}