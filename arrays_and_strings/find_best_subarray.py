def find_best_subarray(nums: List[int], k: int) -> int:
    curr = 0
    for i in range(k):
        curr += nums[i]
    
    max_sum = curr
    for i in range(k, len(nums)):
        curr += nums[i] - nums[i - k]
        max_sum = max(max_sum, curr)

    return max_sum