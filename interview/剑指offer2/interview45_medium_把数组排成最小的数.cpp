// interview45: 把数组排成最小的数

/*
 * https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Cmp2
{
    bool operator()(const string& n1, const string& n2) const
    {
        int len1 = n1.size(), len2 = n2.size();
        int len = min(len1, len2);
        int flag = len1 < len2;
        if(n1.substr(0, len) == n2.substr(0, len))
        {
            int l = max(len1, len2);
            l -= len;
            string n;
            if(flag)
                n = n2.substr(len);
            else
                n = n1.substr(len);
            for(int i = 0; i < l; ++i)
            {
                if(n1[0])
            }
            int cnt = 0;
            while(l > 0)
            {
                int i = 0;
                while(i < l && i < len)
                {
                    if(n1[i] == n[cnt * len + i])
                    {
                        ++i;
                        continue;
                    }
                    if(flag)
                        return n1[i] < n[cnt * len + i];
                    else
                        return n[cnt * len + i] < n1[i];
                }
                ++cnt;
                l -= len;
            }
            return !flag;
        }
        return n1.substr(0, len) < n2.substr(0, len);
    }
};

struct Cmp
{
    bool operator()(const string& n1, const string& n2) const
    {
        return n1 + n2 < n2 + n1;
    }
};

class Solution {
public:
    string minNumber(vector<int>& nums) {
        if(nums.empty()) return "";
        int n = nums.size();
        vector<string> num_strs(n);
        for(int i = 0; i < n; ++i)
        {
            num_strs[i] = to_string(nums[i]);
        }
        sort(num_strs.begin(), num_strs.end(), Cmp());
        string result = "";
        for(const string &item: num_strs)
        {
            result += item;
        }
        return result;
    }
};
