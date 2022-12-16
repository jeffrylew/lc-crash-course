def find_length(nums: List[int], k: int) -> int:
    left = curr = max_subarray_size = 0

    for right in range(len(nums)):
        curr += nums[right]
        while curr > k:
            curr -= nums[left]
            left += 1
        max_subarray_size = max(max_subarray_size, right - left + 1)
    
    return max_subarray_size
