from collections import deque

queue = deque()

queue.append(1)
queue.append(2)
queue.append(3)

while queue:
    print(queue.popleft())

if not queue:
    print("Queue is empty!")