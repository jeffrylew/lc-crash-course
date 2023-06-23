from collections import deque

def snakesAndLaddersBFS(board: list[list[int]]) -> int:
    n = len(board)
    cells = [None] * (n**2 + 1)

    label = 1
    columns = list(range(0, n))

    for row in range(n - 1, -1, -1):
        for column in columns:
            cells[label] = (row, column)
            label += 1
        columns.reverse()
    
    dist = [-1] * (n**2 + 1)
    dist[1] = 0

    queue = deque([1])
    while queue:
        curr = queue.popleft()

        for next in range(curr + 1, min(curr + 6, n**2) + 1):
            row, col = cells[next]
            destination = board[row][col] if board[row][col] != -1 else next

            if dist[destination] == -1:
                dist[destination] = dist[curr] + 1
                queue.append(destination)
    
    return dist[n * n]