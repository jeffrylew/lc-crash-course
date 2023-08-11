import random


def kClosestDS1(points: list[list[int]], k: int) -> list[list[int]]:
    points.sort(key = lambda P: P[0]**2 + P[1]**2)
    return points[:k]


class Solution(object):
    def kClosestDS2(points: list[list[int]], k: int) -> list[list[int]]:
        dist = lambda i: points[i][0]**2 + points[i][1]**2

        def sort(i, j, k):
            # Partially sorts A[i:j + 1] so the first k elements
            # are the smallest k elements
            if i >= j:
                return
            
            # Put random element as A[i] - this is the pivot
            idx = random.randint(i, j)
            points[i], points[idx] = points[idx], points[i]

            mid = partition(i, j)
            if k < mid - i + 1:
                sort(i, mid - 1, k)
            elif k > mid - i + 1:
                sort(mid + 1, j, k - (mid - i + 1))
        
        def partition(i, j):
            # Partition by pivot A[i], returning an index mid
            # such that A[i] <= A[mid] <= A[j] for i < mid < j
            oi = i
            pivot = dist(i)
            i += 1

            while True:
                while i < j and dist(i) < pivot:
                    i += 1
                
                while i <= j and dist(j) >= pivot:
                    j -= 1
                
                if i >= j:
                    break

                points[i], points[j] = points[j], points[i]

            points[oi], points[j] = points[j], points[oi]
            return j
        
        sort(0, len(points) - 1, k)
        return points[:k]