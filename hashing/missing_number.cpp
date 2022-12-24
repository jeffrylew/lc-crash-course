#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
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

TEST(MissingNumberTest, SampleTest)
{
    EXPECT_EQ(2, missingNumberFA({3, 0, 1}));
}