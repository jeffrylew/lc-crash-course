import copy


def uniquePathsWithObstaclesDS(obstacleGrid: list[list[int]]) -> int:
    # If starting cell has an obstacle then return
    # since there are no paths to the destination
    if obstacleGrid[0][0] == 1:
        return 0

    num_rows = len(obstacleGrid)
    num_cols = len(obstacleGrid[0])

    # Assuming cannot modify input, create a copy
    grid = copy.deepcopy(obstacleGrid)

    # Number of ways of reaching the starting cell is 1
    grid[0][0] = 1

    # Fill values for first column
    for row in range(1, num_rows):
        grid[row][0] = int(grid[row][0] == 0 and grid[row - 1][0] == 1)

    # Fill values for first row
    for col in range(1, num_cols):
        grid[0][col] = int(grid[0][col] == 0 and grid[0][col - 1] == 1)

    # Fill values starting from (1, 1)
    # Number of ways of reaching cell[row][col] is
    # cell[row - 1][col] + cell[row][col - 1]
    for row in range(1, num_rows):
        for col in range(1, num_cols):
            if grid[row][col] == 0:
                grid[row][col] = grid[row - 1][col] + grid[row][col - 1]
            else:
                grid[row][col] = 0

    # Return value stored in bottom right corner
    return grid[num_rows - 1][num_cols - 1]
