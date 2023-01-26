// prob1170: Compare Strings by Frequency of the Smallest Character

/*
 * https://leetcode-cn.com/problems/compare-strings-by-frequency-of-the-smallest-character/
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int f(const string& s)
{
    vector<int> cnt(26);
    for(char ch: s)
    {
        ++cnt[ch - 'a'];
    }
    for(int i: cnt)
        if(i > 0)
            return i;
    return -1;
}

class Solution {
public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        int n = words.size();
        vector<int> vec(n);
        for(int i = 0; i < n; ++i)
        {
            int x = f(words[i]);
            vec[i] = x;
        }
        sort(vec.begin(), vec.end());
        int m = queries.size();
        vector<int> result(m);
        for(int i = 0; i < m; ++i)
        {
            int y = f(queries[i]);
            auto it = upper_bound(vec.begin(), vec.end(), y);
            result[i] = vec.end() - it;
        }
        return result;
    }
};
