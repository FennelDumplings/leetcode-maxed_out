// prob1433: Check If a String Can Break Another String

/*
 * https://leetcode-cn.com/problems/check-if-a-string-can-break-another-string/
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool checkIfCanBreak(string s1, string s2) {
        int n = s1.size();
        if(n == 1) return true;
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        // 找到第一个不相同的位置
        int i = 0;
        while(i < n && s1[i] == s2[i])
            ++i;
        if(i == n) return true;
        if(s1[i] > s2[i])
        {
            for(int j = i + 1; j < n; ++j)
                if(s1[j] < s2[j])
                    return false;
        }
        else
        {
            for(int j = i + 1; j < n; ++j)
                if(s1[j] > s2[j])
                    return false;
        }
        return true;
    }
};
