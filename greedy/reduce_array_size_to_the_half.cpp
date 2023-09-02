#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <iterator>
#include <queue>
#include <set>
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

//! @brief Discussion solution: Sorting
//! @param[in] arr Vector of ints
//! @return Min set size so at least half of ints in arr are removed
static int minSetSizeDS1(std::vector<int> arr)
{
    //! @details leetcode.com/problems/reduce-array-size-to-the-half/editorial/
    //!
    //!          Time complexity O(N * log N) where N = arr.size() for sorting.
    //!          Generating counts takes O(N) due to linear scan of arr.
    //!          Computing min set size takes O(N) due to linear scan of counts.
    //!          Space complexity O(N). In worst case, all numbers in arr are
    //!          unique leading to counts of size N. C++ std::sort likely uses
    //!          O(log N) space due to a quicksort variation.
    //!
    //!          See DS2 for space optimization to O(1).

    const auto arr_size = static_cast<int>(arr.size());

    //! Sort the input numbers
    std::sort(arr.begin(), arr.end());

    //! Make vector of counts
    std::vector<int> counts {};

    int currentRun {1};
    for (int i = 1; i < arr_size; ++i)
    {
        if (arr[i] == arr[i - 1])
        {
            ++currentRun;
            continue;
        }

        counts.push_back(currentRun);
        currentRun = 1;
    }
    counts.push_back(currentRun);

    //! Sort counts in decreasing/reverse order
    std::sort(counts.begin(), counts.end(), std::greater<int>());

    //! Remove numbers until at least half are removed
    int numbersRemovedFromArr {};
    int setSize {};

    for (const int count : counts)
    {
        numbersRemovedFromArr += count;
        ++setSize;

        if (numbersRemovedFromArr >= arr_size / 2)
        {
            break;
        }
    }

    return setSize;

} // static int minSetSizeDS1( ...

//! @brief Discussion solution: Optimized sorting
//! @param[in] arr Vector of ints
//! @return Min set size so at least half of ints in arr are removed
static int minSetSizeDS2(std::vector<int> arr)
{
    //! @details leetcode.com/problems/reduce-array-size-to-the-half/editorial/
    //!
    //!          Time complexity O(N * log N), see DS1
    //!          Space complexity O(1). Optimization involves writing counts
    //!          into the input vector arr using the two pointer technique. Any
    //!          extra space at the end should be zeroed (or deleted if using a
    //!          language like Python). If the input vector cannot be modified
    //!          then an alternative optimization would be to use an O(1) space
    //!          sorting algorithm like heapsort or in-place merge sort. Would
    //!          need to implement these yourself.
    //!
    //!          94ms runtime (beats 99.34%)
    //!          54.9 MB memory (beats 100%)

    const auto arr_size = static_cast<int>(arr.size());

    //! Sort the input numbers
    std::sort(arr.begin(), arr.end());

    //! Space complexity optimization
    int currentRun {1};
    int currentRunIdx {};
    for (int i = 1; i < arr_size; ++i)
    {
        if (arr[i] == arr[i - 1])
        {
            ++currentRun;
            continue;
        }

        arr[currentRunIdx++] = currentRun;
        currentRun           = 1;
    }
    arr[currentRunIdx++] = currentRun;

    arr.erase(arr.begin() + currentRunIdx, arr.end());
    /**
     * Can also set to zero instead of deleting elements at currentRunIdx to end
     * 
     * for (int i = currentRunIdx; i < arr_size; ++i)
     * {
     *     arr[i] = 0;
     * }
     */

    //! Sort arr in decreasing/reverse order
    std::sort(arr.begin(), arr.end(), std::greater<int>());

    //! Remove numbers until at least half are removed
    int numbersRemovedFromArr {};
    int setSize {};

    for (const int count : arr)
    {
        numbersRemovedFromArr += count;
        ++setSize;

        if (numbersRemovedFromArr >= arr_size / 2)
        {
            break;
        }
    }

    return setSize;

} // static int minSetSizeDS2( ...

//! @brief Discussion solution: Hashing/Counting
//! @param[in] arr Vector of ints
//! @return Min set size so at least half of ints in arr are removed
static int minSetSizeDS3(std::vector<int> arr)
{
    //! @details leetcode.com/problems/reduce-array-size-to-the-half/editorial/
    //!
    //!          Editorial mentions std::multiset for element counting but it is
    //!          not better to use here. Constructing one from arr has time
    //!          complexity O(N * log N) to add elements in some sorted order.
    //!          However, we only care about keeping the counts of elements in
    //!          sorted order. This requires another O(N * log N) in the worst
    //!          case to iterate through the multiset and determine the counts.
    //!          It is more efficient to create a element frequencies map which
    //!          takes O(N) to iterate through arr and another O(N) in the worst
    //!          case to iterate through the map and retrieve the counts. See
    //!          runtime and memory benchmarks below.
    //!
    //!          Time complexity O(N * log N) for the hash map version
    //!          Space complexity O(N)

    const auto arr_size = static_cast<int>(arr.size());

    std::vector<int> counts {};

    /**
     * std::multiset solution:
     *     294ms runtime (beats 19.03%)
     *     95.96 MB memory (beats 5.02%)
     *
    //! Put elements of arr into countsSet (construction takes O(N * log N))
    std::multiset<int> countsSet(arr.begin(), arr.end());

    auto counts_it = countsSet.cbegin();
    while (counts_it != countsSet.cend()) // O(N) in worst case of unique ele
    {
        const auto it_pair = countsSet.equal_range(*counts_it); // O(log N)

        counts.push_back(std::distance(it_pair.first, it_pair.second));

        //! Update iterator to next unique int
        counts_it = it_pair.second;
    }
     * 
     */

    //! std::unordered_map solution:
    //!     133ms runtime (beats 91.74%)
    //!     78.5 MB memory (beats 61.28%)
    std::unordered_map<int, int> countsMap {};
    for (const int ele : arr) // O(N)
    {
        ++countsMap[ele];
    }

    for (const auto& kv : countsMap) // O(N) in worst case of unique ele
    {
        counts.push_back(kv.second);
    }

    //! Reverse sort counts vector O(N * log N)
    std::sort(counts.begin(), counts.end(), std::greater<int>());

    //! Remove numbers until at least half are removed
    int numbersRemovedFromArr {};
    int setSize {};

    for (const int count : counts)
    {
        numbersRemovedFromArr += count;
        ++setSize;

        if (numbersRemovedFromArr >= arr_size / 2)
        {
            break;
        }
    }

    return setSize;

} // static int minSetSizeDS3( ...

TEST(MinSetSizeTest, SampleTest1)
{
    EXPECT_EQ(2, minSetSizeFA({3, 3, 3, 3, 5, 5, 5, 2, 2, 7}));
    EXPECT_EQ(2, minSetSizeDS1({3, 3, 3, 3, 5, 5, 5, 2, 2, 7}));
    EXPECT_EQ(2, minSetSizeDS2({3, 3, 3, 3, 5, 5, 5, 2, 2, 7}));
    EXPECT_EQ(2, minSetSizeDS3({3, 3, 3, 3, 5, 5, 5, 2, 2, 7}));

    EXPECT_EQ(1, minSetSizeFA({7, 7, 7, 7, 7, 7}));
    EXPECT_EQ(1, minSetSizeDS1({7, 7, 7, 7, 7, 7}));
    EXPECT_EQ(1, minSetSizeDS2({7, 7, 7, 7, 7, 7}));
    EXPECT_EQ(1, minSetSizeDS3({7, 7, 7, 7, 7, 7}));
}