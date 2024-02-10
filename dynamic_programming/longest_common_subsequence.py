from functools import cache


def longestCommonSubsequenceDS1(text1: str, text2: str) -> int:
    @cache
    def get_lcs(idx1: int, idx2: int) -> int:
        if idx1 == len(text1) or idx2 == len(text2):
            return 0

        if text1[idx1] == text2[idx2]:
            return 1 + get_lcs(idx1 + 1, idx2 + 1)

        return max(get_lcs(idx1 + 1, idx2), get_lcs(idx1, idx2 + 1))

    return get_lcs(0, 0)


def longestCommonSubsequenceDS2(text1: str, text2: str) -> int:
    text1_len = len(text1)
    text2_len = len(text2)
    lcs = [[0] * (text2_len + 1) for _ in range(text1_len + 1)]

    for idx1 in range(text1_len - 1, -1, -1):
        for idx2 in range(text2_len - 1, -1, -1):
            if text1[idx1] == text2[idx2]:
                lcs[idx1][idx2] = 1 + lcs[idx1 + 1][idx2 + 1]
            else:
                lcs[idx1][idx2] = max(lcs[idx1 + 1][idx2], lcs[idx1][idx2 + 1])

    return lcs[0][0]
