/*
 * 题目：给定两个非空链表来表示两个非负整数。位数按照逆序方式存储，它们的每个节点只存储单个数字。
 * 将两数相加返回一个新的链表。你可以假设除了数字 0 之外，这两个数字都不会以零开头。
 */

/*
 * 思路：一般会想到将链表转换为（长）整型进行计算，再将计算结果转换为链表，这是一种非常错误的方式，
 * 因为不管整型还是长整型，它们都是有一定的长度的，而链表的长度是不确定的，因此唯一正确的做法就是
 * 模拟加法运算的过程，但是要注意进位问题。
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int carry = 0, sum = 0;
    struct ListNode *l3 = malloc(sizeof(struct ListNode));
    struct ListNode *tmpl = l3, *tmpl_prev = l3;
    
    while ((l1 != NULL) && (l2 != NULL)) {
        sum = l1->val + l2->val + carry;
        carry = sum / 10;
        tmpl->val = sum % 10;
        tmpl->next = malloc(sizeof(struct ListNode));
        tmpl_prev = tmpl;
        tmpl = tmpl->next;
        l1 = l1->next;
        l2 = l2->next;
    }
    
    if (l1 != NULL) {
        while (l1) {
            sum = l1->val + carry;
            tmpl->val = sum %10;
            carry = sum /10;
            tmpl->next = malloc(sizeof(struct ListNode));
            tmpl_prev = tmpl;
            tmpl = tmpl->next;
            l1 = l1->next;
        }
    } else if (l2 != NULL) {
        while (l2) {
            sum = l2->val + carry;
            tmpl->val = sum %10;
            carry = sum /10;
            tmpl->next = malloc(sizeof(struct ListNode));
            tmpl_prev = tmpl;
            tmpl = tmpl->next;
            l2 = l2->next;
        }
    }
    
    if (carry) {
        tmpl->val = carry;
        tmpl->next = NULL;
    } else {
        free(tmpl);
        tmpl_prev->next = NULL;
    }
    
    return l3;
}
