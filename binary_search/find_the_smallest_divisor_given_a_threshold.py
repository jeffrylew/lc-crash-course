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
