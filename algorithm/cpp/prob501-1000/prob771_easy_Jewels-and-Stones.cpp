// prob771: Jewels and Stones

/*
 * https://leetcode-cn.com/problems/jewels-and-stones/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int numJewelsInStones(string J, string S) {
        vector<bool> j(52, false);
        for(char a: J)
        {
            if(a >= 'a' && a <= 'z')
                j[a - 'a'] = true;
            else
                j[a - 'A' + 26] = true;
        }
        int ans = 0;
        for(char a: S)
        {
            if(a >= 'a' && a <= 'z')
            {
                if(j[a - 'a'])
                    ++ans;
            }
            else
            {
                if(j[a - 'A' + 26])
                    ++ans;
            }
        }
        return ans;
    }
};
