from collections import deque

def longestSubarray(nums: list[int], limit: int) -> int:
    increasing = deque()
    decreasing = deque()
    left = ans = 0

    for right in range(len(nums)):
        # Maintain the monotonic deques
        while increasing and increasing[-1] > nums[right]:
            increasing.pop()
        while decreasing and decreasing[-1] < nums[right]:
            decreasing.pop()
        
        increasing.append(nums[right])
        decreasing.append(nums[right])

        # Maintain window property
        while decreasing[0] - increasing[0] > limit:
            if nums[left] == decreasing[0]:
                decreasing.popleft()
            if nums[left] == increasing[0]:
                increasing.popleft()
            
            left += 1
        
        ans = max(ans, right - left + 1)
    
    return ans
