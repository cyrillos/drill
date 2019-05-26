class Solution:
    def strStr(self, a: str, b: str) -> int:
        if len(a) == 0:
            if len(b) == 0: return 0
            else: return -1
        elif len(b) == 0: return 0
        elif len(b) > len(a): return -1
        #
        # Should use KMP, but as tag implies it needs
        # to be easy.
        for i in range(0, len(a)):
            for j in range(0, len(b)):
                if i + j >= len(a): return -1
                if a[i + j] != b[j]:
                    break
            else:
                return i
        return -1

#data = [
#    ["aabaaabaaac", "aabaaac"],
#    ["mississippi", "pi"],
#    ["mississippi", "issip"]
#]
#
#for i in range(0, len(data)):
#    print(Solution().strStr(data[i][0], data[i][1]))
