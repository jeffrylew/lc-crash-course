def hammingDistanceDS1(x: int, y: int) -> int:
    return bin(x ^ y).count('1')


def hammingDistanceDS2(x: int, y: int) -> int:
    x_xor_y = x ^ y
    hamming_distance = 0

    while x_xor_y:
        # Mask out all bits except the rightmost
        if x_xor_y & 1:
            hamming_distance += 1

        x_xor_y = x_xor_y >> 1

    return hamming_distance


def hammingDistanceDS3(x: int, y: int) -> int:
    x_xor_y = x ^ y
    hamming_distance = 0

    while x_xor_y:
        hamming_distance += 1

        # Remove the rightmost bit of '1'
        x_xor_y = x_xor_y & (x_xor_y - 1)

    return hamming_distance
