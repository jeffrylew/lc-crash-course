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
