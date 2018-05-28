/*
 * 题目：给定一个整数数组和一个目标值，找出数组中和为目标值的两个数。
 *
 * 你可以假设每个输入只对应一种答案，且同样的元素不能被重复利用。
 *
 */

/*
 * 思路：蛮力搜索，对于每一个数，拿剩下的数与之匹配，找到后返回结果。
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {
    int i = 0, j = 0;
    int *ret = malloc(sizeof(int) * 2);
    memset(ret, 0, sizeof(int)*2);
    
    for (i = 0; i < numsSize; i++) {
        for (j = i+1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                ret[0] = i;
                ret[1] = j;
                return ret;
            }
        }
    }
    
    return ret;
}
