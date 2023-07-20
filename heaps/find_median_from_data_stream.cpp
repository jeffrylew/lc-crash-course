#include <gtest/gtest.h>

#include <functional>
#include <queue>
#include <vector>

class MedianFinder
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap {};
    std::priority_queue<int>                                      maxHeap {};

    public:
        MedianFinder() {}

        void addNum(int num)
        {
            maxHeap.push(num);
            minHeap.push(maxHeap.top());
            maxHeap.pop();

            if (minHeap.size() > maxHeap.size())
            {
                maxHeap.push(minHeap.top());
                minHeap.pop();
            }
        }

        double findMedian()
        {
            if (maxHeap.size() > minHeap.size())
            {
                reurn maxHeap.top();
            }

            return (minHeap.top() + maxHeap.top()) / 2.0;
        }
};
