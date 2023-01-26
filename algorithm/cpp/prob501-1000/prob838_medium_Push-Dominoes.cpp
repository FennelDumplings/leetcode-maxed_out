// prob838: Push Dominoes

/*
 * https://leetcode-cn.com/problems/push-dominoes/
 */

/*
 * Example 1:
 *
 * Input: ".L.R...LR..L.."
 * Output: "LL.RR.LLRRLL.."
 * Example 2:
 *
 * Input: "RR.L"
 * Output: "RR.L"
 * Explanation: The first domino expends no additional force on the second domino.
 */

/*
 * Note:
 * 0 <= N <= 10^5
 * String dominoes contains only 'L', 'R' and '.'
 */

#include <string>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    string pushDominoes(string dominoes) {
        int n = dominoes.size();
        string &s = dominoes;
        int lR = INT_MIN; // 左侧最近的 R 的位置
        int lL = INT_MIN; // 左侧最近的 L 的位置
        vector<int> LL(n, INT_MIN), LR(n, INT_MIN);
        for(int i = 0; i < n; ++i)
        {
            LL[i] = lL;
            LR[i] = lR;
            if(s[i] == 'L')
                lL = i;
            else if(s[i] == 'R')
                lR = i;
        }
        vector<int> RL(n, INT_MAX), RR(n, INT_MAX);
        int rL = INT_MAX, rR = INT_MAX;
        for(int i = n - 1; i >= 0; --i)
        {
            RL[i] = rL;
            RR[i] = rR;
            if(s[i] == 'L')
                rL = i;
            else if(s[i] == 'R')
                rR = i;
        }
        string result = s;
        for(int i = 0; i < n; ++i)
        {
            if(s[i] != '.') continue;
            int ll = LL[i], lr = LR[i], rl = RL[i], rr = RR[i];
            if(ll == lr || rl == rr)
            {
                if(ll == lr && rl < rr)
                    result[i] = result[i] = 'L';
                else if(rl == rr && ll < lr)
                    result[i] = result[i] = 'R';
                continue;
            }
            if(ll < lr && rr < rl)
                result[i] = 'R';
            else if(lr < ll && rr < rl)
                continue;
            else if(lr < ll && rl < rr)
                result[i] = 'L';
            else
            {
                if(i - lr > rl - i)
                    result[i] = 'L';
                else if(i - lr < rl - i)
                    result[i] = 'R';
            }
        }
        return result;
    }
};
