import random
from heapq import *


def findKthLargestDS1(nums: list[int], k: int) -> int:
    nums.sort(reverse=True)
    return nums[k - 1]


def findKthLargestDS2(nums: list[int], k: int) -> int:
    min_heap = []
    for num in nums:
        heappush(min_heap, num)

        if len(min_heap) > k:
            heappop(min_heap)
    
    return min_heap[0]


def findKthLargestDS3(nums: list[int], k: int) -> int:
    def quick_select(nums, k):
        pivot = random.choice(nums)

        left, mid, right = [], [], []

        for num in nums:
            if num > pivot:
                left.append(num)
            elif num < pivot:
                right.append(num)
            else:
                mid.append(num)
        
        if k <= len(left):
            return quick_select(left, k)
        
        if len(left) + len(mid) < k:
            return quick_select(right, k - len(left) - len(mid))
        
        return pivot

    return quick_select(nums, k)


def findKthLargestDS4(nums: list[int], k: int) -> int:
    min_value = min(nums)
    max_value = max(nums)
    count = [0] * (max_value - min_value + 1)

    for num in nums:
        count[num - min_value] += 1
    
    remain = k
    for num in range(len(count) - 1, -1, -1):
        remain -= count[num]

        if remain <= 0:
            return num + min_value
    
    return -1
