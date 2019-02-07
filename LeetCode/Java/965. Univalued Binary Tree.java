/**
 * Definition for a binary tree node.
 * public class TreeNode {
 * int val;
 * TreeNode left;
 * TreeNode right;
 * TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    public boolean isUnivalTree(TreeNode root) {
        return (root.left == null || (root.val == root.left.val && isUnivalTree(root.left))) && (root.right == null || (root.val == root.right.val && isUnivalTree(root.right)));
    }
}