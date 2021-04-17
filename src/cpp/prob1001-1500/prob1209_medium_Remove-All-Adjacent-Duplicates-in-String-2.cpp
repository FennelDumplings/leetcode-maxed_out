// prob1209:  Remove All Adjacent Duplicates in String II`

/*
 * https://leetcode-cn.com/problems/remove-all-adjacent-duplicates-in-string-ii/
 */

#include <string>

using namespace std;

class Solution {
public:
    string removeDuplicates(string s, int k) {
        string st;
        int n = s.size();
        for(int i = 0; i < n; ++i)
        {
            st += s[i];
            char cur = s[i];
            if((int)st.size() >= k && st.substr((int)st.size() - k) == string(k, cur))
                st.erase((int)st.size() - k);
        }
        return st;
    }
};
