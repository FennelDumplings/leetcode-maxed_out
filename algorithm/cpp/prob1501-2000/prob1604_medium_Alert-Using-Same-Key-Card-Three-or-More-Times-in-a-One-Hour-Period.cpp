// prob1604: Alert Using Same Key-Card Three or More Times in a One Hour Period

/*
 * https://leetcode-cn.com/problems/alert-using-same-key-card-three-or-more-times-in-a-one-hour-period/
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        unordered_map<string, vector<int>> mapping;
        int n = keyName.size();
        for(int i = 0; i < n; ++i)
        {
            mapping[keyName[i]].push_back(get_minute(keyTime[i]));
        }
        vector<string> result;
        for(auto info: mapping)
        {
            if(check(info.second))
                result.push_back(info.first);
        }
        sort(result.begin(), result.end());
        return result;
    }

private:
    unordered_map<string, vector<int>> mapping;

    bool check(vector<int>& ts)
    {
        int n = ts.size();
        if(n < 3)
            return false;
        sort(ts.begin(), ts.end());
        for(int i = 0; i <= n - 3; ++i)
        {
            int j = i + 2;
            if(ts[j] - ts[i] <= 60)
                return true;
        }
        return false;
    }

    int get_minute(const string& t)
    {
        int ans = 0;
        string h_str = t.substr(0, 2);
        stringstream ss;
        ss << h_str;
        int h;
        ss >> h;
        ans += h * 60;
        string m_str = t.substr(3);
        ss.clear();
        ss << m_str;
        int m;
        ss >> m;
        ans += m;
        return ans;
    }
};
