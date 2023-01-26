// prob992: Subarrays with K Different Integers

/*
 * Given an array A of positive integers, call a (contiguous, not necessarily distinct) subarray of
 * A good if the number of different integers in that subarray is exactly K.
 * (For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.)
 * Return the number of good subarrays of A.
 */

/*
 * Note:
 * 1 <= A.length <= 20000
 * 1 <= A[i] <= A.length
 * 1 <= K <= A.length
 */

/*
 * Example 1:
 * Input: A = [1,2,1,2,3], K = 2
 * Output: 7
 * Explanation: Subarrays formed with exactly 2 different integers: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2].
 * Example 2:
 * Input: A = [1,2,1,3,4], K = 3
 * Output: 3
 * Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].
 */

#include <vector>
#include <unordered_map>

using namespace std;


// 维护两个滑窗
// [left1, right]: 以 right 结尾，含 K 个不同整数
// [left2, right]: 以 right 结尾，含 K - 1 个不同整数
// 以right结尾可贡献 left2 - left1 个答案
// 具体做法：
// lower[right]: 遍历一遍，记录对应的 left1
// upper[right]: 遍历一遍，记录对应的 left2
class Solution_2 {
public:
    int subarraysWithKDistinct(vector<int>& A, int K) {
        int n = A.size();
        vector<int> lower(n, 0), upper(n, 0);
        _find(upper, A, K - 1);
        _find(lower, A, K);
        int ans = 0;
        for (int i = 0; i < n; i++)
            ans += upper[i] - lower[i];
        return ans;
    }

private:
    void _find(vector<int> &last, const vector<int> &A, int K) {
        int n = A.size();
        int j = 0, cur = 0;
        vector<int> vis(n + 1, 0); // A[i] 的最大值是 n
        for (int i = 0; i < n; i++)
        {
            if (vis[A[i]] == 0)
                cur++;
            vis[A[i]]++;
            while (cur == K + 1) {
                if (vis[A[j]] == 1)
                    cur--;
                vis[A[j]]--;
                j++;
            }
            // [j, i] 含有 K 个元素
            last[i] = j;
        }
    }
};

class Solution {
public:
    int subarraysWithKDistinct(vector<int>& A, int K) {
        int n = A.size();
        vector<int> cnts(n + 1);
        int num = 0;
        int left = 0, right = 0;
        int ans = 0;
        while(right < n)
        {
            while(right < n && num < K)
            {
                if(cnts[A[right]] == 0)
                    ++num;
                ++cnts[A[right]];
                ++right;
            }
            // 推进 left 时计数
            while(num == K)
            {
                ++ans;
                --cnts[A[left]];
                if(cnts[A[left]] == 0)
                    --num;
                ++left;
            }
        }
        return ans;
    }
};
