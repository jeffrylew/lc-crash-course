from heapq import *

class MedianFinder:
    def __init__(self):
        self.min_heap = []
        self.max_heap = []
    
    def add_num(self, num: int) -> None:
        heappush(self.max_heap, -num)
        heappush(self.min_heap, -heappop(self.max_heap))

        if len(self.min_heap) > len(self.max_heap):
            heappush(self.max_heap, -heappop(self.min_heap))
    
    def find_median(self) -> float:
        if len(self.max_heap) > len(self.min_heap):
            return -self.max_heap[0]
        
        return (self.min_heap[0] - self.max_heap[0]) / 2.0
