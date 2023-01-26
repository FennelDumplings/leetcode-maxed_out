// prob318: Maximum Product of Word Lengths

/*
 * https://leetcode-cn.com/problems/maximum-product-of-word-lengths/
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxProduct(vector<string>& words) {
        int n = words.size();
        if(n < 2) return 0;
        vector<int> keys(n);
        for(int i = 0; i < n; ++i)
        {
            int key = get_key(words[i]);
            keys[i] = key;
        }
        int ans = 0;
        for(int i = 0; i < n - 1; ++i)
            for(int j = i + 1; j < n; ++j)
            {
                if((keys[i] & keys[j]) == 0)
                    ans = max(ans, (int)words[i].size() * (int)words[j].size());
            }
        return ans;
    }

private:
    int get_key(const string& w)
    {
        int key = 0;
        for(const char &ch: w)
            key |= (1 << (ch - 'a'));
        return key;
    }
};
