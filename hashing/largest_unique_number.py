def largestUniqueNumber(nums: List[int]) -> int:
    counts = {}
    for num in nums:
        counts[num] = counts.get(num, 0) + 1
    
    result = -1
    for num, freq in counts.items():
        if freq == 1:
            result = max(result, num)
    
    return result
