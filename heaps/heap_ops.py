# Use heapq module which only implements min heaps
from heapq import *


# Declaration: heapq does not give you a heap data structure.
# You just use a normal list and heapq provides you with methods
# that can be used on this list to perform heap operations
heap = []

# Add to heap
heappush(heap, 1)
heappush(heap, 2)
heappush(heap, 3)

# Check minimum element
heap[0] # 1

# Pop minimum element
heappop(heap) # 1

# Get size
len(heap) # 2

# Convert a list to a heap in linear time
# Afterwards can use heappush and heappop on nums
# and nums[0] will always be the minimum element
nums = [43, 2, 13, 634, 120]
heapify(nums)

min_heap = [67, 341, 234, -67, 12, -976]
heapify(min_heap)

heappush(min_heap, 7451)
heappush(min_heap, -5352)

# The numbers will be printed in sorted order
while heap:
    print(heappop(heap))