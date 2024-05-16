public int hammingDistanceDS1(int x, int y)
{
    // https://leetcode.com/problems/hamming-distance/editorial/
    //
    // Time complexity O(1). The XOR operation takes constant time. The built-in
    // bitCount function takes O(k) where k = number of bits for an integer in
    // the worst case. However, the Integer type is of fixed size in Java so
    // the time complexity is constant.
    // Space complexity O(1). A temporary memory of constant size holds the
    // result of the XOR operation.

    return Integer.bitCount(x ^ y);
}

public int hammingDistanceDS2(int x, int y)
{
    int x_xor_y = x ^ y;
    int hamming_distance = 0;

    while (x_xor_y != 0)
    {
        if (x_xor_y % 2 == 1)
        {
            hamming_distance++;
        }

        x_xor_y = x_xor_y >> 1;
    }

    return hamming_distance;
}

public int hammingDistanceDS3(int x, int y)
{
    int x_xor_y = x ^ y;
    int hamming_distance = 0;

    while (x_xor_y != 0)
    {
        hamming_distance++;

        // Remove the rightmost bit of '1'
        x_xor_y = x_xor_y & (x_xor_y - 1);
    }

    return hamming_distance;
}
