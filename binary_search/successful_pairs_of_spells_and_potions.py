def successfulPairs(
    spells: list[int], potions: list[int], success: int
) -> list[int]:
    def binary_search(arr: list[int], target: float) -> int:
        left = 0
        right = len(arr) - 1

        while left <= right:
            mid = (left + right) // 2

            if arr[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
        
        return left
    
    potions.sort()
    ans = []
    npotions = len(potions) # = m

    for spell in spells:
        insert_idx = binary_search(potions, success / spell)
        ans.append(npotions - insert_idx)
    
    return ans
