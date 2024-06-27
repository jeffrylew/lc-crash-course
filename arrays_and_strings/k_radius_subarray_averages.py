def getAveragesDS1(nums: list[int], k: int) -> list[int]:
    # When a single element is considered then its average is the num itself
    if k == 0:
        return nums

    window_size = 2 * k + 1
    nums_len = len(nums)
    averages = [-1] * nums_len

    # Case when any index does not have k elements on either side
    if window_size > nums_len:
        return averages

    # Generate prefix array for nums
    # prefix[idx + 1] is the sum of all elements from index 0 to idx
    prefix = [0] * (nums_len + 1)
    for idx in range(nums_len):
        prefix[idx + 1] = prefix[idx] + nums[idx]

    # Only iterate on indices that have at least k elements on either side
    # i.e. Indices from k (inclusive) to nums_len - k (exclusive)
    for idx in range(k, nums_len - k):
        leftBound, rightBound = idx - k, idx + k
        subArraySum = prefix[rightBound + 1] - prefix[leftBound]
        averages[idx] = subArraySum // window_size

    return averages


def getAveragesDS2(nums: list[int], k: int) -> list[int]:
    # When a single element is considered then its average is the num itself
    if k == 0:
        return nums

    window_size = 2 * k + 1
    nums_len = len(nums)
    averages = [-1] * nums_len

    # Case when any index does not have k elements on either side
    if window_size > nums_len:
        return averages

    # Get sum of first window in nums array
    window_sum = sum(nums[:window_size])
    averages[k] = window_sum // window_size

    # Iterate on rest of indices that have at least k elements on either side
    for idx in range(window_size, nums_len):
        # Remove discarded element and add new element for current window sum
        # idx is index of newly inserted element
        # (idx - window_size) is index of last removed element
        window_sum = window_sum - nums[idx - window_size] + nums[idx]
        averages[idx - k] = window_sum // window_size

    return averages
