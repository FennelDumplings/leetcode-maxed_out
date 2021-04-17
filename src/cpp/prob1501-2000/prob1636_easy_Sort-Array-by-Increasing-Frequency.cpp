// prob1636: Sort Array by Increasing Frequency

/*
 * https://leetcode-cn.com/problems/sort-array-by-increasing-frequency/
 */

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Item
{
    int val;
    int cnt;
    Item(int v, int c):val(v),cnt(c){}
};

struct Cmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        if(i1.cnt == i2.cnt)
            return i1.val > i2.val;
        return i1.cnt < i2.cnt;
    }
};

class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        unordered_map<int, int> mapping; // 值 -> 频数
        for(int i: nums)
            ++mapping[i];
        vector<Item> items;
        for(auto i: mapping)
            items.emplace_back(i.first, i.second);
        sort(items.begin(), items.end(), Cmp());
        vector<int> result;
        for(auto item: items)
        {
            for(int i = 0; i < item.cnt; ++i)
                result.push_back(item.val);
        }
        return result;
    }
};
