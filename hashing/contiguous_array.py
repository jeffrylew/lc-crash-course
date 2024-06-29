def findMaxLengthDS1(nums: list[int]) -> int:
    max_len = 0
    nums_len = len(nums)

    for start in range(nums_len):
        zeros = 0
        ones = 0

        for end in range(start, nums_len):
            if nums[end] == 0:
                zeros += 1
            else:
                ones += 1

            if zeros == ones:
                max_len = max(max_len, end - start + 1)

    return max_len
