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
