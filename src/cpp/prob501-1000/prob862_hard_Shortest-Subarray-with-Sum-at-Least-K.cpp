// prob862: Shortest Subarray with Sum at Least K

/*
 * Return the length of the shortest, non-empty, contiguous subarray of A with sum at least K.
 * If there is no non-empty subarray with sum at least K, return -1.
 */

/*
 * Note:
 * 1 <= A.length <= 50000
 * -10 ^ 5 <= A[i] <= 10 ^ 5
 *  1 <= K <= 10 ^ 9
 */

/*
 * Example 1:
 * Input: A = [1], K = 1
 * Output: 1
 * Example 2:
 * Input: A = [1,2], K = 4
 * Output: -1
 * Example 3:
 * Input: A = [2,-1,2], K = 3
 * Output: 3
 */

#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

// 单调队列 120ms
class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        int n = A.size();
        vector<int> sums(n + 1, 0);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + A[i - 1];
        deque<int> dq; // dq 中存 A 的下标
        dq.push_back(0); // 前缀和的0
        int result = n + 1;
        for(int i = 1; i <= n; ++i)
        {
            // 先更新队头的答案, 若满足下式则可以更新答案
            // s[dq.front()] + K <= s[i]
            while(!dq.empty() && sums[dq.front()] + K <= sums[i])
            {
                result = min(result, i - dq.front());
                dq.pop_front();
            }

            // 然后 i 进队之前先看有没有可以弹出的
            while(!dq.empty() && sums[dq.back()] >= sums[i])
                dq.pop_back();

            dq.push_back(i);
        }
        if(result == n + 1) return -1;
        return result;
    }
};

// BIT 写法 400ms
// f 维护的是离散化后的前缀和 1 到 s(i) 中的最大的坐标值。
// query 就是询问这个最大值，update 需要在树状数组上更新离散化后的 s(i) + K 这个位置为 i。
class Solution_2 {
public:

    void update(vector<int> &f, int x, int y) {
        int n = f.size();
        for (; x < n; x += x & -x)
            f[x] = max(f[x], y);
    }

    int query(vector<int> &f, int x) {
        int t = -1;
        for (; x; x -= x & -x)
            t = max(f[x], t);
        return t;
    }

    int shortestSubarray(vector<int>& A, int K) {
        int n = A.size();
        vector<int> s(2 * n + 2, 0), d(2 * n + 2, 0);
        vector<int> f(2 * n + 3, -1);

        for (int i = 1; i <= n; i++) {
            s[i] = s[i - 1] + A[i - 1];
            d[i] = s[i];
        }
        for (int i = n + 1; i <= 2 * n + 1; i++) {
            s[i] = s[i - n - 1] + K;
            d[i] = s[i];
        }

        sort(d.begin(), d.end());

        // 离散化
        for (int i = 0; i <= 2 * n + 1; i++)
            s[i] = lower_bound(d.begin(), d.end(), s[i]) - d.begin() + 1;

        update(f, s[n + 1], 0);

        int ans = n + 1;

        for (int i = 1; i <= n; i++) {
            int t = query(f, s[i]);
            if (t != -1)
                ans = min(ans, i - t);
            update(f, s[i + n + 1], i);
        }

        if (ans == n + 1)
            ans = -1;

        return ans;
    }
};
