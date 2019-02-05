class Solution {
    public int[][] floodFill(int[][] image, int sr, int sc, int newColor) {
        if (image[sr][sc] != newColor)
            dfs(image, sr, sc, newColor);
        return image;
    }

    public void dfs(int[][] image, int r, int c, int newColor) {
        int color = image[r][c];
        image[r][c] = newColor;
        if (r > 0 && image[r - 1][c] == color)
            dfs(image, r - 1, c, newColor);
        if (c > 0 && image[r][c - 1] == color)
            dfs(image, r, c - 1, newColor);
        if (r + 1 < image.length && image[r + 1][c] == color)
            dfs(image, r + 1, c, newColor);
        if (c + 1 < image[0].length && image[r][c + 1] == color)
            dfs(image, r, c + 1, newColor);
    }
}