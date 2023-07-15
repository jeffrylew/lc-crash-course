public int lastStoneWeight(int[] stones)
{
    // Create a max heap with Comparator.reverseOrder()
    PriorityQueue<Integer> heap =
        new PriorityQueue<>(Comparator.reverseOrder());
    
    for (int stone : stones)
    {
        heap.add(stone);
    }

    while (heap.size() > 1)
    {
        int first = heap.remove();
        int second = heap.remove();

        if (first != second)
        {
            heap.add(first - second);
        }
    }

    return heap.isEmpty() ? 0 : heap.remove();
}