// prob1297: Maximum Number of Occurrences of a Substring

/*
 * https://leetcode-cn.com/problems/maximum-number-of-occurrences-of-a-substring/
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int n = s.size();
        vector<int> cnts(26);
        unordered_map<string, int> mapping;
        int cnt = 0;
        for(int i = 0; i < minSize; ++i)
        {
            if(cnts[s[i] - 'a'] == 0)
                ++cnt;
            ++cnts[s[i] - 'a'];
        }
        if(cnt <= maxLetters)
            ++mapping[s.substr(0, minSize)];
        for(int i = minSize; i < n; ++i)
        {
            --cnts[s[i - minSize] - 'a'];
            if(cnts[s[i - minSize] - 'a'] == 0)
                --cnt;
            if(cnts[s[i] - 'a'] == 0)
                ++cnt;
            ++cnts[s[i] - 'a'];
            if(cnt <= maxLetters)
                ++mapping[s.substr(i - minSize + 1, minSize)];
        }
        int ans = 0;
        for(auto i: mapping)
            ans = max(ans, i.second);
        return ans;
    }
};
