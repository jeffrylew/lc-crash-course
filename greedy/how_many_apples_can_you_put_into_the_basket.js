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