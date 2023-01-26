// prob1337: The K Weakest Rows in a Matrix

/*
 * https://leetcode-cn.com/problems/the-k-weakest-rows-in-a-matrix/
 */

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct Item
{
    int cnt;
    int idx;
    Item(int c, int i):cnt(c),idx(i){}
};

struct Cmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        if(i1.cnt == i2.cnt)
            return i1.idx < i2.idx;
        return i1.cnt < i2.cnt;
    }
};

class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        int n = mat.size();
        vector<Item> row_infos;
        for(int i = 0; i < n; ++i)
        {
            const vector<int> &row = mat[i];
            auto it = lower_bound(row.begin(), row.end(), 0, greater<int>());
            row_infos.emplace_back(it - row.begin(), i);
        }
        sort(row_infos.begin(), row_infos.end(), Cmp());
        vector<int> result(k);
        for(int i = 0; i < k; ++i)
            result[i] = row_infos[i].idx;
        return result;
    }
};
