import heapq

def lastStoneWeight(stones: list[int]) -> int:
    stones = [-stone for stone in stones]

    # Turn an array into a heap in linear time
    heapq.heapify(stones)

    while len(stones) > 1:
        first = abs(heapq.heappop(stones))
        second = abs(heapq.heappop(stones))

        if first != second:
            heapq.heappush(stones, -(first - second))
    
    return -stones[0] if stones else 0