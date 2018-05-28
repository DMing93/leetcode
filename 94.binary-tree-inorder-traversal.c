/*
 * 题目：给定一个二叉树，返回它的中序遍历。
 *
 * 示例:
 * 输入: [1,null,2,3]
 *  1
 *   \
 *    2
 *   /
 *  3
 *
 * 输出: [1,3,2]
 *
 * 进阶: 递归算法很简单，你可以通过迭代算法完成吗？
 *
 */

/*
 * 思路：二叉树的中序遍历可以采用递归和非递归两种算法。本题中的难点在于题目要求
 * 返回中序遍历的数组，以及树中的元素个数，需要每次在添加元素时动态的调整内存空间的大小；
 * 非递归算法需要借助于栈来实现；
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#if 0
/* 递归解法 */
static void internal_traversal(struct TreeNode* root, int* returnSize, int **array)
{
    if (root == NULL) {
        return ;
    } else {
        internal_traversal(root->left, returnSize, array);
        (*returnSize)++;
        *array = realloc(*array, (*returnSize)*sizeof(int));
        (*array)[*returnSize - 1] = root->val;
        internal_traversal(root->right, returnSize, array);
    }
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int *array = NULL;
    *returnSize = 0;
    
    internal_traversal(root, returnSize, &array);
    
    return array;
}
#endif 

/* 非递归解法 */
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    const int max = 100;
    struct TreeNode* stack[max];
    int stack_index = -1; /* point to the bottom */
    int *array = NULL;
    
    if (root == NULL) {
        return NULL;
    }
    
    while (root || stack_index != -1) {
        if (root) {
            stack_index++;
            stack[stack_index] = root;
            root = root->left;
        } else {
            root = stack[stack_index];
            stack_index--;
            (*returnSize)++;
            array = realloc(array, sizeof(int) * (*returnSize));
            array[(*returnSize) - 1] = root->val;
            root = root->right;
        }
    }
    
    return array;
}
