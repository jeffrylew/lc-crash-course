public int findCheapestPriceDS1(int     n,
                                int[][] flights,
                                int     src,
                                int     dst,
                                int     k)
{
    Map<Integer, List<int[]>> adj = new HashMap<>();
    for (int[] flight : flights)
    {
        adj.computeIfAbsent(flight[0], value -> new ArrayList<>()).add(
            new int[] {flight[1], flight[2]});
    }

    // costs stores min price to reach city from src
    int[] costs = new int[n];
    Arrays.fill(costs, Integer.MAX_VALUE);

    // city_cost stores <city, cost> pairs
    Queue<int[]> city_cost = new LinkedList<>();
    city_cost.offer(new int[] {src, 0});

    int stops = 0;
    while (stops <= k && !city_cost.isEmpty())
    {
        int level_size = city_cost.size();

        // Iterate on current level
        while (level_size-- > 0)
        {
            int[] curr_city_cost = city_cost.poll();
            int curr_city = curr_city_cost[0];
            int cost_to_curr_city = curr_city_cost[1];

            if (!adj.containsKey(curr_city))
            {
                continue;
            }

            // Iterate over neighbors of popped city
            for (int[] nei_price : adj.get(curr_city))
            {
                int neighbor = nei_price[0];
                int price = nei_price[1];

                if (cost_to_curr_city + price >= costs[neighbor])
                {
                    continue;
                }

                costs[neighbor] = cost_to_curr_city + price;
                city_cost.offer(new int[] {neighbor, costs[neighbor]});
            }
        }
        stops++;
    }

    return costs[dst] == Integer.MAX_VALUE ? -1 : costs[dst];
}
