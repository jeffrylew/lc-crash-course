from collections import defaultdict
from heapq import *
from math import inf


def networkDelayTime(times: list[list[int]], n: int, k: int) -> int:
    graph = defaultdict(list)
    for u, v, w in times:
        graph[u - 1].append([v - 1, w])

    distances = [inf] * n
    distances[k - 1] = 0

    min_heap = [(0, k - 1)]
    while min_heap:
        curr_dist, node = heappop(min_heap)
        if curr_dist > distances[node]:
            continue

        for neighbor, weight in graph[node]:
            dist = curr_dist + weight
            if dist < distances[neighbor]:
                distances[neighbor] = dist
                heappush(min_heap, (dist, neighbor))

    min_time = max(distances)
    return min_time if min_time < inf else -1
