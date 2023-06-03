from collections import deque

def updateMatrix(mat: list[list[int]]) -> list[list[int]]:
    def valid(row, col):
        return 0 <= row < m and 0 <= col < n and mat[row][col] == 1

    # Can create copy of mat to avoid modifying the input
    m = len(mat)
    n = len(mat[0])

    queue = deque();
    seen = set();

    for row in range(m):
        for col in range(n):
            if mat[row][col] == 0:
                queue.append((row, col, 1))
                seen.add((row, col))
    
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    while queue:
        row, col, steps = queue.popleft()

        for dcol, drow in directions:
            next_row, next_col = row + drow, col + dcol

            if valid(next_row, next_col) and (next_row, next_col) not in seen:
                queue.append((next_row, next_col, steps + 1))
                seen.add((next_row, next_col))
                mat[next_row][next_col] = steps
    
    return mat
