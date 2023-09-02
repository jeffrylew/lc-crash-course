from heapq import *


def maxNumberOfApplesDS1(weight: list[int]) -> int:
    weight.sort()
    apples = units = 0

    for ele in weight:
        units += ele

        if units > 5000:
            break

        apples += 1
    
    return apples


def maxNumberOfApplesDS2(weight: list[int]) -> int:
    heapify(weight)
    apples = units = 0

    # Note that arr[0] always represents the smallest element in the min-heap
    while weight and units + weight[0] <= 5000:
        units += heappop(weight)
        apples += 1
    
    return apples


def maxNumberOfApplesDS3(weight: list[int]) -> int:
    # Initialize the bucket to store all elements
    size = max(weight) + 1
    bucket = [0] * size
    for ele in weight:
        bucket[ele] += 1
    
    apples = units = 0
    for i in range(size):
        # If we have apples of i units of weight
        if bucket[i] != 0:
            # We need to make sure that:
            # 1. We do not take more apples than those provided
            # 2. We do not exceed 5000 units of weight
            take = min(bucket[i], (5000 - units) // i)

            if take == 0:
                break

            apples += take
            units += take * i
    
    return apples