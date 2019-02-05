//695. Max Area of Island
int maxAreaOfIsland(int **grid, int gridRowSize, int gridColSize) {

    int area(int r, int c, int **grid, int gridRowSize, int gridColSize, _Bool seen[gridRowSize][gridColSize]);

    int ans = 0, tmp;
    _Bool seen[gridRowSize][gridColSize];

    for (int r = 0; r < gridRowSize; r++)
        for (int c = 0; c < gridColSize; c++)
            seen[r][c] = 0;

    for (int r = 0; r < gridRowSize; r++)
        for (int c = 0; c < gridColSize; c++) {
            tmp = area(r, c, grid, gridRowSize, gridColSize, seen);
            ans = ans > tmp ? ans : tmp;
        }

    return ans;
}

int area(int r, int c, int **grid, int gridRowSize, int gridColSize, _Bool seen[gridRowSize][gridColSize]) {
    if (r < 0 || r >= gridRowSize || c < 0 || c >= gridColSize || !grid[r][c] || seen[r][c])
        return 0;
    seen[r][c] = 1;
    return 1 + area(r + 1, c, grid, gridRowSize, gridColSize, seen) +
           area(r - 1, c, grid, gridRowSize, gridColSize, seen) +
           area(r, c - 1, grid, gridRowSize, gridColSize, seen) +
           area(r, c + 1, grid, gridRowSize, gridColSize, seen);
}
