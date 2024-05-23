def totalNQueens(n: int) -> int:
    def backtrack(
        row: int,
        diagonals: int,
        anti_diagonals: int,
        cols: int
    ) -> int:
        # Base case: N queens have been placed
        if row == n:
            return 1

        num_solutions = 0
        for col in range(n):
            # Bit masks. Add n to avoid negative bit shifting
            curr_diagonal = 1 << (row - col + n)
            curr_anti_diagonal = 1 << (row + col)
            curr_col = 1 << col

            # If the queen is not placeable. Check if bits are set
            if (
                (cols & curr_col) != 0
                or (diagonals & curr_diagonal) != 0
                or (anti_diagonals & curr_anti_diagonal) != 0
            ):
                continue

            # "Add" the queen to the board
            cols ^= curr_col
            diagonals ^= curr_diagonal
            anti_diagonals ^= curr_anti_diagonal

            # Move onto the next row with the updated board state
            num_solutions += backtrack(row + 1, diagonals, anti_diagonals, cols)

            # "Remove" the queen from the board since we have already
            # explored all valid paths using the above function call
            cols ^= curr_col
            diagonals ^= curr_diagonal
            anti_diagonals ^= curr_anti_diagonal

        return num_solutions

    return backtrack(0, 0, 0, 0)
