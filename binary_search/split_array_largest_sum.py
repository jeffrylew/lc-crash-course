import functools
import itertools


def splitArrayDS1(nums: list[int], k: int) -> int:
    nums_len = len(nums)

    # Create a prefix sum array of nums
    prefix_sum = [0] + list(itertools.accumulate(nums))

    @functools.lru_cache(None)
    def get_min_largest_split_sum(curr_idx: int, subarr_count: int):
        # Base case: If there is only one subarray left then all remaining
        # numbers must go in the current subarray. Return sum of remaining nums
        if subarr_count == 1:
            return prefix_sum[nums_len] - prefix_sum[curr_idx]

        # Otherwise use recurrence relation to determine min largest subarray
        # sum between curr_idx and end of array with subarr_count subarrays left
        minimum_largest_split_sum = prefix_sum[nums_len]
        for i in range(curr_idx, nums_len - subarr_count + 1):
            # Store the sum of the first subarray
            first_split_sum = prefix_sum[i + 1] - prefix_sum[curr_idx]

            # Find the maximum subarray sum for the current first split
            largest_split_sum = max(first_split_sum,
                                    get_min_largest_split_sum(i + 1,
                                                              subarr_count - 1))

            # Find the minimum among all possible combinations
            minimum_largest_split_sum = min(minimum_largest_split_sum,
                                            largest_split_sum)

            if first_split_sum >= minimum_largest_split_sum:
                break

        return minimum_largest_split_sum

    return get_min_largest_split_sum(0, k)


def splitArrayDS2(nums: list[int], k: int) -> int:
    nums_len = len(nums)
    memo = [[0] * (k + 1) for _ in range(nums_len)]

    # Create a prefix sum array of nums
    prefix_sum = [0] + list(itertools.accumulate(nums))

    for subarr_count in range(1, k + 1):
        for curr_idx in range(nums_len):
            # Base Case: If there is only one subarray left then all remaining
            # numbers must go in the current subarray. Return sum of nums left
            if subarr_count == 1:
                memo[curr_idx][subarr_count] = (prefix_sum[nums_len] -
                                                prefix_sum[curr_idx])
                continue

            # Otherwise, use the recurrence relation to determine the minimum
            # largest subarray sum between curr_idx and the end of nums with
            # subarr_count subarrays remaining
            minimum_largest_split_sum = prefix_sum[nums_len]
            for i in range(curr_idx, nums_len - subarr_count + 1):
                # Store the sum of the first subarray
                first_split_sum = prefix_sum[i + 1] - prefix_sum[curr_idx]

                # Find the maximum subarray sum for the current first split
                largest_split_sum = max(first_split_sum,
                                        memo[i + 1][subarr_count - 1])

                # Find the minimum among all possible combinations
                minimum_largest_split_sum = min(minimum_largest_split_sum,
                                                largest_split_sum)

                if first_split_sum >= minimum_largest_split_sum:
                    break

            memo[curr_idx][subarr_count] = minimum_largest_split_sum

    return memo[0][k]


def splitArrayDS3(nums: list[int], k: int) -> int:
    def min_subarrays_required(max_sum_allowed: int) -> int:
        current_sum = 0
        splits_required = 0

        for element in nums:
            # Add element only if the sum doesn't exceed max_sum_allowed
            if current_sum + element <= max_sum_allowed:
                current_sum += element
            else:
                # If the element addition makes sum greater than max_sum_allowed
                # then increment the splits required and reset sum
                current_sum = element
                splits_required += 1

        # Return the number of subarrays, which is the number of splits + 1
        return splits_required + 1

    # Define the left and right boundaries of binary search
    left = max(nums)
    right = sum(nums)
    while left <= right:
        # Find the mid value
        max_sum_allowed = (left + right) // 2

        # Find the minimum splits. If splits_required is less than
        # or equal to k then move towards smaller values (left)
        if min_subarrays_required(max_sum_allowed) <= k:
            right = max_sum_allowed - 1
            minimum_largest_split_sum = max_sum_allowed
        else:
            # Move towards right if splits_required is more than k
            left = max_sum_allowed + 1

    return minimum_largest_split_sum
