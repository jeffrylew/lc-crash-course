def findKthLargestDS1(nums: list[int], k: int) -> int:
    nums.sort(reverse=True)
    return nums[k - 1]

