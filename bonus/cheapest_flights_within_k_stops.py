from collections import defaultdict
from collections import deque


def findCheapestPriceDS1(
    n: int, flights: list[list[int]], src: int, dst: int, k: int
) -> int:
    adj = defaultdict(list)
    for flight in flights:
        adj[flight[0]].append([flight[1], flight[2]])

    costs = [float('inf')] * n

    city_cost = deque([(src, 0)])

    stops = 0
    while stops <= k and city_cost:
        level_size = len(city_cost)

        for _ in range(level_size, 0, -1):
            curr_city, cost_to_curr_city = city_cost.popleft()

            for neighbor, price in adj[curr_city]:
                if cost_to_curr_city + price >= costs[neighbor]:
                    continue

                costs[neighbor] = cost_to_curr_city + price
                city_cost.append((neighbor, costs[neighbor]))

        stops += 1

    return -1 if costs[dst] == float('inf') else costs[dst]
