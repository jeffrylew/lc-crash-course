/**
 * @param {number[]} spells
 * @param {number[]} potions
 * @param {number} success
 * @returns {number[]}
 */
var successfulPairs = function(spells, potions, success) {
    const binarySearch = (arr, target) => {
        let left = 0;
        let right = arr.length - 1;

        while (left <= right)
        {
            const mid = Math.floor((left + right) / 2);

            if (arr[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return left;
    }

    potions.sort((a, b) => a - b);
    let ans = [];
    const npotions = potions.length; // = m

    for (const spell of spells)
    {
        const insert_idx = binarySearch(potions, success / spell);
        ans.push(npotions - insert_idx);
    }

    return ans;
};