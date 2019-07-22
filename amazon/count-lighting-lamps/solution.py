def solve(a) -> int:
    print("Input", a)
    res = []
    r = 0
    for i in range(0, len(a)):
        # Just remember that once all
        # previous lamps are turned on
        # we have a sum of their numbers
        # to match [1,i] sequence.
        r += a[i]
        n = (i+1)
        v = n * (n+1) // 2
        if r == v:
            #
            # Put arrays just to illustrate the results.
            res.append(sorted(a[0:i+1]))
    return res

data = [
    [1,2,3,4,5],        #=> [1,2,3,4,5]
    [5,4,3,2,1],        #=> [1]
    [1,3,2,5,4],        #=> [3,5]
    [4,5,2,3,1],        #=> [1]
    [2,1,3],            #=> [2,3]
]

for i in range(0, len(data)):
    print("Output", solve(data[i]))
