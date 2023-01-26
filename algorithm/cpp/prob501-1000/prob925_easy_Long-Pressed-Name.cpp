// prob925: Long Pressed Name

/*
 * https://leetcode-cn.com/problems/long-pressed-name/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isLongPressedName(string name, string typed) {
        int n = name.size();
        int i = 0;
        string s1;
        vector<int> cnts1;
        while(i < n)
        {
            char ch = name[i];
            int j = i;
            while(j < n && name[j] == ch)
                ++j;
            s1 += ch;
            cnts1.push_back(j - i);
            i = j;
        }
        n = typed.size();
        i = 0;
        string s2;
        vector<int> cnts2;
        while(i < n)
        {
            char ch = typed[i];
            int j = i;
            while(j < n && typed[j] == ch)
                ++j;
            s2 += ch;
            cnts2.push_back(j - i);
            i = j;
        }
        int m1 = s1.size();
        int m2 = s2.size();
        if(m1 != m2)
            return false;
        int m = m1;
        for(i = 0; i < m; ++i)
        {
            if(s1[i] != s2[i])
                return false;
            if(cnts1[i] > cnts2[i])
                return false;
        }
        return true;
    }
};
