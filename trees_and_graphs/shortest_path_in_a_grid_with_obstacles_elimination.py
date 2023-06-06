from collections import deque

def shortestPath1(grid: list[list[int]], k: int) -> int:
    """
    Runtime: 749 ms, Beats 25.26%
    Memory: 24.5 MB, Beats 16.53%
    """
    def valid(row, col):
        return 0 <= row < m and 0 <= col < n
    
    m = len(grid)
    n = len(grid[0])

    queue = deque([(0, 0, k, 0)])
    seen = {(0, 0, k)}
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    while queue:
        row, col, remain, steps = queue.popleft()
        if (row, col) == (m - 1, n - 1):
            return steps
        
        for dcol, drow in directions:
            next_row, next_col = row + drow, col + dcol

            if valid(next_row, next_col):
                if grid[next_row][next_col] == 0:
                    if (next_row, next_col, remain) not in seen:
                        seen.add((next_row, next_col, remain))
                        queue.append((next_row, next_col, remain, steps + 1))
                # Otherwise it is an obstacle and can pass if have removals
                elif remain and (next_row, next_col, remain - 1) not in seen:
                    seen.add((next_row, next_col, remain - 1))
                    queue.append((next_row, next_col, remain - 1, steps + 1))
    
    return -1

def shortestPath2(grid: list[list[int]], k: int) -> int:
    """
    Runtime: 237 ms, Beats 57.87%
    Memory: 16.7 MB, Beats 76.46%
    """
    def valid(row, col):
        return 0 <= row < m and 0 <= col < n
    
    m = len(grid)
    n = len(grid[0])

    queue = deque([(0, 0, k, 0)])

    # No point in returning to already visited square but with fewer removals
    seen = [[-1 for _ in range(n)] for _ in range(m)]

    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    while queue:
        row, col, remain, steps = queue.popleft()

        if (row, col) == (m - 1, n - 1):
            return steps

        # If current square is an obstacle, need to spend one removal
        if grid[row][col] == 1:
            if remain == 0:
                continue
            else:
                remain -= 1
        
        # If square already visited but with more removals then current path is
        # pointless since more removals is better
        if seen[row][col] >= remain:
            continue

        seen[row][col] = remain

        for dcol, drow in directions:
            next_row, next_col = row + drow, col + dcol

            if valid(next_row, next_col):
                queue.append((next_row, next_col, remain, steps + 1))
    
    return -1