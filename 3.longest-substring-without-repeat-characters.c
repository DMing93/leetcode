/*
 * 题目：给定一个字符串，找出不含有重复字符的最长子串的长度。
 * 示例：
 * 给定 "abcabcbb" ，没有重复字符的最长子串是 "abc" ，那么长度就是3。
 * 给定 "bbbbb" ，最长的子串就是 "b" ，长度是1。
 * 给定 "pwwkew" ，最长子串是 "wke" ，长度是3。请注意答案必须是一个子串，
 * "pwke" 是 子序列  而不是子串。
 */

/*
 * 思路：使用一个桶和一个计数器用来计算，桶的大小为256，对应256个ascii字符，
 * 桶中每个位置初值为0，计数器初值为0；这里需要双层循环，对每一个字符起始的子串都需要
 * 进行一次遍历，如何判断子串到达最长呢？只要字符对应的桶的位置为0，就可以继续，
 * 直到遇到了桶里的一个位置处值为1，这说明这个字符之前已经出现过一次，计数器每次都记录
 * 下当前子串的长度，如果当前子串的长度超过了之前记录的最大长度，更新最大长度。
 */

int lengthOfLongestSubstring(char* s) {
    int max_len = 0, start = 0, i = 0;
    int len = strlen(s);
    int bucket[255];
    int count = 0;
    
    for (start = 0; start < len; start++) {
        memset(bucket, 0, sizeof(int) * 255);
        count = 0;
        for (i = start; i < len; i++) {
            if (bucket[s[i]] == 0) {
                bucket[s[i]] ++;
                count ++;
            } else {
                break;
            }
        }
        if (max_len < count) {
            max_len = count;
        }
    }
    
    return max_len;
}
