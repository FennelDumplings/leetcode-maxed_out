// prob1234: Replace the Substring for Balanced String

/*
 * https://leetcode-cn.com/problems/replace-the-substring-for-balanced-string/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int balancedString(string s) {
        int n = s.size();
        vector<int> diffs(4);
        for(int i = 0; i < n; ++i)
            ++diffs[ch2idx(s[i])];
        for(int &i: diffs)
        {
            i = max(0, i - n / 4);
        }
        vector<int> cnts(4);
        if(check(diffs, cnts))
            return 0;
        int left = 0, right = 0;
        int ans = n;
        while(right < n)
        {
            while(right < n && !check(diffs, cnts))
            {
                ++cnts[ch2idx(s[right])];
                ++right;
            }
            if(!check(diffs, cnts))
                break;
            while(check(diffs, cnts))
            {
                --cnts[ch2idx(s[left])];
                ++left;
            }
            ans = min(ans, right - left + 1);
        }
        return ans;
    }

private:
    bool check(const vector<int>& diffs, const vector<int>& cnts)
    {
        for(int i = 0; i < 4; ++i)
            if(diffs[i] > cnts[i])
                return false;
        return true;
    }

    int ch2idx(char ch)
    {
        if(ch == 'Q')
            return 0;
        else if(ch == 'W')
            return 1;
        else if(ch == 'E')
            return 2;
        else
            return 3;
    }
};
