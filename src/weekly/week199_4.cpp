#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int getLengthOfOptimalCompression(string s, int k) {
        if(s.empty()) return 0;
        int n = s.size();
        // dp[i][j] := [i..j] 上的缩写
        vector<vector<string>> dp(n, vector<string>(n, ""));
        for(int len = 1; len <= n; ++len)
        {
            for(int i = 0; i < n - len + 1; ++i)
            {
                int j = i + len - 1;
                dp[i][j] = s.substr(i, len);
                for(int k = i; k < j; ++k)
                {
                    string left = dp[i][k], right = dp[k + 1][j];
                    if(left.size() + right.size() < dp[i][j].size())
                        dp[i][j] = left + right;
                }
                string tmp = s.substr(i, len), replace = "";
                auto pos = (tmp + tmp).find(tmp, 1);
                if(pos >= tmp.size())
                    replace = tmp;
                else
                {
                    replace = dp[i][i + pos - 1] + to_string(tmp.size() / pos);
                }
                if(replace.size() < dp[i][j].size())
                    dp[i][j] = replace;
            }
        }
        int ans = get(dp[0][n - 1], k);
        return ans;
    }

    int get(const string& s, int k)
    {
        if(k == 0)
            return s.size();
        return s.size();

    }
};
