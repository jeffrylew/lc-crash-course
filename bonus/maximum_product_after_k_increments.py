import heapq


def maximumProduct(nums: list[int], k: int) -> int:
    heapq.heapify(nums)

    for _ in range(k):
        heapq.heappush(nums, heapq.heappop(nums) + 1)

    modulus = 1_000_000_007
    ans = 1

    for ele in nums:
        ans = (ans * ele) % modulus

    return ans
