from heapq import *


def connectSticks(sticks: list[int]) -> int:
    total_cost = 0

    min_heap = sticks
    heapify(min_heap)

    while len(min_heap) > 1:
        stick1, stick2 = heappop(min_heap), heappop(min_heap)

        cost = stick1 + stick2
        total_cost += cost

        heappush(min_heap, cost)

    return total_cost