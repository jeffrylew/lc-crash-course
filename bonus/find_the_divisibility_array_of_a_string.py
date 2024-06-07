def divisibilityArray(word: str, m: int) -> list[int]:
    div = []
    curr = 0

    for digit in word:
        curr = (curr * 10 + int(digit)) % m

        if curr == 0:
            div.append(1)
        else:
            div.append(0)

    return div
