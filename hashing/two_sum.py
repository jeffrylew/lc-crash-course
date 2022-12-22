def twoSum(nums: List[int], target: int) -> List[int]:
    dic = {}
    for i in range(len(nums)):
        num = nums[i]
        complement = target - num
        if complement in dic: # This op is O(1)
            return [i, dic[complement]]
        
        dic[num] = i

    return [-1, -1]