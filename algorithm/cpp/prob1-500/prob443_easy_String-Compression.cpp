// prob443: String Compression

/*
 * https://leetcode-cn.com/problems/string-compression/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int compress(vector<char>& chars) {
        if(chars.empty()) return 0;
        int n = chars.size();
        int l = 0, r = 0;
        int iter = 0;
        while(l < n)
        {
            chars[iter++] = chars[l];
            while(r < n && chars[r] == chars[l]) ++r;
            int k = r - l;
            if(k > 1)
            {
                string num_str = to_string(k);
                for(char ch: num_str)
                    chars[iter++] = ch;
            }
            l = r;
        }
        return iter;
    }
};
