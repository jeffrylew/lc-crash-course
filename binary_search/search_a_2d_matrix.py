def searchMatrix(matrix: list[list[int]], target: int) -> bool:
    nrows, ncols = len(matrix), len(matrix[0]) # m, n
    left, right = 0, nrows * ncols - 1

    while left <= right:
        mid = (left + right) // 2
        row = mid // ncols
        col = mid % ncols
        num = matrix[row][col]

        if num == target:
            return True
        
        if num < target:
            left = mid + 1
        else:
            right = mid - 1
    
    return False