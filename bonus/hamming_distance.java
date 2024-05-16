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
