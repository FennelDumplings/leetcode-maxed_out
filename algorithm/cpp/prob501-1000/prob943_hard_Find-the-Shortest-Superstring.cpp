// prob943: Find the Shortest Superstring

/*
 * Given an array A of strings, find any smallest string that contains each string in A as a substring.
 * We may assume that no string in A is substring of another string in A.
 */

/*
 * Example 1:
 * Input: ["alex","loves","leetcode"]
 * Output: "alexlovesleetcode"
 * Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
 * Example 2:
 * Input: ["catg","ctaagt","gcta","ttca","atgcatc"]
 * Output: "gctaagttcatgcatc"
 */

/*
 * Note:
 * 1 <= A.length <= 12
 * 1 <= A[i].length <= 20
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string shortestSuperstring(vector<string>& A) {
        // n [1, 12]
        int n = A.size();
        vector<vector<int> > adj(n, vector<int>(n, 0)); // A[i] 后缀和 A[j] 前缀的重合长度
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
            {
                if(i == j)
                    continue;
                adj[i][j] = _process(A[i], A[j]);
            }
        vector<vector<int> > dp((1 << n), vector<int>(n, 0));
        vector<vector<int> > path((1 << n), vector<int>(n, -1));
        for(int state = 0; state < (1 << n); ++state)
        {
            // dp[state|(1<<j)][j] = max{dp[state][i] + adj[i][j]}
            // 已选 state, 当前在 j 的最长 overlap
            for(int j = 0; j < n; ++j)
            {
                if((1 << j) & state) continue;
                for(int i = 0; i < n; ++i)
                {
                    if(!(state & (1 << i))) continue;
                    if(dp[state | (1 << j)][j] <= dp[state][i] + adj[i][j])
                    {
                        dp[state | (1 << j)][j] = dp[state][i] + adj[i][j];
                        path[state | (1 << j)][j] = i;
                    }
                }
            }
        }
        int max_overlap = 0;
        int tail_idx = 0;
        for(int i = 0; i < n; ++i)
        {
            if(max_overlap < dp[(1 << n) - 1][i])
            {
                max_overlap = dp[(1 << n) - 1][i];
                tail_idx = i;
            }
        }
        vector<int> result_idxs;
        int idx = tail_idx;
        int s = (1 << n) - 1;
        while(idx != -1)
        {
            result_idxs.push_back(idx);
            int new_idx = path[s][idx];
            s &= (~(1 << idx));
            idx = new_idx;
        }
        reverse(result_idxs.begin(), result_idxs.end());

        int prev_idx = result_idxs[0];
        string result = A[prev_idx];
        for(int i = 1; i < n; ++i)
        {
            int cur_idx = result_idxs[i];
            int overlap = adj[prev_idx][cur_idx];
            result += A[cur_idx].substr(overlap);
            prev_idx = cur_idx;
        }
        return result;

    }

private:
    int _process(const string& s1, const string& s2)
    {
        int n1 = s1.size();
        int n2 = s2.size();
        int result = 0;
        for(int len = 1; len <= min(n1, n2); ++len)
        {
            // if(s2.substr(0, len) == s1.substr(n1 - len, len))
            //     result = len;
            int i2 = 0, i1 = n1 - len;
            while(i2 < len)
            {
                if(s1[i1] != s2[i2])
                    break;
                ++i1;
                ++i2;
            }
            if(i2 == len)
                result = len;
        }
        return result;
    }
};
