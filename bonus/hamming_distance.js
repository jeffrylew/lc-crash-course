/**
 * @param {number} x
 * @param {number} y
 * @return {number}
 */
var hammingDistanceDS1 = function(x, y)
{
    let x_xor_y = x ^ y;
    let hamming_distance = 0;

    while (x_xor_y != 0)
    {
        if (x_xor_y % 2 == 1)
        {
            hamming_distance++;
        }

        x_xor_y = x_xor_y >> 1;
    }

    return hamming_distance;
};
