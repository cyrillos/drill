class Solution:
    def isNumber(self, s: str) -> bool:
        lo, hi = 0, len(s)

        for i in range(lo, hi):
            if s[i] != ' ':
                lo = i
                break
        else: return False

        for i in range(hi-1, -1, -1):
            if s[i] != ' ':
                hi = i+1
                break
        else: return False

        if lo >= hi: return False

        def is_digit(c):
            v = ord(c)
            return (v >= ord('0') and v <= ord('9'))

        # [+|-]([n])(.[n])[(e[+|-]n]

        has_dot = False
        if s[lo] == '-' or s[lo] == '+':
            lo += 1
        if s[lo] == '.':
            has_dot = True
            lo += 1
        if lo >= hi: return False

        has_digits = False
        for i in range(lo, hi):
            if is_digit(s[i]):
                if not has_digits:
                    has_digits = True
                continue
            elif s[i] == '.':
                if has_dot: return False
                has_dot = True
                continue
            elif s[i] == 'e' or s[i] == 'E':
                if not has_digits: return False
                if i == hi-1:
                    return False
                lo = i+1
                if s[lo] == '-' or s[lo] == '+':
                    lo += 1
                    if lo >= hi: return False
                for j in range(lo, hi):
                    if not is_digit(s[j]):
                        return False
                else:
                    return True
                break
            return False
        else:
            return True

        return False

data = [
    "2e0",      # True
    ".2e-0",    # True
    "-.2e+12",  # True
    ".",        # False
    "  1 ",     # True
    "3.",       # True
    ".1",       # True
    "0",        # True
    "e9"        # False
]

for i in range(0, len(data)):
    print(data[i], Solution().isNumber(data[i]))
