
#include <string>
#include <algorithm>

using namespace std;

bool cmp(const string& s, const string& t)
{
    return s < t;
}

class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        int n = s.size();
        string iter = s;
        string ans = s;
        while(true)
        {
            int flag = 0;
            if(cmp(iter, ans))
                ans = iter;
            string p = iter;
            while(true)
            {
                flag = (flag + a) % 10;
                if(flag == 0)
                    break;
                for(int i = 0; i < n; i += 2)
                {
                    char &ch = p[i + 1];
                    int k = ch - '0';
                    k = (k + a) % 10;
                    ch = '0' + k;
                }
                if(cmp(p, ans))
                    ans = p;
            }
            rotate(iter.begin(), iter.begin() + b, iter.end());
            if(iter == s)
                break;
        }
        return ans;
    }
};
