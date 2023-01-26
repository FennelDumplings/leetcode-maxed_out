// prob1424: Diagonal Traverse II

/*
 * https://leetcode-cn.com/problems/diagonal-traverse-ii/
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Item
{
    int i, j;
    Item(int i, int j):i(i),j(j){}
};

struct Cmp
{
    bool operator()(const Item& item1, const Item& item2) const
    {
        int sum1 = item1.i + item1.j;
        int sum2 = item2.i + item2.j;
        if(sum1 == sum2)
            return item1.i > item2.i;
        return sum1 < sum2;
    }
};

class Solution_2 {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        vector<Item> items;
        int n = nums.size();
        for(int i = 0; i < n; ++i)
        {
            int m = nums[i].size();
            for(int j = 0; j < m; ++j)
                items.emplace_back(i, j);
        }
        sort(items.begin(), items.end(), Cmp());
        int N = items.size();
        vector<int> result(N);
        for(int i = 0; i < N; ++i)
            result[i] = nums[items[i].i][items[i].j];
        return result;
    }
};


// 桶排序

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        int n = nums.size();
        vector<vector<int>> buckets;
        int all = 0;
        for(int i = 0; i < n; ++i)
        {
            int m = nums[i].size();
            all += m;
            for(int j = 0; j < m; ++j)
            {
                int k = i + j;
                if((int)buckets.size() < k + 1)
                    buckets.push_back({});
                buckets[k].push_back(nums[i][j]);
            }
        }
        vector<int> result(all);
        int idx = 0;
        int N = buckets.size();
        for(int k = 0; k < N; ++k)
        {
            int bn = buckets[k].size();
            for(int i = bn - 1; i >= 0; --i)
                result[idx++] = buckets[k][i];
        }
        return result;
    }
};


