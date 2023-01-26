// prob1003: Check If Word Is Valid After Substitutions

/*
 * https://leetcode-cn.com/problems/check-if-word-is-valid-after-substitutions/
 */

#include <string>
#include <fstream>

using namespace std;

class Solution_2 {
public:
    bool isValid(string S) {
        int n = S.size();
        if(n % 3 != 0)
            return false;
        return check(S);
    }

private:
    bool check(const string& s)
    {
        int n = s.size();
        if(n == 3)
            return s == "abc";
        for(int i = 0; i <= n - 3; ++i)
        {
            if(s.substr(i, 3) == "abc" && check(s.substr(0, i) + s.substr(i + 3)))
                return true;
        }
        return false;
    }
};


class Solution {
public:
    bool isValid(string S) {
        int n = S.size();
        if(n % 3 != 0)
            return false;
        string st;
        for(int i = 0; i < n; ++i)
        {
            st += S[i];
            if((int)st.size() >= 3 && st.substr((int)st.size() - 3) == "abc")
                st.erase((int)st.size() - 3, 3);
        }
        return st.empty();
    }
};

int main()
{
    fstream fin("./prob1000_hard_Minimum-Cost-to-Merge-Stones.cpp");
}
