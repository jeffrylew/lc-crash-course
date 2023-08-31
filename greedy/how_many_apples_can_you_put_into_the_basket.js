/**
 * @param {number[]} weight
 * @return {number}
 */
var maxNumberOfApplesDS1 = function(weight)
{
    weight.sort((a, b) => a - b);

    let apples = 0;
    let units = 0;

    for (let i = 0; i < weight.length && units + weight[i] <= 5000; i++)
    {
        apples++;
        units += weight[i];
    }

    return apples;
};

// JavaScript does not have any built-in support for a heap so skip DS2 solution

/**
 * @param {number[]} weight
 * @return {number}
 */
var maxNumberOfApplesDS3 = function(weight)
{
    // Initialize the bucket to store all elements
    let size = -1;
    for (const ele of weight)
    {
        size = Math.max(size, ele);
    }

    let bucket = Array(size + 1).fill(0);
    for (const ele of weight)
    {
        bucket[ele]++;
    }

    let apples = 0;
    let units = 0;

    for (let i = 0; i < size + 1; i++)
    {
        // If we have apples of i units of weight
        if (bucket[i] != 0)
        {
            // We need to make sure that:
            // 1. We do not take more apples than those provided
            // 2. We do not exceed 5000 units of weight
            const take = Math.min(bucket[i], Math.trunc((5000 - units) / i));

            if (take == 0)
            {
                break;
            }

            units += take * i;
            apples += take;
        }
    }

    return apples;
};