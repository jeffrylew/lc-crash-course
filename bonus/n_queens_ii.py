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

        # Todo: Remaining cases

    return backtrack(0, 0, 0, 0)
