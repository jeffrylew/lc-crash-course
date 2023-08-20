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

/**
 * @param {number} num
 * @return {number}
 */
var maximum69NumberDS2 = function(num)
{
    // Since we start with the lowest digit, initialize currDigit = 0
    let numCopy = num;
    let idxFirstSix = -1;
    let idxCurrDigit = 0;

    // Check every digit of numCopy from low to high
    while (numCopy > 0)
    {
        // If the current digit is 6, record it as the highest digit of 6
        if (numCopy % 10 == 6)
        {
            idxFirstSix = idxCurrDigit;
        }

        // Move onto next digit
        numCopy = Math.floor(numCopy / 10);
        idxCurrDigit++;
    }

    // If don't find any digit of 6, return original number
    // Else, increment num by the difference made by the first 6
    return idxFirstSix == -1 ? num : num + 3 * (10 ** idxFirstSix);
};
