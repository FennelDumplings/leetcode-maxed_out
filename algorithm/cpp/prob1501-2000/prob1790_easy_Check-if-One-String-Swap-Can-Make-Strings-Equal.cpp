

#include <string>

using namespace std;

class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        int n = s1.size();
        int i1 = -1, i2 = -1;
        for(int i = 0; i < n; ++i)
        {
            if(s1[i] != s2[i])
            {
                if(i2 != -1)
                    return false;
                else if(i1 != -1)
                {
                    if(s1[i] == s2[i1] && s1[i1] == s2[i])
                        i2 = i;
                    else
                        return false;
                }
                else
                    i1 = i;
            }
        }
        return i1 == -1 || i2 != -1;
    }
};
