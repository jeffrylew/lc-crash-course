def binary_search(arr: list[int], target: int) -> int:
    left = 0
    right = len(arr) - 1

    while left <= right:
        mid = (left + right) // 2

        if arr[mid] == target:
            # Do something
            return mid
        
        if arr[mid] > target:
            right = mid - 1
        else:
            left = mid + 1
    
    # Target is not in arr but left is at the insertion point
    return left


def binary_search_first_index(arr: list[int], target: int) -> int:
    left = 0
    right = len(arr)

    while left < right:
        mid = (left + right) // 2

        if arr[mid] >= target:
            right = mid
        else:
            left = mid + 1
    
    return left


def binary_search_last_index(arr: list[int], target: int) -> int:
    left = 0
    right = len(arr)

    while left < right:
        mid = (left + right) // 2

        if arr[mid] > target:
            right = mid
        else:
            left = mid + 1
    
    return left