// prob1363: Largest Multiple of Three

/*
 * https://leetcode-cn.com/problems/largest-multiple-of-three/
 */

#include <string>
#include <vector>

using namespace std;

class Solution_2 {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        vector<int> cnts(10);
        int sum = 0;
        for(int i: digits)
        {
            sum += i;
            ++cnts[i];
        }
        if(sum % 3 == 1)
        {
            bool flag = false;
            for(int i = 1; i <= 9; i += 3)
            {
                if(cnts[i] > 0)
                {
                    flag = true;
                    --cnts[i];
                    break;
                }
            }
            if(!flag)
            {
                int cnt = 2;
                int i = 2;
                while(i <= 9)
                {
                    if(cnts[i] > 0)
                    {
                        --cnts[i];
                        --cnt;
                    }
                    else
                        i += 3;
                    if(cnt == 0)
                    {
                        flag = true;
                        break;
                    }
                }
            }
            if(!flag)
                return "";
        }
        else if(sum % 3 == 2)
        {
            bool flag = false;
            for(int i = 2; i <= 9; i += 3)
            {
                if(cnts[i] > 0)
                {
                    flag = true;
                    --cnts[i];
                    break;
                }
            }
            if(!flag)
            {
                int cnt = 2;
                int i = 1;
                while(i <= 9)
                {
                    if(cnts[i] > 0)
                    {
                        --cnts[i];
                        --cnt;
                    }
                    else
                        i += 3;
                    if(cnt == 0)
                    {
                        flag = true;
                        break;
                    }
                }
            }
            if(!flag)
                return "";
        }
        string result;
        for(int i = 9; i >= 0; --i)
        {
            if(i == 0 && result.empty())
            {
                if(cnts[0] == 0)
                    return "";
                else
                    return "0";
            }
            result += string(cnts[i], '0' + i);
        }
        return result;
    }
};

#include <climits>
#include <algorithm>

class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        int n = digits.size();
        sort(digits.begin(), digits.end());
        vector<vector<int>> dp(n + 1, vector<int>(3, 0));
        for(int j = 1; j < 3; ++j)
            dp[0][j] = INT_MIN;
        for(int i = 1; i <= n; ++i)
            for(int j = 0; j < 3; ++j)
                dp[i][j] = max(dp[i - 1][j], 1 + dp[i - 1][((j - (digits[i - 1] % 3)) + 3) % 3]);
        if(dp[n][0] < 0)
            return "";

        string result;
        int j = 0;
        for(int i = n; i >= 1; --i)
        {
            if(dp[i][j] == 1 + dp[i - 1][(j - (digits[i - 1] % 3) + 3) % 3])
            {
                // 选了 digits[i]
                result += to_string(digits[i - 1]);
                j = (j - (digits[i - 1] % 3) + 3) % 3;
                if(result == "0")
                    return "0";
            }
        }
        return result;
    }
};
