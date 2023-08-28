#include <gtest/gtest.h>

#include <queue>
#include <unordered_map>
#include <vector>

//! @brief First attempt to get min set size so >= half of ints in arr are gone
//! @param[in] arr Vector of ints
//! @return Min set size so at least half of ints in arr are removed
static int minSetSizeFA(std::vector<int> arr)
{
    //! Problem specifies arr.size() is even
    auto half_arr_size = static_cast<int>(arr.size()) / 2;

    //! <integer element, count>
    std::unordered_map<int, int> counts {};

    for (const int ele : arr)
    {
        if (++counts[ele] == half_arr_size)
        {
            return 1;
        }
    }

    //! Store element counts in max heap
    std::priority_queue<int> maxHeap {};
    for (const auto& kv : counts)
    {
        maxHeap.push(kv.second);
    }

    int set_size {};
    while (not maxHeap.empty())
    {
        const int ele_count {maxHeap.top()};
        maxHeap.pop();

        ++set_size;
        half_arr_size -= ele_count;

        if (half_arr_size <= 0)
        {
            return set_size;
        }
    }

    return set_size;

} // static int minSetSizeFA( ...

TEST(MinSetSizeTest, SampleTest1)
{
    EXPECT_EQ(2, minSetSizeFA({3, 3, 3, 3, 5, 5, 5, 2, 2, 7}));

    EXPECT_EQ(1, minSetSizeFA({7, 7, 7, 7, 7, 7}));
}