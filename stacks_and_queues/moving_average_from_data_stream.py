from collections import deque

class MovingAverage:
    def __init__(self, size: int):
        self.size = size
        self.queueDS1 = deque()
        self.window_sumDS1 = 0
        self.countDS1 = 0

        self.circ_queueDS2 = [0] * self.size
        self.headDS2 = 0
        self.window_sumDS2 = 0
        self.countDS2 = 0
    
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
    
    def nextDS2(self, val: int) -> float:
        '''
        Circular queue discussion solution
        '''

        self.countDS2 += 1
        # Calculate the new sum by shifting the window
        tail = (self.headDS2 + 1) % self.size
        self.window_sumDS2 = self.window_sumDS2 - self.circ_queueDS2[tail] + val
        # Move on to the next head
        self.headDS2 = tail
        self.circ_queueDS2[self.headDS2] = val
        return self.window_sumDS2 / min(self.size, self.countDS2)
