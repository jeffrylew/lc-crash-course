def missingNumber(nums: List[int]) -> int:
    num_set = set(nums)

    expected_num_count = len(nums) + 1
    for number in range(expected_num_count):
        if number not in num_set:
            return number

