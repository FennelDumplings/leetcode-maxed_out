// prob358: Rearrange String k Distance Apart

/*
 * Given a non-empty string s and an integer k, rearrange the string such that the same characters are at least distance k from each other.
 * All input strings are given in lowercase letters. If it is not possible to rearrange the string, return an empty string "".
 */

/*
 * Example 1:
 * Input: s = "aabbcc", k = 3
 * Output: "abcabc"
 * Explanation: The same letters are at least distance 3 from each other.
 * Example 2:
 * Input: s = "aaabc", k = 3
 * Output: ""
 * Explanation: It is not possible to rearrange the string.
 * Example 3:
 * Input: s = "aaadbbcc", k = 2
 * Output: "abacabcd"
 * Explanation: The same letters are at least distance 2 from each other.
 */

#include <string>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    string rearrangeString(string s, int k) {
        int n = s.size();
        if(n == 1 || k == 0) return s;
        // 有解的条件，n / k 商 p 余 q
        // 最多有 q 个 char 的 cnt == p + 1, 其余均需要 <= p
        int p = n / k, q = n % k;

        vector<int> char_cnt(26, 0);
        int M = 0; // cnt == p + 1 的个数
        for(int i = 0; i < n; ++i)
        {
            int cur = s[i] - 'a';
            ++char_cnt[cur];
            if(char_cnt[cur] > p + 1)
                return "";
            if(char_cnt[cur] == p + 1)
            {
                ++M;
                if(M > q)
                    return "";
            }
        }
        // 在循环中没有退出说明有解

        using PII = pair<int, int>; // (频数，字符)
        priority_queue<PII> pq;
        for(int i = 0; i < 26; ++i)
        {
            if(char_cnt[i] > 0)
                pq.push(PII(char_cnt[i], i));
        }

        vector<int> prev_idx(26, -n);
        vector<PII> buffer(26);
        string result(n, ' ');
        for(int i = 0; i < n; ++i)
        {
            int m = 0;
            while(!pq.empty() && i - prev_idx[pq.top().second] < k)
            {
                buffer[m] = pq.top();
                ++m;
                pq.pop();
            }
            // if(pq.empty()) return "";
            PII cur = pq.top();
            pq.pop();
            for(int j = 0; j < m; ++j)
                pq.push(buffer[j]);
            result[i] = cur.second + 'a';
            prev_idx[cur.second] = i;
            --cur.first;
            if(cur.first > 0)
                pq.push(cur);
        }
        return result;
    }
};

// 更新答案时候，k 个字符一组
class Solution_2 {
public:
    string rearrangeString(string s, int k) {
        int n = s.size();
        if(n == 1 || k == 0) return s;
        // 有解的条件，n / k 商 p 余 q
        // 最多有 q 个 char 的 cnt == p + 1, 其余均需要 <= p
        int p = n / k, q = n % k;

        vector<int> char_cnt(26, 0);
        int M = 0; // cnt == p + 1 的个数
        for(int i = 0; i < n; ++i)
        {
            int cur = s[i] - 'a';
            ++char_cnt[cur];
            if(char_cnt[cur] > p + 1)
                return "";
            if(char_cnt[cur] == p + 1)
            {
                ++M;
                if(M > q)
                    return "";
            }
        }
        // 在循环中没有退出说明有解
        using PII = pair<int, int>; // (频数，字符)
        priority_queue<PII> pq;
        for(int i = 0; i < 26; ++i)
        {
            if(char_cnt[i] > 0)
                pq.push(PII(char_cnt[i], i));
        }

        vector<PII> buffer(k);
        string result(n, ' ');
        for(int i = 0; i < n; i += k)
        {
            for(int j = 0; j < min(k, n - i); ++j)
            {
                buffer[j] = pq.top();
                pq.pop();
            }
            for(int j = 0; j < min(k, n - i); ++j)
            {
                PII cur = buffer[j];
                result[i + j] = cur.second + 'a';
                --cur.first;
                if(cur.first > 0)
                    pq.push(cur);
            }
        }
        return result;
    }
};
