// interview60: n个骰子的点数

/*
 * https://leetcode-cn.com/problems/nge-tou-zi-de-dian-shu-lcof/
 */

#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

class Solution {
public:
    vector<double> twoSum(int n) {
        const double P = 1 / 6.0;
        if(n == 1) return {P,P,P,P,P,P};
        using PID = pair<int, double>;
        unordered_map<int, double> mapping;
        for(int i = 1; i <= 6; ++i) mapping[i] = P;
        for(int i = 2; i <= n; ++i)
        {
            unordered_map<int, double> new_mapping;
            for(PID item: mapping)
            {
                int y = item.first;
                double p = item.second;
                for(int x = 1; x <= 6; ++x)
                {
                    int s = x + y;
                    if(new_mapping.find(s) == new_mapping.end())
                        new_mapping[s] = 0.0;
                    new_mapping[s] += p * P;
                }
            }
            mapping = new_mapping;
        }
        vector<double> result;
        map<int, double> mapp;
        for(PID item: mapping)
            mapp.insert(item);
        for(PID item: mapp)
            result.push_back(item.second);
        return result;
    }
};
