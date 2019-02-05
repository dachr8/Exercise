class Solution {
    public int numMagicSquaresInside(int[][] grid) {
        int R = grid.length, C = grid[0].length;
        int ans = 0;
        for (int r = 1; r < R - 1; r++)
            for (int c = 1; c < C - 1; c++)
                if (grid[r][c] == 5)
                    if (magic(grid[r - 1][c - 1], grid[r - 1][c], grid[r - 1][c + 1],
                            grid[r][c - 1], grid[r][c], grid[r][c + 1],
                            grid[r + 1][c - 1], grid[r + 1][c], grid[r + 1][c + 1]))
                        ans++;

        return ans;
    }

    public boolean magic(int... vals) {
        Set<Integer> count = new HashSet<>();
        for (int v : vals)
            if (v > 9 || count.contains(v))
                return false;
            else
                count.add(v);
        return (vals[0] + vals[1] + vals[2] == 15 &&
                vals[3] + vals[5] == 10 &&
                vals[6] + vals[7] + vals[8] == 15 &&
                vals[0] + vals[3] + vals[6] == 15 &&
                vals[1] + vals[7] == 10 &&
                vals[2] + vals[5] + vals[8] == 15 &&
                vals[0] + vals[8] == 10 &&
                vals[2] + vals[6] == 10);
    }
}