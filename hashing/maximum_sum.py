from collections import defaultdict

def get_digit_sum(num: int):
    digit_sum = 0
    while num:
        digit_sum += num % 10
        num //= 10
    
    return digit_sum

def maximumSum1(nums: List[int]) -> int:
    dic = defaultdict(list)
    for num in nums:
        digit_sum = get_digit_sum(num)
        dic[digit_sum].append(num)
    
    ans = -1
    for key in dic:
        curr = dic[key]
        if len(curr) > 1:
            curr.sort(reverse=True)
            ans = max(ans, curr[0] + curr[1])
    
    return ans

def maximumSum2(nums: List[int]) -> int:
    dic = defaultdict(int)
    ans = -1

    for num in nums:
        digit_sum = get_digit_sum(num)
        if digit_sum in dic:
            ans = max(ans, num + dic[digit_sum])
        
        dic[digit_sum] = max(dic[digit_sum], num)
    
    return ans
