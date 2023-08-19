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

