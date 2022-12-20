def running_sum(nums: List[int]) -> List[int]:
    prefix = [nums[0]]

    for i in range(1, len(nums)):
        prefix.append(nums[i] + prefix[i - 1])
    
    return prefix