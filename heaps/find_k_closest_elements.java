public List<Integer> findClosestElementsDS1(int[] arr, int k, int x)
{
    PriorityQueue<Integer> maxHeap = new PriorityQueue<>((n1, n2) -> {
        if (Math.abs(n1 - x) == Math.abs(n2 - x))
        {
            return n2 - n1;
        }

        return Math.abs(n2 - x) - Math.abs(n1 - x);
    });

    for (int num : arr)
    {
        maxHeap.add(num);

        if (maxHeap.size() > k)
        {
            maxHeap.remove();
        }
    }

    List<Integer> ans = new ArrayList<>();
    for (int i = 0; i < k; i++)
    {
        ans.add(maxHeap.remove());
    }

    Collections.sort(ans);
    return ans;
}