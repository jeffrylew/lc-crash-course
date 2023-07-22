public int minStoneSum(int[] piles, int k)
{
    PriorityQueue<Integer> heap =
        new PriorityQueue<>(Comparator.reverseOrder());
    
    int totalSum = 0;
    for (int num : piles)
    {
        totalSum += num;
        heap.add(num);
    }

    for (int i = 0; i < k; i++)
    {
        int curr = heap.remove();
        int remove = curr / 2;
        total -= remove;
        heap.add(curr - remove);
    }

    return total;
}