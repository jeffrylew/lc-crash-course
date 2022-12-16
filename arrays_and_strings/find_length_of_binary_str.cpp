#include <gtest/gtest.h>

#include <algorithm>
#include <string>

//! @brief Get length of longest substring containing only "1" with one op
//! @param[in] s String containing binary "0" and/or "1"
//! @return Length of longest substring
static int findLengthOfBinaryStr(std::string s)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /703/arraystrings/4502/
    //!
    //!          Sliding window condition is window.count("0") <= 1
    //!
    //!          Time complexity O(s.size()) since work done in each loop
    //!          iteration is amortized constant.
    //!          Space complexity is O(1) for a few integer variables

    //! curr keeps track of how many "0" currently have in window
    int left = 0, curr = 0, max_substr_length = 0;

    for (int right = 0; right < static_cast<int>(s.size()); ++right)
    {
        if (s[right] == '0')
        {
            ++curr;
        }
        
        while (curr > 1)
        {
            if (s[left] == '0')
            {
                --curr;
            }
            ++left;
        }

        max_substr_length = std::max(max_substr_length, right - left + 1);

    } // for (int right = 0; ...

    return max_substr_length;

} // static int findLengthOfBinaryStr( ...

TEST(FindLengthOfBinaryStr, SampleTest)
{
    EXPECT_EQ(4, findLengthOfBinaryStr("11001011"));
    EXPECT_EQ(5, findLengthOfBinaryStr("1101100111"));
}