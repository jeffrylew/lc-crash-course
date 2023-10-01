def minimumEffortPath(heights: list[list[int]]) -> int:
    def valid(row, col):
        return 0 <= row < nrows and 0 <= col < ncols
    
    def check(effort):
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        seen = {(0, 0)}
        stack = [(0, 0)]

        while stack:
            row, col = stack.pop()
            if (row, col) == (nrows - 1, ncols - 1):
                return True
            
            for dcol, drow in directions:
                next_row, next_col = row + drow, col + dcol

                if (valid(next_row, next_col) and
                    (next_row, next_col) not in seen):
                    if (abs(heights[next_row][next_col] - heights[row][col])
                        <= effort):
                        seen.add((next_row, next_col))
                        stack.append((next_row, next_col))
        
        return False
    
    nrows = len(heights)
    ncols = len(heights[0])
    left = 0
    right = max(max(row) for row in heights)

    while left <= right:
        mid = (left + right) // 2
        if check(mid):
            right = mid - 1
        else:
            left = mid + 1
    
    return left