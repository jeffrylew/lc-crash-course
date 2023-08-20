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
