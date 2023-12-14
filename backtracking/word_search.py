def exist(board: list[list[str]], word: str) -> bool:
    # Space complexity is O(L) where L = len(word) for seen set
    # and recursion call stack

    def valid(row: int, col: int) -> bool:
        return 0 <= row < nrows and 0 <= col < ncols

    def backtrack(row: int, col: int, i: int, seen: list[list[bool]]) -> bool:
        if i == len(word):
            return True

        for dcol, drow in directions:
            next_row, next_col = row + drow, col + dcol

            if valid(next_row, next_col) and (next_row, next_col) not in seen:
                if board[next_row][next_col] == word[i]:
                    seen.add((next_row, next_col))

                    if backtrack(next_row, next_col, i + 1, seen):
                        return True

                    seen.remove((next_row, next_col))

        return False

    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    nrows = len(board)
    ncols = len(board[0])

    for row in range(nrows):
        for col in range(ncols):
            if (
                board[row][col] == word[0]
                and backtrack(row, col, 1, {(row, col)})
            ):
                return True

    return False
