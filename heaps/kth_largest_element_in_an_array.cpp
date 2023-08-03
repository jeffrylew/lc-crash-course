#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <queue>
#include <random>
#include <vector>

//! @brief First attempt solution to get the kth largest element in the vector
//! @param[in] nums Vector of integers
//! @param[in] k    Defines which largest element to retrieve
//! @return The kth largest element in nums
static int findKthLargestFA(std::vector<int> nums, int k)
{
    //! @details Time complexity O(N + k * log k) where N = nums.size(). O(N) to
    //!          convert nums to a max heap. O(k * log k) for k pops from the
    //!          max heap (technically k - 1 pops).
    //!          Space complexity O(N) since max heap initially stores all ints.
    std::priority_queue<int> maxHeap(nums.cbegin(), nums.cend());

    while (k-- > 1)
    {
        maxHeap.pop();
    }

    return maxHeap.top();
}

//! @brief Discussion solution: Sort
//! @param[in] nums Vector of integers
//! @param[in] k    Defines which largest element to retrieve
//! @return The kth largest element in nums
static int findKthLargestDS1(std::vector<int> nums, int k)
{
    //! @details leetcode.com/problems/kth-largest-element-in-an-array/editorial
    //!
    //!          Time complexity O(N * log N) where N = nums.size(). Sorting
    //!          nums requires O(N * log N) time.
    //!          Space complexity O(log N) for C++. std::sort uses a hybrid of
    //!          Quick Sort, Heap Sort, and Insertion Sort with a worst case
    //!          space complexity of O(log N). In Java, Arrays.sort() for
    //!          primitives is O(log N) while sort() in Python is implemented
    //!          using Timsort which has a worst-case of O(N).

    std::sort(nums.begin(), nums.end(), std::greater<int>());
    return nums[k - 1];
}

//! @brief Discussion solution: Min-Heap
//! @param[in] nums Vector of integers
//! @param[in] k    Defines which largest element to retrieve
//! @return The kth largest element in nums
static int findKthLargestDS2(std::vector<int> nums, int k)
{
    //! @details leetcode.com/problems/kth-largest-element-in-an-array/editorial
    //!
    //!          Time complexity O(N * log k) where N = nums.size(). The heap
    //!          size is limited to a size of k so operations cost O(log k). We
    //!          iterate N times, performing one or two operations per element.
    //!          Because k <= N, this is an improvement over DS1.
    //!          Space complexity O(log k) for the min heap.

    //! std::priority_queue is a max heap so multiply values by -1 before
    //! pushing onto the heap. Or use
    //! std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    std::priority_queue<int> minHeap {};

    for (const int num : nums)
    {
        minHeap.push(-num);

        if (minHeap.size() > k)
        {
            minHeap.pop();
        }
    }

    return -minHeap.top();
}

//! @brief Get kth largest element in nums
//! @param[in, out] nums Reference to vector of ints
//! @param[in]      k    Defines which largest element to retrieve
//! @return kth largest element in nums
static int quickSelect(std::vector<int>& nums, int k)
{
    const int pivot {nums[std::minstd_rand() % nums.size()]};

    std::vector<int> left {};  //! Store elements greater than pivot
    std::vector<int> mid {};   //! Store elements equal to pivot
    std::vector<int> right {}; //! Store elements less than pivot

    for (const int num : nums)
    {
        if (num > pivot)
        {
            left.push_back(num);
        }
        else if (num < pivot)
        {
            right.push_back(num);
        }
        else
        {
            mid.push_back(num);
        }
    }

    //! kth largest element must be in left. Restart process in left.
    if (k <= static_cast<int>(left.size()))
    {
        return quickSelect(left, k);
    }

    //! kth largest element must be in right. Restart process in right but
    //! adjust k by left_mid_size since elements in left and mid are "deleted"
    const auto left_mid_size = static_cast<int>(left.size() + mid.size());
    if (left_mid_size < k)
    {
        return quickSelect(right, k - left_mid_size);
    }

    //! mid only has elements equal to the pivot
    return pivot;

} // static int quickSelect( ...

//! @brief Discussion solution: Quickselect
//! @param[in] nums Vector of integers
//! @param[in] k    Defines which largest element to retrieve
//! @return The kth largest element in nums
static int findKthLargestDS3(std::vector<int> nums, int k)
{
    //! @details leetcode.com/problems/kth-largest-element-in-an-array/editorial
    //!
    //!          Time complexity O(N) on average and O(N^2) in worst case where
    //!          N = nums.size(). Each call to quickSelect costs O(N) to iterate
    //!          over nums to create left, mid, and right. The number of times
    //!          it is called depends on how the pivot is chosen. On average,
    //!          size of nums decreases by a factor of ~2 on each call. Using
    //!          the master theorem with a = 1, b = 2, k = 1, we get
    //!          T(N) = T(N / 2) + O(N) = O(N)
    //!          Space complexity O(N) to create left, mid, and right.

    return quickSelect(nums, k);
}

TEST(FindKthLargestTest, SampleTest1)
{
    const std::vector<int> nums {3, 2, 1, 5, 6, 4};

    EXPECT_EQ(5, findKthLargestFA(nums, 2));
    EXPECT_EQ(5, findKthLargestDS1(nums, 2));
    EXPECT_EQ(5, findKthLargestDS2(nums, 2));
    EXPECT_EQ(5, findKthLargestDS3(nums, 2));
}

TEST(FindKthLargestTest, SampleTest2)
{
    const std::vector<int> nums {3, 2, 3, 1, 2, 4, 5, 5, 6};

    EXPECT_EQ(4, findKthLargestFA(nums, 4));
    EXPECT_EQ(4, findKthLargestDS1(nums, 4));
    EXPECT_EQ(4, findKthLargestDS2(nums, 4));
    EXPECT_EQ(4, findKthLargestDS3(nums, 4));
}