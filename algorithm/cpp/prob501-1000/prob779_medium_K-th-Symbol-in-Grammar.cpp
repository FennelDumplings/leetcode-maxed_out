// prob779: K-th Symbol in Grammar

/*
 * https://leetcode-cn.com/problems/k-th-symbol-in-grammar/
 */

class Solution {
public:
    int kthGrammar(int N, int K) {
        return solve(N, K);
    }

private:
    int solve(int N, int K)
    {
        if(N == 1)
            return 0;
        int ans = -1;
        int top_ans = solve(N - 1, (K + 1) / 2);
        if(top_ans == 0)
        {
            if(K & 1)
                ans = 0;
            else
                ans = 1;
        }
        else
        {
            if(K & 1)
                ans = 1;
            else
                ans = 0;
        }
        return ans;
    }
};
