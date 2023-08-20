/**
 * @param {number} num
 * @return {number}
 */
var maximum69NumberDS1 = function(num)
{
    // Convert the input num to a string numString
    let numString = num.toString();

    // Iterate over the string (from high to low)
    for (let i = 0; i < numString.length; i++)
    {
        // If we find the first 6, replace it with 9 and break the loop
        if (numString.charAt(i) == '6')
        {
            return parseInt(
                numString.slice(0, i) + "9" + numString.slice(i + 1));
        }
    }

    return num;
};
