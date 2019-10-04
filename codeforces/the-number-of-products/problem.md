[F. The Number of Products](https://codeforces.com/gym/102348/problem/F?locale=en)
===========================

```
time limit per test: 2.0 s
memory limit per test: 256 MB
input: standard input
output: standard output
```

You are given a sequence `a1, a2, ... ,an` consisting of `n` integers.

You have to calculate three following values:

- the number of pairs of indices (l,r) (l<=r) such that al⋅al+1…ar−1⋅aral⋅al+1…ar−1⋅ar is negative;
- the number of pairs of indices (l,r)(l,r) (l≤r)(l≤r) such that al⋅al+1…ar−1⋅aral⋅al+1…ar−1⋅ar is zero;
- the number of pairs of indices (l,r)(l,r) (l≤r)(l≤r) such that al⋅al+1…ar−1⋅aral⋅al+1…ar−1⋅ar is positive;

Input
The first line contains one integer nn (1≤n≤2⋅105)(1≤n≤2⋅105) — the number of elements in the sequence.

The second line contains nn integers a1,a2,…,ana1,a2,…,an (−109≤ai≤109)(−109≤ai≤109) — the elements of the sequence.

Output
Print three integers — the number of subsegments with negative product, the number of subsegments with product equal to zero and the number of subsegments with positive product, respectively.

Examples
inputCopy
5
5 -3 3 -1 0
outputCopy
6 5 4
inputCopy
10
4 0 -4 3 1 2 -4 3 0 3
outputCopy
12 32 11
inputCopy
5
-1 -2 -3 -4 -5
outputCopy
9 0 6
Note
In the first example there are six subsegments having negative products:
(1,2)(1,2), (1,3)(1,3), (2,2)(2,2), (2,3)(2,3), (3,4)(3,4), (4,4)(4,4),
five subsegments having products equal to zero: (1,5)(1,5), (2,5)(2,5), (3,5)(3,5), (4,5)(4,5), (5,5)(5,5), and four subsegments having positive products: (1,1)(1,1), (1,4)(1,4), (2,4)(2,4), (3,3)(3,3).


