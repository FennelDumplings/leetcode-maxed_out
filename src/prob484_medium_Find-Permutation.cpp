// prob484: Find Permutation

/*
 * https://leetcode-cn.com/problems/find-permutation/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> findPermutation(string s) {
        int n = s.size();
        // 1..n+1
        vector<int> net_nd(n, 0); // 从该点往后的连续 D 个数
        int i = 0;
        while(i < n)
        {
            const char &ch = s[i];
            if(ch == 'I')
            {
                net_nd[i] = 0;
                ++i;
                continue;
            }
            int j = i + 1;
            while(j < n && s[j] == 'D')
                ++j;
            int t = j - i;
            for(int k = 0; k < j - i; ++k)
                net_nd[i + k] = t--;
            i = j;
        }
        int cur = 0;
        vector<int> result;
        if(net_nd[0] == 0)
            result.push_back(++cur);
        else
        {
            result.push_back(cur + net_nd[0] + 1);
            cur += net_nd[0] + 1;
        }
        int maxx = cur;
        for(int i = 0; i < n; ++i)
        {
            if(s[i] == 'D')
            {
                result.push_back(--cur);
            }
            else
            {
                if(i < n - 1)
                {
                    result.push_back(maxx + 1 + net_nd[i + 1]);
                    maxx += 1 + net_nd[i + 1];
                }
                else
                    result.push_back(++maxx);
                cur = maxx;
            }
        }
        return result;
    }
};
