public int connectSticks(int[] sticks)
{
    int totalCost = 0;

    PriorityQueue<Integer> pq = new PriorityQueue<>();

    // Add all sticks to min heap
    for (int stick : sticks)
    {
        pq.add(stick);
    }

    // Combine two of smallest sticks until left with just one
    while (pq.size() > 1)
    {
        int stick1 = pq.remove();
        int stick2 = pq.remove();

        int cost = stick1 + stick2;
        totalCost += cost;

        pq.add(cost);
    }

    return totalCost;
}