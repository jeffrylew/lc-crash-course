def num_subarray_product_less_than_k(nums: List[int], k: int) -> int:
    if k <= 1:
        return 0

    num_subarrays = left = 0
    curr_product = 1

    for right in range(len(nums)):
        curr_product *= nums[right]
        
        while curr_product >= k:
            curr_product //= nums[left]
            left += 1

        num_subarrays += right - left + 1
    
    return num_subarrays
