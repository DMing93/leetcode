/*
 * 题目：二叉搜索树中的两个节点被错误地交换。
 * 请在不改变其结构的情况下，恢复这棵树。
 *
 * 示例 1:
 *
 * 输入: [1,3,null,null,2]
 *
 *   1
 *  /
 * 3
 *  \
 *   2
 *
 * 输出: [3,1,null,null,2]
 *
 *   3
 *  /
 * 1
 *  \
 *   2
 *
 * 示例 2:
 *
 * 输入: [3,1,4,null,null,2]
 *
 *     3
 *    / \
 *   1   4
 *      /
 *     2
 *
 * 输出: [2,1,4,null,null,3]
 *
 *     2
 *    / \
 *   1   4
 *      /
 *     3
 *
 * 进阶:
 *
 *   使用 O(n) 空间复杂度的解法很容易实现。
 *   你能想出一个只使用常数空间的解决方案吗？
 */

/*
 * 思路：使用一个数组，把遍历的轨迹记录下来，找出没有按照递增规律出现的元素，
 * 交换两个元素中的值即可，这个想法空间复杂度为O(n)；
 *
 * 按照中序遍历，记录下第一个没有按照顺序递增的元素；
 * 按照右子树、根、左子树的顺序遍历，找到第一个没有按照递减顺序的元素；
 * 交换两个元素中的值，这个想法的空间复杂度为O(2)；
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#if 0
/*
 * first method:
 *     1. traverse the bst tree and record the order of each element.
 *     2. find the out-of-order elements.
 *     3. exchange the out-of-order elements's values.
 */
/* O(n) */
void traverse_tree(struct TreeNode *root, struct TreeNode *order[], int *begin)
{
    if (root == NULL) {
        return ;
    }

    traverse_tree(root->left, order, begin);
    order[*begin] = root;
    (*begin)++;
    traverse_tree(root->right, order, begin);
}

void recoverTree(struct TreeNode* root) {
    const int max = 1000;
    struct TreeNode *order[max];
    int num = 0;
    struct TreeNode *first = NULL, *second = NULL;
    int i = 0;

    if (root == NULL) {
        return ;
    }

    traverse_tree(root, order, &num);

    for (i = 0; i < num; i++) {
        if (order[i]->val > order[i+1]->val) {
            first = order[i];
            break;
        }
    }

    for (i = num - 1; i >= 0; i--) {
        if (order[i]->val < order[i-1]->val) {
            second = order[i];
            break;
        }
    }

    i = first->val;
    first->val = second->val;
    second->val = i;
}
#endif

/* O(2) */
void inorder_traverse_tree(struct TreeNode *root, struct TreeNode **last, struct TreeNode *order[])
{
    if (root == NULL) {
        return ;
    }

    inorder_traverse_tree(root->left, last, order);
    if (*last == NULL) {
        *last = root;
    } else {
        if (((*last)->val > root->val) && (order[0] == NULL)) {
            order[0] = *last;
        }
    }
    *last = root;
    inorder_traverse_tree(root->right, last, order);
}

void reverseorder_traverse_tree(struct TreeNode *root, struct TreeNode **last, struct TreeNode *order[])
{
    if (root == NULL) {
        return ;
    }
    
    reverseorder_traverse_tree(root->right, last, order);
    if (*last == NULL) {
        *last = root;
    } else {
        if ((*last)->val < (root->val) && (order[1] == NULL)) {
            order[1] = *last;
        }
    }
    *last = root;
    reverseorder_traverse_tree(root->left, last, order);
}

void recoverTree(struct TreeNode* root) {
    struct TreeNode *order[2] = {NULL};
    int index = 0;
    struct TreeNode *last = NULL;

    if (root == NULL) {
        return ;
    }

    inorder_traverse_tree(root, &last, order);
    last = NULL;
    reverseorder_traverse_tree(root, &last, order);

    index = order[0]->val;
    order[0]->val = order[1]->val;
    order[1]->val = index;
}
