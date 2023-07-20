#include <gtest/gtest.h>

#include <functional>
#include <queue>
#include <vector>

//! @class MedianFinder
//! @brief Finds the median in an ordered integer list
//! @details https://leetcode.com/problems/find-median-from-data-stream/
//!
//!          Use min heap to store greater half of data and max heap to store
//!          lesser half. Elements at the tops of both will be in the middle.
//!          If keep the heaps the same size and there is an even number of
//!          elements then the median is the average of the values at the top of
//!          both. When there is an odd number, we arbitrarily choose the max
//!          heap to store the median.
class MedianFinder
{
    //! Space complexity O(N) where N is number of times addNum has been called
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap {};
    std::priority_queue<int>                                      maxHeap {};

    public:
        MedianFinder() = default;

        //! @brief Add integer num to data structure
        //! @param[in] num Integer to add
        void addNum(int num)
        {
            //! @details Need to make sure difference between heap's sizes stays
            //!          the same or within one and that all elements in the min
            //!          heap are >= to all elements in the max heap. Algorithm:
            //!          1. Push num onto max heap (arbitrarily chosen)
            //!          2. Pop from max heap and push onto min heap. This is
            //!             how we ensure all in min heap are >= all in max heap
            //!          3. If min heap has more elements than max heap, pop
            //!             from min heap and push onto max heap. This is how we
            //!             maintain the decision to have the max heap store the
            //!             extra element if there are an odd number of elements
            //!
            //!          Time complexity O(log N) where N is number of times
            //!          addNum has been called so far.

            maxHeap.push(num);
            minHeap.push(maxHeap.top());
            maxHeap.pop();

            if (minHeap.size() > maxHeap.size())
            {
                maxHeap.push(minHeap.top());
                minHeap.pop();
            }
        }

        //! @brief Get median of all elements so far
        //! @return Median of elements so far
        double findMedian()
        {
            //! @details Time complexity O(1)

            if (maxHeap.size() > minHeap.size())
            {
                reurn maxHeap.top();
            }

            return (minHeap.top() + maxHeap.top()) / 2.0;
        }
};

TEST(MedianFinderTest, SampleTest)
{
    MedianFinder medianFinder {};

    medianFinder.addNum(1);
    medianFinder.addNum(2);
    EXPECT_EQ(1.5, medianFinder.findMedian());

    medianFinder.add(3);
    EXPECT_EQ(2.0, medianFinder.findMedian());
}
