from collections import defaultdict

def subarraySum(nums: List[int], k: int) -> int:
    counts = defaultdict(int)
    counts[0] = 1

    ans = curr = 0
    for num in nums:
        curr += num
        ans += counts[num - k]
        counts[curr] += 1
    
    return ans
