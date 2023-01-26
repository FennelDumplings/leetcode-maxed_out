// prob93: Restore IP Addresses

/*
 * Given a string containing only digits, restore it by returning all possible valid IP address combinations.
 */

/*
 * Example:
 * Input: "25525511135"
 * Output: ["255.255.11.135", "255.255.111.35"]
 */

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        int n = s.size();
        if(n < 4 || n > 12) return vector<string>();
        vector<string> results;
        int pos = 0;
        int num = 0;
        string path;
        dfs(s, results, path, pos, n, num);
        return results;
    }

private:
    void dfs(const string& s, vector<string>& results, string path, int pos, int n, int num)
    {
        if(pos == n)
        {
            if(num == 4)
            {
                results.push_back(path.substr(1));
            }
            return;
        }

        if(num > 4) return;

        if(s[pos] == '0')
            dfs(s, results, path + ".0", pos + 1, n, num + 1);
        else
        {
            for(int i = pos, x = 0; i < n; ++i)
            {
                x = x * 10 + s[i] - '0';
                if(x < 256)
                    dfs(s, results, path + '.' + to_string(x), i + 1, n, num + 1);
                else
                    break;
            }
        }
    }
};
