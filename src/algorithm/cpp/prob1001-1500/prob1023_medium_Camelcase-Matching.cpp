// prob1023: Camelcase Matching

/*
 * https://leetcode-cn.com/problems/camelcase-matching/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        int m = queries.size();
        vector<bool> result(m);
        for(int i = 0; i < m; ++i)
            result[i] = check(queries[i], pattern);
        return result;
    }

private:
    bool check(const string& s, const string& p)
    {
        int np = p.size();
        int ip = 0;
        int ns = s.size();
        int is = 0;
        while(is < ns && ip < np)
        {
            while(is < ns && s[is] != p[ip])
            {
                if(s[is] <= 'Z' && s[is] >= 'A')
                    return false;
                ++is;
            }
            if(is == ns)
                return false;
            ++is;
            ++ip;
        }
        if(ip < np)
            return false;
        while(is < ns && s[is] <= 'z' && s[is] >= 'a')
            ++is;
        return is == ns;
    }
};
