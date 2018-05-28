/*
 * 题目：给定一个二叉树，检查它是否是镜像对称的。
 *
 * 例如，二叉树 [1,2,2,3,4,4,3] 是对称的。
 *
 *            1
 *           / \
 *          2   2
 *         / \ / \
 *        3  4 4  3
 *
 * 但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:
 *
 *            1
 *           / \
 *          2   2
 *           \   \
 *           3    3
 *
 * 说明:
 *
 * 如果你可以运用递归和迭代两种方法解决这个问题，会很加分。
 *
 */

/*
 * 思路：对根的左子树按照中序遍历，对右子树按照与中序相反的顺序进行遍历，
 * 并判断对应的节点上的元素是否相等。
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
 * first method: recursively
 *    1. L = root->left: traverse by the order: L, L->left, L->right
 *    2. R = root->right: traverse by the order: R, R->right, R->left
 *    3. L->val equal R->val ?
 */
void traverse_to_judge(struct TreeNode *l, struct TreeNode *r, int *sym)
{
    if (*sym == 0 || (l == NULL && r != NULL) || (l != NULL && r == NULL)) {
        *sym = 0;
        return;
    }

    if (l == NULL && r == NULL) {
        return ;
    }

    if (l->val != r->val) {
        *sym = 0;
        return ;
    }
    traverse_to_judge(l->left, r->right, sym);
    traverse_to_judge(l->right, r->left, sym);
}

bool isSymmetric(struct TreeNode* root) {
    int sym = 1;
    
    if (root == NULL) {
        return true;
    }
    
    traverse_to_judge(root->left, root->right, &sym);
    if (sym == 0) {
        return false;
    } else {
        return true;
    }
}
#endif

bool isSymmetric(struct TreeNode* root) {
    const int max = 1000;
    int stack1[max], stack2[max];
    int index1 = -1, index2 = -1;
    struct TreeNode *l = NULL, *r = NULL;

    if (root == NULL) {
        return true;
    }
    
    l = root->left;
    r = root->right;
    
    if ((l && !r) || (!l && r)) {
        return false;
    }

    while ((l && r) || (index1 != -1 && index2 != -1)) {
        if (l) {
            index1++;
            stack1[index1] = l;
            l = l->left;

            index2++;
            stack2[index2] = r;
            r = r->right;
        } else {
            l = stack1[index1];
            index1--;
            r = stack2[index2];
            index2--;
            if (l->val != r->val) {
                return false;
            }
            l = l->right;
            r = r->left;
        }

        if ((l && !r) || (!l && r)) {
            return false;
        }
    }
    
    return true;
}
