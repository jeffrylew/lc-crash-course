def answerQueriesDS1(nums: list[int], queries: list[int]) -> list[int]:
    # Sort nums
    nums.sort()
    ans = []

    # For each query, collect numbers from lowest to highest
    # If their sum exceeds the limit query, move on to the next query
    for query in queries:
        count = 0
        for num in nums:
            if query >= num:
                query -= num
                count += 1
            else:
                break
        ans.append(count)
    
    return ans