// prob1531: String Compression II

/*
 * https://leetcode-cn.com/problems/string-compression-ii/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.size();
        vector<int> ss;
        int i = 0;
        while(i < n)
        {
            char ch = s[i];
            int j = i + 1;
            while(j < n && s[j] == ch)
                ++j;
            ss.push_back
        }

    }
};
