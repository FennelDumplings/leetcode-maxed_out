// prob1239: Maximum Length of a Concatenated String with Unique Characters

/*
 * https://leetcode-cn.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int maxLength(vector<string>& arr) {
        vector<int> vec;
        for(const string& s: arr)
        {
            int v = 0;
            bool flag = true;
            for(const char &ch: s)
            {
                if(v >> (ch - 'a') & 1)
                {
                    flag = false;
                    break;
                }
                v |= (1 << (ch - 'a'));
            }
            if(flag)
                vec.push_back(v);
        }
        int ans = 0;
        dfs(vec, 0, 0,ans);
        return ans;
    }

private:
    void dfs(const vector<int>& vec, int pos, int state, int& ans)
    {
        int n = vec.size();
        if(pos == n)
        {
            ans = max(ans, get_cnt(state));
            return;
        }
        dfs(vec, pos + 1, state, ans);
        if(check(vec[pos], state))
            dfs(vec, pos + 1, state | vec[pos], ans);
    }

    int get_cnt(int x)
    {
        int ans = 0;
        while(x)
        {
            if(x & 1)
                ++ans;
            x >>= 1;
        }
        return ans;
    }

    bool check(int cand, int state)
    {
        while(cand > 0 && state > 0)
        {
            if((cand & 1) && (state & 1))
                return false;
            cand >>= 1;
            state >>= 1;
        }
        return true;
    }
};
