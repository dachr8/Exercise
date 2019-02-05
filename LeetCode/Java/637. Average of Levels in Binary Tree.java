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
    List<Integer> count;
    List<Double> res;

    public List<Double> averageOfLevels(TreeNode root) {
        count = new ArrayList<>();
        res = new ArrayList<>();
        average(root, 0);
        for (int i = 0; i < res.size(); i++)
            res.set(i, res.get(i) / count.get(i));
        return res;
    }

    public void average(TreeNode t, int i) {
        if (t == null)
            return;
        if (i < res.size()) {
            res.set(i, res.get(i) + t.val);
            count.set(i, count.get(i) + 1);
        } else {
            res.add(1.0 * t.val);
            count.add(1);
        }
        average(t.left, i + 1);
        average(t.right, i + 1);
    }
}