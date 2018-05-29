/*
 * 题目：给定一个二叉树，返回其节点值的锯齿形层次遍历。
 * （即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
 *
 * 例如：
 * 给定二叉树 [3,9,20,null,null,15,7],
 *
 *      3
 *     / \
 *    9  20
 *      /  \
 *     15   7
 *
 * 返回锯齿形层次遍历如下：
 *
 * [
 *  [3],
 *  [20,9],
 *  [15,7]
 * ]
 */

/*
 * 思路：二叉树的层次遍历，需要用到队列。首先将根放入队列中，然后只要队列不为空，
 * 从中取出一个元素进行处理，将该元素的左右儿子加入队列中。本体要求输出为Z形，所以
 * 只要按照层次输出，然后对于偶数层，将输出元素逆序即可。
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/*
 * Let's build a queue first.
 */
typedef struct queue_element {
    struct TreeNode *node;
    struct queue_element *prev;
    struct queue_element *next;
} queue_element_t;

void init_queue(queue_element_t **head, queue_element_t **tail)
{
    *head = *tail = NULL;
}

int is_queue_empty(queue_element_t **head, queue_element_t **tail)
{
    if (*head == NULL && *tail == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void add_element(struct TreeNode *node, queue_element_t **head, queue_element_t **tail)
{
    queue_element_t *e = malloc(sizeof(*e));
    if (is_queue_empty(head, tail)) {
        e->node = node;
        e->prev = NULL;
        e->next = NULL;
        *head = e;
        *tail = e;
    } else {
        e->node = node;
        e->prev = *tail;
        e->next = NULL;
        (*tail)->next = e;
        *tail = e;
    }
}

struct TreeNode *del_element(queue_element_t **head, queue_element_t **tail)
{
    struct TreeNode *t = NULL;
    queue_element_t *q = NULL;

    if (is_queue_empty(head, tail)) {
        return NULL;
    }

    q = *head;
    t = q->node;

    *head = (*head)->next;
    if (*head == NULL) {
        *head = *tail = NULL;
    }

    free(q);
    return t;
}

void reverse(int *array, int count)
{
    int back[count];
    int i = 0;
    
    for (i = 0; i < count; i++) {
        back[i] = array[i];
    }
    
    for (i = 0; i < count; i++) {
        array[count - 1 - i] = back[i];
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** zigzagLevelOrder(struct TreeNode* root, int** columnSizes, int* returnSize) {
    int **arrays = NULL;
    int i = 0, level_count = 0, len = 0;
    queue_element_t *head, *tail;
    struct TreeNode *e = NULL;
    int level = 1;

    *columnSizes = NULL;
    *returnSize = 0;
    init_queue(&head, &tail);

    if (root == NULL) {
        return NULL;
    }

    add_element(root, &head, &tail);
    level_count++;
    len = level_count;
    level_count = 0;

    while (!is_queue_empty(&head, &tail)) {
        (*returnSize)++;
        arrays = realloc(arrays, sizeof(int *) * (*returnSize));
        arrays[(*returnSize) - 1] = malloc(sizeof(int) * len);
        *columnSizes = realloc(*columnSizes, sizeof(int) * (*returnSize));
        (*columnSizes)[(*returnSize) - 1] = len;

        while (i < len) {
            e = del_element(&head, &tail);
            arrays[(*returnSize) - 1][i] = e->val;
            i++;
            if (e->left) {
                add_element(e->left, &head, &tail);
                level_count++;
            }
            if (e->right) {
                add_element(e->right, &head, &tail);
                level_count++;
            }
        }/* end while i < len */
        if (level % 2 == 0) {
            reverse(arrays[(*returnSize) - 1], len);
        }
        
        len = level_count;
        level_count = 0;
        i = 0;
        level++;
    }

    return arrays;
}
