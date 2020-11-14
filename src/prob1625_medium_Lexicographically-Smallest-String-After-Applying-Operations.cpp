// prob1625: Lexicographically Smallest String After Applying Operations

/*
 * https://leetcode-cn.com/problems/lexicographically-smallest-string-after-applying-operations/
 */

#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    string findLexSmallestString(string s, int a, int b) {
        visited = unordered_set<string>();
        min_dict_order_str = s;
        dfs(s, a, b);
        return min_dict_order_str;
    }

private:
    unordered_set<string> visited;
    string min_dict_order_str;

    void dfs(const string& s, const int& a, const int& b)
    {
        visited.insert(s);
        if(s < min_dict_order_str)
            min_dict_order_str = s;
        string nxt = s;
        rotate(nxt.begin(), nxt.begin() + b, nxt.end());
        if(visited.count(nxt) == 0)
            dfs(nxt, a, b);
        nxt = s;
        int n = nxt.size();
        for(int i = 1; i < n; i += 2)
        {
            int d = nxt[i] - '0';
            d = (d + a) % 10;
            nxt[i] = '0' + d;
        }
        if(visited.count(nxt) == 0)
            dfs(nxt, a, b);
    }
};
