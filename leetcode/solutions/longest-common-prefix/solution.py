class Solution:
    def longestCommonPrefix(self, s: [str]) -> str:
        if len(s) == 0:
            return ""
        m = len(s[0])
        pos = 0

        for i in range(1, len(s)):
            if len(s[i]) < m:
                m = len(s[i])
        if m == 0:
            return ""

        #
        # Plain char by char compare all
        # entries (it must be transitive).
        while pos < m:
            for i in range(1, len(s)):
                if s[0][pos] != s[i][pos]:
                    if pos == 0:
                        return ""
                    else:
                        return s[0][0:pos]
            pos += 1
        return s[0][0:pos]
#
#data = [
#    ["flower","flow","flight"]
#]
#
#for i in range(0, len(data)):
#    print(Solution().longestCommonPrefix(data[i]))
