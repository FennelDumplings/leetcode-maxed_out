// prob1054:  Distant Barcodes

/*
 * https://leetcode-cn.com/problems/distant-barcodes/
 */

#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Item
{
    int v, cnt;
    Item(int v, int cnt):v(v),cnt(cnt){}
    Item():v(-1),cnt(0){}
};

struct HeapCmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        return i1.cnt < i2.cnt;
    }
};

class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        int n = barcodes.size();
        if(n <= 2)
            return barcodes;
        const int MAX_VAL = 10000;
        vector<int> cnts(MAX_VAL + 1);
        for(int i: barcodes)
            ++cnts[i];
        priority_queue<Item, vector<Item>, HeapCmp> pq;
        for(int i = 1; i <= MAX_VAL; ++i)
        {
            if(cnts[i] == 0)
                continue;
            pq.push(Item(i, cnts[i]));
        }
        vector<int> result(n, -1);
        bool odd = true;
        int iter = 0;
        while(!pq.empty())
        {
            Item item = pq.top();
            int cnt = item.cnt;
            while(iter < n && cnt > 0)
            {
                result[iter] = item.v;
                iter += 2;
                --cnt;
            }
            if(iter >= n && odd)
            {
                odd = false;
                iter = 1;
                while(iter < n && cnt > 0)
                {
                    result[iter] = item.v;
                    iter += 2;
                    --cnt;
                }
            }
        }
        return result;
    }
};
