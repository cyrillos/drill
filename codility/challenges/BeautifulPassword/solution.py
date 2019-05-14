alphabet_remap = { }
alphabet_last_pos = 0

def char_opcode(c):
    global alphabet_last_pos
    if c in alphabet_remap:
        return alphabet_remap[c]
    alphabet_remap[c] = 1 << alphabet_last_pos
    alphabet_last_pos += 1
    return char_opcode(c)

def solution_weigths(s):
    points = [[0, 0]]
    fx = 0

    for i in range(0, len(s)):
        fx ^= char_opcode(s[i])
        points.append([i + 1, fx])

    points.sort(key=lambda x: x[1])

    max_len = 0
    i = 0
    while i < len(points):
        j = i
        while j < len(points) - 1:
            if points[i][1] != points[j + 1][1]:
                break
            else:
                j += 1
        a = points[i][0]
        b = points[j][0]
        if a < b and (b - a) > max_len:
            max_len = b - a
        i = j + 1
    return max_len

def solution(S):
    return solution_weigths(S)
