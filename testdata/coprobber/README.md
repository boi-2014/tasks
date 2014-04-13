Test input file format:

 * First line: N

        4

 * Next N lines: adjacency matrix A.
   Each line contains N numbers, where each one is `0` or `1`.
   The matrix must be symmetric and the main diagonal values must all be zeroes.

        0 1 1
        1 0 1
        1 1 0

 * Next line: CopCanWin.
   Must be `0` or `1`.

        1

 * If CopCanWin = 1, another N lines follow which define the robber's strategy.
   Each line contains N+1 integers between 0 and N-1.
   
   The value at row _c_ and column _r_, where _r_ < N, corresponds to a situation where it's robber's turn, the cop is at corner _c_ and the robber is at corner _r_, and represents the corner, which the robber has to move to.
   
   The right-most column defines robber's starting corners for each possible cop's starting corner.

        0 2 1 2
        2 0 0 2
        1 0 0 1


## Examples

### Triangle

```
3
0 1 1
1 0 1
1 1 0

1
0 2 1 2
2 0 0 2
1 0 0 1
```

### Square

```
4
0 1 0 1
1 0 1 0
0 1 0 1
1 0 1 0

1
0 2 1 2 2
3 0 3 0 3
1 0 0 0 0
1 0 1 0 1
```
