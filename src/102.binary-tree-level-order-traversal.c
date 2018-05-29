/*
 * 给定一个二叉树，返回其按层次遍历的节点值。 （即逐层地，从左到右访问所有节点）。
 *
 * 例如:
 * 给定二叉树: [3,9,20,null,null,15,7],
 *
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 *
 * 返回其层次遍历结果：
 *
 * [
 *  [3],
 *  [9,20],
 *  [15,7]
 * ]
 */

/*
 * 思路：二叉树的层次遍历，即广度优先搜索，需要使用到队列。首先将根放入队列中，
 * 只要队列不为空，从其中取出一个元素进行处理，然后将该元素的左儿子和右儿子放入
 * 队列中进行处理。
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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
/*
 * Let's build a queue first.
 */
typedef struct queue_element {
    struct TreeNode *node;
    struct queue_element *next;
    struct queue_element *prev;
} queue_element_t;

void init_queue(queue_element_t **tail, queue_element_t **head)
{
    *tail = *head = NULL;
}

void add_element(struct TreeNode *node, queue_element_t **tail, queue_element_t **head)
{
    struct queue_element *e = malloc(sizeof(*e));
    if (is_queue_empty(head, tail)) {
        e->node = node;
        e->next = NULL;
        e->prev = NULL;
        *head = *tail = e;
    } else {
        e->node = node;
        e->next = NULL;
        e->prev = *tail;
        (*tail)->next = e;
        *tail = e;
    }
}

struct TreeNode *del_element(queue_element_t **head, queue_element_t **tail)
{
    struct TreeNode *e = NULL;
    queue_element_t *q = NULL;
    if (is_queue_empty(head, tail)) {
        return NULL;
    }
    q = *head;
    e = (*head)->node;
    *head = (*head)->next;
    if ((*head) == NULL) {
        *tail = NULL;
    }
    free(q);
    return e;
}

int is_queue_empty(queue_element_t **head, queue_element_t **tail)
{
    if (*head == NULL && *tail == NULL) {
        return 1;
    } else {
        return 0;
    }
}

int** levelOrder(struct TreeNode* root, int** columnSizes, int* returnSize) {
    queue_element_t *head, *tail;
    struct TreeNode *e = NULL;
    int len = 0, level_count = 0, i = 0;
    int **arrays = NULL;
    *columnSizes = NULL;
    *returnSize = 0;

    if (root == NULL) {
        return NULL;
    }
    
    init_queue(&head, &tail);
    add_element(root, &tail, &head);
    level_count++;
    len = level_count;
    level_count = 0;

    while (!is_queue_empty(&head, &tail)) {
        (*returnSize)++;
        arrays = realloc(arrays, sizeof(int*)*(*returnSize));
        arrays[(*returnSize) - 1] = malloc(sizeof(int) * len);
        *columnSizes = realloc(*columnSizes, sizeof(int) * (*returnSize));
        (*columnSizes)[(*returnSize) - 1] = len;
        while (i < len) {
            e = del_element(&head, &tail);
            arrays[(*returnSize)-1][i] = e->val;
            i++;
            if (e->left) {
                add_element(e->left, &tail, &head);
                level_count++;
            }
            if (e->right) {
                add_element(e->right, &tail, &head);
                level_count++;
            }
        }
        len = level_count;
        level_count = 0;
        i = 0;
    }

    return arrays;
}
