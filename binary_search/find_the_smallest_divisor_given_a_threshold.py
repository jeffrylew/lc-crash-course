import math


def smallestDivisorDS1(nums: list[int], threshold: int) -> int:
    max_element = max(nums)

    # Iterate on all divisors
    for divisor in range(1, max_element + 1):
        sum_of_division_results = 0
        threshold_exceeded = False

        # Divide all numbers of array and sum the result
        for num in nums:
            sum_of_division_results += math.ceil((1.0 * num) / divisor)
            
            if sum_of_division_results > threshold:
                threshold_exceeded = True
                break
        
        # If threshold was not exceeded then return current divisor
        if not threshold_exceeded:
            return divisor
    
    return -1

def smallestDivisorDS2(nums: list[int], threshold: int) -> int:
    # Return the sum of division results with divisor
    def find_division_sum(divisor: int) -> int:
        result = 0
        for num in nums:
            result += math.ceil((1.0 * num) / divisor)
        return result
    
    ans = -1
    low = 1
    high = max(nums)

    # Iterate using binary search on all divisors
    while low <= high:
        mid = (low + high) // 2
        result = find_division_sum(mid)

        # If current divisor does not exceed threshold then it can be the answer
        # but also try smaller divisors - change search space to left half
        if result <= threshold:
            ans = mid
            high = mid - 1
        
        # Otherwise need a bigger divisor to reduce result sum
        # so change search space to right half
        else:
            low = mid + 1
    
    return ans
