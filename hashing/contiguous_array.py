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


def findMaxLengthDS2(nums: list[int]) -> int:
    nums_len = len(nums)
    arr_of_counts = [-2] * (2 * nums_len + 1)
    arr_of_counts[nums_len] = -1

    max_len = 0
    count = 0

    for idx in range(nums_len):
        count += -1 if nums[idx] == 0 else 1

        idx_in_2n_plus_1 = count + nums_len
        if arr_of_counts[idx_in_2n_plus_1] >= -1:
            max_len = max(max_len, idx - arr_of_counts[idx_in_2n_plus_1])
        else:
            arr_of_counts[idx_in_2n_plus_1] = idx

    return max_len


def findMaxLengthDS3(nums: list[int]) -> int:
    count_idx = {0: -1}

    max_len = 0
    count = 0

    for idx in range(len(nums)):
        count += (-1 if nums[idx] == 0 else 1)

        if count in count_idx:
            max_len = max(max_len, idx - count_idx[count])
        else:
            count_idx[count] = idx

    return max_len
