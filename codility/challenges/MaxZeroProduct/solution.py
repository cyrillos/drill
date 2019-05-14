def solution(a):
    def factor(v):
        r = [v, 0, 0]
        while v and v % 5 == 0:
            v /= 5
            r[1] += 1
        while v and v % 2 == 0:
            v /= 2
            r[2] += 1
        return r

    def get_zeros(a):
        f = 0
        t = 0
        for i in a:
            f += i[1]
            t += i[2]
        return min(f,t)

    if len(a) < 3:
        return 0
    elif len(a) == 3:
        return get_zeros([factor(a[0]), factor(a[1]), factor(a[2])])

    d = { }

    for i in a:
        v = factor(i)
        r = v[1] - v[2]
        if r in d:
            d[r].append(v)
        else:
            d[r] = [v]

    for i in d.keys():
        if i < 0:
            d[i].sort(reverse=True, key=lambda x: (x[2],x[1]))
        elif i >= 0:
            d[i].sort(reverse=True, key=lambda x: (x[1],x[2]))

    n = []
    for i in d.keys():
        n += d[i][:3]

    max_zeros = 0

    for i in range(0, len(n) - 2):
        for j in range(i+1, len(n) - 1):
            for k in range(j+1, len(n)):
                c = get_zeros([n[i], n[j], n[k]])
                if c > max_zeros:
                    max_zeros = c

    return max_zeros
