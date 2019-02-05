//101. Symmetric Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSymmetric(struct TreeNode *root) {
    bool isMirror(struct TreeNode *t1, struct TreeNode *t2);

    return isMirror(root, root);
}

bool isMirror(struct TreeNode *t1, struct TreeNode *t2) {
    if (t1 == NULL && t2 == NULL)
        return true;
    if (t1 == NULL || t2 == NULL || (t1->val != t2->val))
        return false;
    return isMirror(t1->right, t2->left) && isMirror(t1->left, t2->right);
}
