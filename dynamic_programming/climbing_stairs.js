/**
 * @param {number} n
 * @return {number}
 */
var climbStairsDS1 = function(n) {
    const climb_Stairs = curr_step => {
        if (curr_step > n)
        {
            return 0;
        }

        if (curr_step == n)
        {
            return 1;
        }

        return climb_Stairs(curr_step + 1) + climb_Stairs(curr_step + 2);
    }

    return climb_Stairs(0);
};
