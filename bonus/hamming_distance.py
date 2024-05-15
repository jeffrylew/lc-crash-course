def hammingDistanceDS1(x: int, y: int) -> int:
    return bin(x ^ y).count('1')
