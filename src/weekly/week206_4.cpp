
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isTransformable(string s, string t) {
        int n = s.size();
        vector<int> cnt1(10, 0);
        vector<int> cnt2(10, 0);
        vector<int> rs(10, 0);
        vector<int> rt(10, 0);
        for(int i = 0; i < n; ++i)
        {
            ++cnt1[s[i] - '0'];
            ++cnt2[t[i] - '0'];
            rs[s[i] - '0'] = i;
            rt[t[i] - '0'] = i;
        }
        for(char c = '0'; c <= '9'; ++c)
            if(cnt1[c - '0'] != cnt2[c - '0'])
                return false;
        string tmp = s;
        sort(tmp.begin(), tmp.end());
        vector<int> mapping(10, -1); // mapping[x]:= x 的最大下标
        for(char c = '0'; c <= '9'; ++c)
        {
            mapping[c - '0'] = upper_bound(tmp.begin(), tmp.end(), c) - tmp.begin() - 1;
        }
        for(char c = '0'; c <= '9'; ++c)
        {
            if(rt[c - '0'] > rs[c - '0'] && rt[c - '0'] > mapping[c - '0'])
                return false;
        }
        return true;
    }
};
