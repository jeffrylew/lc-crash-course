public int maximum69NumberDS1(int num)
{
    // Convert the input num to a string builder numSB
    StringBuilder numSB = new StringBuilder();
    numSB.append(num);

    // Iterate over the string builder from high to low
    for (int i = 0; i < numSB.length(); ++i)
    {
        // If we find the first 6, replace it with 9 and break the loop
        if (numSB.charAt(i) == '6')
        {
            numSB.setCharAt(i, '9');
            break;
        }
    }

    // Convert the modified string builder to integer and return it
    return Integer.parseInt(numSB.toString());
}

public int maximum69NumberDS2(int num)
{
    // Convert the input num to the string numString
    String numString = "" + num;

    // Use the built-in function to replace the first 6 with 9
    // Return the integer converted from the modified numString
    return Integer.parseInt(numString.replaceFirst("6", "9")); 
}

public int maximum69NumberDS3(int num)
{
    // Since start with lowest digit, initialize currDigit = 0
    int numCopy = num;
    int idxSix = -1;
    int currDigit = 0;

    // Check every digit of numCopy from low to high
    while (numCopy > 0)
    {
        // If the current digit is 6, record it as the highest digit for 6
        if (numCopy % 10 == 6)
        {
            idxSix = currDigit;
        }

        // Move onto next digit
        numCopy /= 10;
        currDigit++;
    }

    // If don't find any digit of 6, return original number
    // Else, increment num by the difference made by the first 6
    return idxSix == -1 ? num : num + 3 * (int)Math.pow(10, idxSix);
}