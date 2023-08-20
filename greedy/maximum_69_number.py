def maximum69NumberDS1(num: int) -> int:
    # Convert the input num to a list of characters, num_char_list
    num_char_list = list(str(num))

    # Iterate over the list from high to low
    for i, curr_char in enumerate(num_char_list):
        # If we find the first 6, replace it with 9 and break the loop
        if curr_char == '6':
            num_char_list[i] = '9'
            break
    
    # Convert the modified char list to integer and return it
    return int("".join(num_char_list))


def maximum69NumberDS2(num: int) -> int:
    # Convert the input num to the string num_string
    num_string = str(num)

    # Use the built-in function to replace the first 6 with 9
    # Return the integer converted from the modified num_string
    return int(num_string.replace('6', '9', 1))


def maximum69NumberDS3(num: int) -> int:
    # Since we start with the lowest digit, initialize idx_curr_digit = 0
    idx_curr_digit = 0
    idx_first_six = -1
    num_copy = num

    # Check every digit of num_copy from low to high
    while num_copy:
        # If the current digit is 6, record it as the highest digit for 6
        if num_copy % 10 == 6:
            idx_first_six = idx_curr_digit
        
        # Move onto the next digit
        num_copy //= 10
        idx_curr_digit += 1
    
    # If don't find any digit of 6, return the original number
    # Else, increment num by the difference made by the first 6
    return num if idx_first_six == -1 else num + 3 * 10 ** idx_first_six
