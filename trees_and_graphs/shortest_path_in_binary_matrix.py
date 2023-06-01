from collections import deque

def shortestPathBinaryMatrix(grid: list[list[int]]) -> int:
    if grid[0][0] == 1:
        return -1
    
    def valid(row, col):
        return 0 <= row < n and 0 <= col < n and grid[row][col] == 0
    
    n = len(grid)
    seen = {(0, 0)}
    queue = deque([0, 0, 1]) # row, col, steps

    directions = [
        (0, 1), (1, 0), (1, 1), (-1, -1), (-1, 1), (1, -1), (0, -1), (-1, 0)]

    while queue:
        row, col, steps = queue.popleft()

        if (row, col) == (n - 1, n - 1):
            return steps
        
        for dcol, drow in directions:
            next_row, next_col = row + drow, col + dcol

            if valid(next_row, next_col) and (next_row, next_col) not in seen:
                seen.add((next_row, next_col))
                queue.append((next_row, next_col, steps + 1))
    
    return -1


