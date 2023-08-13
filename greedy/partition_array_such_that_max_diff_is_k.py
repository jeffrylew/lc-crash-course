def partitionArray(nums: list[int], k: int) -> int:
    nums.sort()

    ans = 1
    x = nums[0]

    for i in range(1, len(nums)):
        if nums[i] - x > k:
            x = nums[i]
            ans += 1
    
    return ans