/*
 * 给定一个二叉树，判断其是否是一个有效的二叉搜索树。
 * 一个二叉搜索树具有如下特征：
 *   节点的左子树只包含小于当前节点的数。
 *   节点的右子树只包含大于当前节点的数。
 *   所有左子树和右子树自身必须也是二叉搜索树。
 *
 * 示例 1:
 *
 * 输入:
 *   2
 *  / \
 * 1   3
 * 输出: true
 *
 * 示例 2:
 *
 * 输入:
 *   5
 *  / \
 * 1   4
 *    / \
 *   3   6
 * 输出: false
 * 解释: 输入为: [5,1,4,null,null,3,6]。
 * 根节点的值为 5 ，但是其右子节点值为 4 。
 */

/*
 * 思路：因为二叉搜索树按照中序遍历得到的结果是递增的，可以根据这个特性来进行判断。
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isValidBST(struct TreeNode* root) {
    int last = 0;
    int init_flag = 1;
    const int max = 1000;
    int stack[max];
    int index = -1; /* point to the stack's bottom */
    
    if (root == NULL) {
        return true;
    }
    
    while (root || index != -1) {
        if (root) {
            index++;
            stack[index] = root;
            root = root->left;
        } else {
            root = stack[index];
            index--;
            if (init_flag) {
                last = root->val;
                init_flag = 0;
            } else if (last >= root->val) {
                return false;
            }
            last = root->val;
            root = root->right;
        }
    }
    
    return true;
}
