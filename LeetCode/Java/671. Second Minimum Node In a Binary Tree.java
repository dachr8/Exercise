class Solution {
    int rootval;

    public int findSecondMinimumValue(TreeNode root) {
        if (rootval == 0) {
            rootval = root.val;
            int ans = findSecondMinimumValue(root);
            return ans == Integer.MAX_VALUE ? -1 : ans;
        } else if (root != null)
            if (root.val > rootval)
                return root.val;
            else
                return Math.min(findSecondMinimumValue(root.left), findSecondMinimumValue(root.right));
        return Integer.MAX_VALUE;
    }
}