from collections import deque

class MovingAverage:
    def __init__(self, size: int):
        self.size = size
        self.queueDS1 = deque()
        self.window_sumDS1 = 0
        self.countDS1 = 0
    
    def nextDS1(self, val: int) -> float:
        '''
        Double-ended queue discussion solution
        '''
        
        self.countDS1 += 1
        # Calculate the new sum by shifting the window
        self.queueDS1.append(val)
        tail = self.queueDS1.popleft() if self.countDS1 > self.size else 0

        self.window_sumDS1 = self.window_sumDS1 - tail + val

        return self.window_sumDS1 / min(self.size, self.countDS1)