// prob907: Sum of Subarray Minimums

/*
 * Given an array of integers A, find the sum of min(B), where B ranges over every (contiguous) subarray of A.
 * Since the answer may be large, return the answer modulo 10^9 + 7.
 */

/*
 * Example 1:
 * Input: [3,1,2,4]
 * Output: 17
 * Explanation: Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
 * Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.  Sum is 17.
 */

/*
 * Note:
 * 1 <= A.length <= 30000
 * 1 <= A[i] <= 30000
 */

#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int sumSubarrayMins(vector<int>& A) {
        int n = A.size();
        const int MOD = 1e9 + 7;
        stack<int> st;
        st.push(-1);
        // 左边第 1 个 < A[j] 的位置
        vector<int> lefts(n, -1);
        // 右边第 1 个 <= A[j] 的位置
        vector<int> rights(n, -1);
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            while(st.top() != -1 && A[st.top()] >= A[i])
            {
                int j = st.top();
                st.pop();
                lefts[j] = st.top();
                rights[j] = i;
                result = (result + A[j] * (i - j) * (j - st.top())) % MOD;
            }
            st.push(i);
        }
        while(st.top() != -1)
        {
            int j = st.top();
            st.pop();
            lefts[j] = st.top();
            rights[j] = n;
            result = (result + A[j] * (n - j) * (j - st.top())) % MOD;
        }
        return result;
    }
};

