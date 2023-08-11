def kClosestDS1(points: list[list[int]], k: int) -> list[list[int]]:
    points.sort(key = lambda P: P[0]**2 + P[1]**2)
    return points[:k]