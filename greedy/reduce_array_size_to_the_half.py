import collections
import math


def minSetSizeDS1(arr: list[int]) -> int:
    # Sort the input numbers
    arr.sort()

    # Generate the counts array
    counts = []
    current_run = 1
    for i in range(1, len(arr)):
        if arr[i] == arr[i - 1]:
            current_run += 1
            continue

        counts.append(current_run)
        current_run = 1
    counts.append(current_run)

    # Reverse sort the counts
    counts.sort(reverse=True)

    # Remove numbers until at least half are removed
    numbers_removed_from_arr = 0
    set_size = 0

    for count in counts:
        numbers_removed_from_arr += count
        set_size += 1

        if numbers_removed_from_arr >= (len(arr) // 2):
            break
    
    return set_size


def minSetSizeDS2(arr: list[int]) -> int:
    # Store initial input length
    arr_len = len(arr)

    # Sort the input numbers
    arr.sort()

    # Space complexity optimization
    current_run = 1
    current_run_idx = 0
    for i in range(1, arr_len):
        if arr[i] == arr[i - 1]:
            current_run += 1
            continue

        arr[current_run_idx] = current_run
        current_run_idx += 1
        current_run = 1
    arr[current_run_idx] = current_run
    current_run_idx += 1

    del arr[current_run_idx:]

    # Reverse sort the counts
    arr.sort(reverse=True)

    # Remove numbers until at least half are removed
    numbers_removed_from_arr = 0
    set_size = 0

    for count in arr:
        numbers_removed_from_arr += count
        set_size += 1

        if numbers_removed_from_arr >= arr_len // 2:
            break
    
    return set_size


def minSetSizeDS3(arr: list[int]) -> int:
    # In Python, we can use the built-in Counter class
    counts = collections.Counter(arr)

    # Extract the counts in reverse-sorted order
    # most_common gives (number, count) pairs, reverse sorted on count
    counts = [count for _, count in counts.most_common()]

    # Remove numbers until at least half are removed
    total_removed = 0
    set_size = 0

    for count in counts:
        total_removed += count
        set_size += 1

        if total_removed >= (len(arr) // 2):
            break
    
    return set_size


def minSetSizeDS4(arr: list[int]) -> int:
    # In Python, we can use the built-in Counter class
    counts = collections.Counter(arr)
    max_value = max(counts.values())

    # Put the counts into buckets
    buckets = [0] * (max_value + 1)

    for count in counts.values():
        buckets[count] += 1

    # Determine set_size
    set_size = 0
    arr_numbers_to_remove = len(arr) // 2
    bucket = max_value

    while arr_numbers_to_remove > 0:
        max_needed_from_bucket = math.ceil(arr_numbers_to_remove / bucket)
        set_size_increase = min(buckets[bucket], max_needed_from_bucket)

        set_size += set_size_increase
        arr_numbers_to_remove -= set_size_increase * bucket
        bucket -= 1
    
    return set_size