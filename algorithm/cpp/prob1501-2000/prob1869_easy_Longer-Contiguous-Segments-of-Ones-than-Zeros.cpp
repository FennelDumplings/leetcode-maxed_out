
#include <string>

using namespace std;

class Solution {
public:
    bool checkZeroOnes(string s) {
        int l1 = sub(s, '1');
        int l0 = sub(s, '0');
        return l1 > l0;
    }

private:
    int sub(const string& s, char ch)
    {
        int n = s.size();
        int l = 0;
        while(l < n && s[l] != ch)
            ++l;
        int ans = 0;
        while(l < n)
        {
            int r = l;
            while(r < n && s[r] == ch)
                ++r;
            ans = max(ans, r - l);
            l = r;
            while(l < n && s[l] != ch)
                ++l;
        }
        return ans;
    }
};
