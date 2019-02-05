//530. Minimum Absolute Difference in BST
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int min = 2147483647, prev = 0;

int getMinimumDifference(struct TreeNode *root) {

    if (root == NULL)
        return min;

    getMinimumDifference(root->left);

    if (prev)
        min = min < (root->val - prev) ? min : (root->val - prev);

    prev = root->val;

    getMinimumDifference(root->right);

    return min;
}
