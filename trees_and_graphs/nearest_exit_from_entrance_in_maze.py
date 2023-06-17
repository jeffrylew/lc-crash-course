from collections import deque

def nearestExit(maze: list[list[str]], entrance: list[int]) -> int:
    rows, cols = len(maze), len(maze[0])
    directions = ((-1, 0), (0, -1), (1, 0), (0, 1))

    # Mark entrance as visited since it's not an exit
    start_row, start_col = entrance
    maze[start_row][start_col] = '+'

    # Start BFS from the entrance and use queue to store all cells to visit
    queue = deque([(start_row, start_col, 0)])

    while queue:
        curr_row, curr_col, curr_distance = queue.popleft()

        # For current cell, check its four neighbor cells
        for dcol, drow in directions:
            next_row, next_col = curr_row + drow, curr_col + dcol

            # If there exists an unvisited empty neighbor
            if (0 <= next_row < rows and 0 <= next_col < cols
                and maze[next_row][next_col] == "."):

                # If this empty cell is an exit, return distance + 1
                if (next_row == 0
                    or next_row == rows - 1
                    or next_col == 0
                    or next_col == cols - 1):
                    return curr_distance + 1
                
                # Else, add cell to queue and mark it as visited
                maze[next_row][next_col] = "+"
                queue.append((next_row, next_col, curr_distance + 1))
    
    # If finish without finding an exit, return -1
    return -1
