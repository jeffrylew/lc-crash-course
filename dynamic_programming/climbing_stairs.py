def climbStairsDS1(n: int) -> int:
    def climb_Stairs(curr_step: int) -> int:
        if curr_step > n:
            return 0

        if curr_step == n:
            return 1

        return climb_Stairs(curr_step + 1) + climb_Stairs(curr_step + 2)

    return climb_Stairs(0)
