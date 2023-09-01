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