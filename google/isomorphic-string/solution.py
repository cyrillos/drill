def is_isomorphic(s: str, t: str) -> bool:
    ds = {}
    dt = {}
    for i in range(0, len(s)):
        if s[i] not in ds:
            ds[s[i]] = t[i]
        if t[i] not in dt:
            dt[t[i]] = s[i]
        if ds[s[i]] != t[i] or dt[t[i]] != s[i]:
            return False
    return True

data = [
    ["abca", "dced"],
    ["ab", "ba"],
    ["abcdefghijklmnopqrstuvwxyz", "bcdefghijklmnopqrstuvwxyza"],
    ["egg", "add"],
    ["foo", "bar"],
    ["paper", "title"],
]

for a in data:
    print(a[0],a[1], is_isomorphic(a[0],a[1]))
