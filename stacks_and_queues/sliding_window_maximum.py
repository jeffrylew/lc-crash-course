from collections import deque

def maxSlidingWindow(nums: List[int], k: int) -> List[int]:
    ans = []
    deque = deque()

    for i in range(len(nums)):
        # Maintain monotonically decreasing deque
        # All elements in the deque smaller than the current one
        # have no chance of being the maximum so get rid of them
        while deque and nums[i] > nums[deque[-1]]:
            deque.pop()
        
        deque.append(i)

        # deque[0] is the index of the maximum element
        # If deque[0] + k == i then it is outside the window
        if deque[0] + k == i:
            deque.popleft()
        
        # Only add to the answer once our window has reached size k
        if i >= k - 1:
            ans.append(nums[deque[0]])
    
    return ans
