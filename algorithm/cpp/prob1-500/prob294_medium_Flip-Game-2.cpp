// prob294: Flip Game 2

/*
 * You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -,
 * you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer
 * make a move and therefore the other person will be the winner.
 * Write a function to determine if the starting player can guarantee a win.
 */

/*
 * Example:
 * Input: s = "++++"
 * Output: true
 * Explanation: The starting player can guarantee a win by flipping the middle "++" to become "+--+".
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// 记忆化搜索
// 策梅洛定理
class Solution {
public:
    bool canWin(string s) {
        int n = s.size();
        if(n < 2) return false;
        unordered_map<string, bool> dp;
        return solve(s, dp);
    }

private:
    bool solve(string& s, unordered_map<string, bool>& dp)
    {
        int n = s.size();
        if(dp.find(s) != dp.end()) // 该状态已经算过
            return dp[s];
        for(int i = 0; i < n - 1; ++i) // 枚举所有次态
        {
            if(s[i] == '+' && s[i + 1] == '+')
            {
                s[i] = '-';
                s[i + 1] = '-';
                bool f = solve(s, dp);
                s[i] = '+';
                s[i + 1] = '+';
                if(!f)
                    return dp[s] = true;
            }
        }
        return dp[s] = false;
    }
};

// SG 定理
// g(x) = FMN(g(0) ^ g(x - 2))
// g(0) = 0
// g(1) = 0
class Solution_2 {
public:
    bool canWin(string s) {
        int n = s.size();
        if(n < 2) return false;
        vector<int> state = _get_state(s);
        int maxx = 0;
        for(int x: state) maxx = max(maxx, x);
        if(maxx < 2) return false;
        vector<int> g(maxx + 1, 0);
        vector<int> sub;
        for(int x = 2; x <= maxx; ++x)
        {
            sub.clear();
            for(int i = 0; i * 2 <= x - 2; ++i)
            {
                // (0, n - 2) (1, n - 3), ...
                // (i, n - 2 - i)
                sub.push_back(g[i] ^ g[x - 2 - i]);
            }
            g[x] = _fmn(sub);
        }
        int res = 0;
        for(int x: state) res ^= g[x];
        return res > 0;
    }

private:
    int _fmn(vector<int>& sub)
    {
        int n = sub.size();
        for(int i = 0; i < n; ++i)
        {
            if(sub[i] == -1) continue;
            int nxt = sub[i];
            while(nxt < n && sub[nxt] != -1)
            {
                int tmp = sub[nxt];
                sub[nxt] = -1;
                nxt = tmp;
            }
        }
        for(int i = 0; i < n; ++i)
            if(sub[i] != -1)
                return i;
        return n;
    }

    vector<int> _get_state(string& s)
    {
        int n = s.size();
        int i = 0;
        vector<int> result;
        while(i < n)
        {
            while(i < n && s[i] == '-')
                ++i;
            if(i == n) break;
            int j = i;
            while(j < n && s[j] == '+')
                ++j;
            int len = j - i;
            if(len >= 2)
                result.push_back(len);
            i = j;
        }
        return result;
    }
};
