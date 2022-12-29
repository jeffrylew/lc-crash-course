from collections import defaultdict

def number_of_subarrays(nums: List[int], k: int) -> int:
    counts = defaultdict(int)
    counts[0] = 1

    ans = curr = 0
    for num in nums:
        curr += num % 2
        ans += counts[curr - k]
        counts[curr] += 1
    
    return ans

