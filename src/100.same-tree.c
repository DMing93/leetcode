/*
 * 题目：给定两个二叉树，编写一个函数来检验它们是否相同。
 * 如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。
 *
 * 示例 1:
 *
 * 输入:       1         1
 *            / \       / \
 *           2   3     2   3
 *
 *          [1,2,3],   [1,2,3]
 *
 * 输出: true
 *
 * 示例 2:
 *
 * 输入:      1          1
 *           /           \
 *          2             2
 *
 *         [1,2],     [1,null,2]
 *
 * 输出: false
 *
 * 示例 3:
 *
 * 输入:       1         1
 *            / \       / \
 *           2   1     1   2
 *
 *          [1,2,1],   [1,1,2]
 *
 * 输出: false
 */

/*
 * 思路：判断两棵树是否相同，只需要按照相同的顺序（前序、中序、后序）遍历，
 * 并在遍历的过程中判断对应节点的值是否相同即可。
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void traverse_two_trees(struct TreeNode *p, struct TreeNode *q, int *res)
{
    if ((p == NULL && q != NULL) || (p != NULL && q == NULL) || (*res) == 1) {
        *res = 1;
        return ;
    }
    
    if (p == NULL && q == NULL) {
        return ;
    }
    
    traverse_two_trees(p->left, q->left, res);
    if (p->val != q->val) {
        *res = 1;
        return;
    }
    traverse_two_trees(p->right, q->right, res);
}

bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    int res = 0;
    traverse_two_trees(p, q, &res);
    
    if (res) {
        return false;
    } else {
        return true;
    }
}
