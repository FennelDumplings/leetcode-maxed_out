// prob696: Count Binary Substrings

/*
 * https://leetcode-cn.com/problems/count-binary-substrings/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int countBinarySubstrings(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        vector<int> vec;
        int left = 0;
        while(left < n)
        {
            int right = left + 1;
            while(right < n && s[right] == s[left])
                ++right;
            vec.push_back(right - left);
            left = right;
        }
        int m = vec.size();
        if(m <= 1) return 0;
        int ans = 0;
        for(int i = 1; i < m; ++i)
            ans += min(vec[i], vec[i - 1]);
        return ans;
    }
};
