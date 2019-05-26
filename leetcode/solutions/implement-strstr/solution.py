class Solution:
    def strStr(self, a: str, b: str) -> int:
        if len(a) == 0:
            if len(b) == 0: return 0
            else: return -1
        elif len(b) == 0: return 0
        elif len(b) > len(a): return -1
        #
        # May use KMP, but "easy" tag implies plain search :)
        for i in range(0, len(a)):
            for j in range(0, len(b)):
                if i + j >= len(a): return -1
                if a[i + j] != b[j]:
                    break
            else:
                return i
        return -1
