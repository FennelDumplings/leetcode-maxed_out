// prob1090: Largest Values From Labels

/*
 * https://leetcode-cn.com/problems/largest-values-from-labels/
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Item
{
    int val;
    int label;
    Item(int v, int l):val(v),label(l){}
    Item():val(-1),label(-1){}
};

struct Cmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        return i1.val > i2.val;
    }
};

class Solution {
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int num_wanted, int use_limit) {
        int n = values.size();
        vector<Item> items(n);
        int max_label = -1;
        for(int i = 0; i < n; ++i)
        {
            items[i].val = values[i];
            items[i].label = labels[i];
            max_label = max(max_label, labels[i]);
        }
        vector<int> labels_record(max_label + 1, use_limit);
        sort(items.begin(), items.end(), Cmp());
        int cnt = 0;
        int ans = 0;
        for(const Item& i: items)
        {
            if(labels_record[i.label] == 0)
                continue;
            ans += i.val;
            ++cnt;
            --labels_record[i.label];
            if(cnt == num_wanted)
                break;
        }
        return ans;
    }
};
