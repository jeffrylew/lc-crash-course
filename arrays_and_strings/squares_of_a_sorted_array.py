def sortedSquaresDS1(nums: List[int]) -> List[int]:
    """
    Time complexity O(N log N) where N = len(nums)
    Space complexity O(N) since list.sort() uses Timsort algorithm whose space
    complexity is O(N) (if we ignore space for output list)
    """
    
    return sorted(x * x for x in nums)


def sortedSquaresDS2(nums: List[int]) -> List[int]:
    N = len(nums)
    result = [0] * N
    left = 0
    right = N - 1
    for i in range(N - 1, -1, -1):
        if abs(nums[left]) < abs(nums[right]):
            square = nums[right]
            right -= 1
        else:
            square = nums[left]
            left += 1
        result[i] = square * square
    return result
