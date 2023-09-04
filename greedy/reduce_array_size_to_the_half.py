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