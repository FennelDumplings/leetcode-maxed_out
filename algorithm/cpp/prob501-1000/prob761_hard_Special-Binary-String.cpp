// prob761: Special Binary String

/*
 * https://leetcode-cn.com/problems/special-binary-string/
 */

#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// 10 是特殊序列
// (特殊序列)(特殊序列)  : 1010
// 1(特殊序列)0  : 1100
class Solution {
public:
    string makeLargestSpecial(string S) {
        int n = S.size();
        if(n == 2)
            return S;
        // n >= 4
        // 将 S 分解为若干不可再分解的特殊序列子串，求解每个特殊序列子串，将所得结果排序
        // 如果始终没有找到 i 使得 S[0..i] 是特殊序列，则求 S[1..n-2]
        int left = 0;
        vector<string> subS;
        while(left < n)
        {
            int right = left;
            int cnt = 0;
            while(right < n)
            {
                if(S[right] == '1')
                    ++cnt;
                if(((right - left) & 1) && cnt == (right - left + 1) / 2)
                {
                    subS.push_back(S.substr(left, right - left + 1));
                    break;
                }
                ++right;
            }
            left = right + 1;
        }
        int m = subS.size();
        if(m == 1)
            return S[0] + makeLargestSpecial(S.substr(1, n - 2)) + S[n - 1];
        vector<string> results(m);
        for(int i = 0; i < m; ++i)
            results[i] = makeLargestSpecial(subS[i]);
        sort(results.begin(), results.end(), greater<string>());
        string ans = "";
        for(const string &p: results)
            ans += p;
        return ans;
    }
};
