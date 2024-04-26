def find_brightest_position(lights: list[list[int]]) -> int:
    brightness_changes = []
    for position, radius in lights:
        brightness_changes.append([position - radius, 1])
        brightness_changes.append([position + radius + 1, -1])

    brightness_changes.sort()

    brightest_pos = 0
    curr_brightness = 0
    max_brightness = 0

    for position, brightness in brightness_changes:
        curr_brightness += brightness
        if curr_brightness > max_brightness:
            max_brightness = curr_brightness
            brightest_pos = position

    return brightest_pos
