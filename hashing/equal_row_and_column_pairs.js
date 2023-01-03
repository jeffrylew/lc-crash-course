/**
 * @param {number[][]} grid
 * @returns {number}
 */
var equalPairs = function(grid) {
    let convertToKey = arr => {
        let key = "";
        for (const num of arr)
        {
            key += num + ",";
        }

        return key;
    }

    let row_dic = new Map();
    for (const row of grid)
    {
        let key = convertToKey(row);
        row_dic.set(key, (row_dic.get(key) || 0) + 1);
    }

    let col_dic = new Map();
    for (let col = 0; col < grid[0].length; col++)
    {
        let currentCol = [];
        for (let row = 0; row < grid.length; row++)
        {
            currentCol.push(grid[row][col]);
        }

        let key = convertToKey(currentCol);
        col_dic.set(key, (col_dic.get(key) || 0) + 1);
    }

    let ans = 0;
    for (const [key, val] of row_dic)
    {
        ans += val * col_dic.get(key) || 0;
    }

    return ans;
}