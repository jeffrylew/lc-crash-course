from collections import defaultdict

def equalPairs(grid: List[List[int]]) -> int:
    def convert_to_key(arr: List[int]):
        return tuple(arr)
    
    row_dic = defaultdict(int)
    for row in grid:
        row_dic[convert_to_key(row)] += 1
    
    col_dic = defaultdict(int)
    for col in range(len(grid[0])):
        current_col = []
        for row in range(len(grid)):
            current_col.append(grid[row][col])
        
        col_dic[convert_to_key(current_col)] += 1
    
    ans = 0
    for arr in row_dic:
        ans += row_dic[arr] * col_dic[key]
    
    return ans
