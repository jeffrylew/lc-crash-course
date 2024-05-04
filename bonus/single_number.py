def singleNumber(nums: list[int]) -> int:
    mask = 0
    for num in nums:
        mask ^= num

    return mask
