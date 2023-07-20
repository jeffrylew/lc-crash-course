class MedianFinder
{
    private PriorityQueue<Integer> minHeap = new PriorityQueue<>();
    private PriorityQueue<Integer> maxHeap =
        new PriorityQueue<>(Comparator.reverseOrder());
    
    public void addNum(int num)
    {
        maxHeap.add(num);
        minHeap.add(maxHeap.remove());

        if (minHeap.size() > maxHeap.size())
        {
            maxHeap.add(minHeap.remove());
        }
    }

    public double findMedian()
    {
        if (maxHeap.size() > minHeap.size())
        {
            return maxHeap.peek();
        }

        return (minHeap.peek() + maxHeap.peek()) / 2.0;
    }
}