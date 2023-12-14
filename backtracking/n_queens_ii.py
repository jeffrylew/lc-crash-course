def totalNQueens(n: int) -> int:
    def backtrack(
        row: int, diagonals: set[int], anti_diagonals: set[int], cols: set[int]
    ) -> int:
        # Base case - N queens have been placed
        if row == n:
            return 1

        solutions = 0
        for col in range(n):
            curr_diagonal = row - col
            curr_anti_diagonal = row + col

            # If the queen is not placeable
            if (col in cols
                or curr_diagonal in diagonals
                or curr_anti_diagonal in anti_diagonals):
                continue

            # "Add" the queen to the board
            cols.add(col)
            diagonals.add(curr_diagonal)
            anti_diagonals.add(curr_anti_diagonal)

            # Move onto the next row with the updated board state
            solutions += backtrack(row + 1, diagonals, anti_diagonals, cols)

            # "Remove" the queen from the board since we have already
            # explored all valid paths using the above function call
            cols.remove(col)
            diagonals.remove(curr_diagonal)
            anti_diagonals.remove(curr_anti_diagonal)

        return solutions

    return backtrack(0, set(), set(), set())
