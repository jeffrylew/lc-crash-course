def minStartValue(nums: List[int]) -> int:
    min_val = total = 0

    for num in nums:
        total += num
        min_val = min(min_val, total)
    
    return 1 - min_val