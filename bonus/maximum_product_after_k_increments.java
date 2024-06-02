public int maximumProduct(int[] nums, int k)
{
    PriorityQueue<Integer> heap = new PriorityQueue<>();
    for (int num : nums)
    {
        heap.add(num);
    }

    for (int num_ops = 0; num_ops < k; num_ops++)
    {
        heap.add(heap.remove() + 1);
    }

    int modulus = 1_000_000_007;
    long ans = 1;

    while (!heap.isEmpty())
    {
        ans = (ans * heap.remove()) % modulus;
    }

    return (int) ans;
}
