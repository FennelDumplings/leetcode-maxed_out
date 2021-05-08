// prob792: Number of Matching Subsequences

/*
 * https://leetcode-cn.com/problems/number-of-matching-subsequences/
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        int n = S.size();
        vector<vector<int>> mappings(26);
        for(int i = 0; i < n; ++i)
            mappings[S[i] - 'a'].push_back(i);
        int ans = 0;
        for(const string &word: words)
        {
            int w = word.size();
            int prev = 0;
            bool flag = true;
            for(int i = 0; i < w; ++i)
            {
                const vector<int> &idxs = mappings[word[i] - 'a'];
                auto it =lower_bound(idxs.begin(), idxs.end(), prev);
                if(it == idxs.end())
                {
                    flag = false;
                    continue;
                }
                prev = *it + 1;
            }
            if(flag)
                ++ans;
        }
        return ans;
    }
};
