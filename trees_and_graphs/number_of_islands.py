def numIslands(grid: list[list[str]]) -> int:
    def valid(row, col):
        return 0 <= row < m and 0 <= col < n and grid[row][col] == "1"
    
    def dfsRecursive(row, col):
        for drow, dcol in directions:
            next_row, next_col = row + drow, col + dcol
            if valid(next_row, next_col) and (next_row, next_col) not in seen:
                seen.add((next_row, next_col))
                dfsRecursive(next_row, next_col)
    
    def dfsIterative(start_row, start_col):
        stack = [(start_row, start_col)]
        while stack:
            row, col = stack.pop()
            for drow, dcol in directions:
                next_row, next_col = row + drow, col + dcol
                if valid(next_row, next_col) and (next_row, next_col) not in seen:
                    seen.add((next_row, next_col))
                    stack.append((next_row, next_col))
    
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    seen = set()
    ans = 0
    m = len(grid)
    n = len(grid[0])

    for row in range(m):
        for col in range(n):
            if grid[row][col] == "1" and (row, col) not in seen:
                ans += 1
                seen.add((row, col))
                dfsRecursive(row, col)
                # dfsIterative(row, col)
    
    return ans
