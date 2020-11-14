// prob555: Split Concatenated Strings

/*
 * https://leetcode-cn.com/problems/split-concatenated-strings/
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string splitLoopedString(vector<string>& strs) {
        string str;
        for(string &s: strs)
        {
            string t = s;
            reverse(t.begin(), t.end());
            if(t > s)
                reverse(s.begin(), s.end());
            str += s;
        }
        int n = str.size();
        int iter = 0;
        int i = 0;
        string ans = str;
        while(iter < n)
        {
            string &start = strs[i];
            int m = start.size();
            int l = iter, r = iter + m;
            string cand = str;
            // cand 向右旋转 t 单位
            rotate(cand.begin(), cand.begin() + l, cand.end());
            for(int t = l; t < r; ++t)
            {
                if(cand > ans)
                    ans = cand;
                rotate(cand.begin(), cand.begin() + 1, cand.end());
            }
            cand = str;
            reverse(cand.begin() + l, cand.begin() + r);
            rotate(cand.begin(), cand.begin() + l, cand.end());
            for(int t = l; t < r; ++t)
            {
                if(cand > ans)
                    ans = cand;
                rotate(cand.begin(), cand.begin() + 1, cand.end());
            }
            iter = r;
            ++i;
        }
        return ans;
    }
};
