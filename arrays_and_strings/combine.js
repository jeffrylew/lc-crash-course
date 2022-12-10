/**
 * @param {number[]} arr1
 * @param {number[]} arr2
 * @returns {number[]}
 */

/**
 * Alternatively, can use ES6 arrow function,
 * let combine = (arr1, arr2) => { ... }
 */
var combine = function(arr1, arr2) {
    let ans = [];
    let i = 0, j = 0;

    while (i < arr1.length && j < arr2.length)
    {
        if (arr1[i] < arr2[j])
        {
            ans.push(arr1[i]);
            i++;
        }
        else
        {
            ans.push(arr2[j]);
            j++;
        }
    }

    while (i < arr1.length)
    {
        ans.push(arr1[i]);
        i++;
    }

    while (j < arr2.length)
    {
        ans.push(arr2[j]);
        j++;
    }

    return ans;
}