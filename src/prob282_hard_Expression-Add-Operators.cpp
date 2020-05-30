// prob282: Expression Add Operators

/*
 * Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.
 */

/*
 * Example 1:
 * Input: num = "123", target = 6
 * Output: ["1+2+3", "1*2*3"]
 * Example 2:
 * Input: num = "232", target = 8
 * Output: ["2*3+2", "2+3*2"]
 * Example 3:
 * Input: num = "105", target = 5
 * Output: ["1*0+5","10-5"]
 * Example 4:
 * Input: num = "00", target = 0
 * Output: ["0+0", "0-0", "0*0"]
 * Example 5:
 * Input: num = "3456237490", target = 9191
 * Output: []
 */

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        if(num.empty()) return vector<string>();
        int n = num.size();
        vector<string> result;
        string item;
        vector<vector<ll> > dp(n, vector<ll>(n, -1)); // dp[i][j] := num[i..j] 代表的数字
        dfs(num, 0, target, item, result, dp, 1, false);
        return result;
    }

private:
    using ll = long long;

    void dfs(const string& num, int left, int target, string& item, vector<string>& result, vector<vector<ll> >& dp, ll prev, bool mul)
    {
        int n = num.size();
        if(left == n) return;

        if(dp[left][n - 1] == -1)
        {
            ll tmp;
            stringstream ss;
            ss << num.substr(left);
            ss >> tmp;
            dp[left][n - 1] = tmp;
        }
        if((!mul && dp[left][n - 1] == target) || (mul && dp[left][n - 1] * prev == target))
        {
            int pos = item.size();
            item += to_string(dp[left][n - 1]);
            result.push_back(item);
            item.erase(pos);
            return;
        }

        for(int i = left; i < n; ++i)
        {
            string cur = num.substr(left, i - left + 1);
            if(dp[left][i] == -1)
            {
                ll tmp;
                stringstream ss;
                ss << cur;
                ss >> tmp;
                dp[left][i] = tmp;
            }
            int pos = item.size();
            item += cur;
            if(mul)
                prev *= dp[left][i];
            else
                prev = dp[left][i];
            // +
            item += '+';
            dfs(num, i + 1, target - prev, item, result, dp, prev, false);
            item.pop_back();
            // -
            item += '-';
            dfs(num, i + 1, prev - target, item, result, dp, prev, false);
            item.pop_back();
            // *
            item += '*';
            dfs(num, i + 1, target, item, result, dp, prev, true);
            item.pop_back();
            item.erase(pos);
        }
    }
};
