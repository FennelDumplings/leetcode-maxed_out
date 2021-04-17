// prob1564: Put Boxes Into the Warehouse I

/*
 * https://leetcode-cn.com/problems/put-boxes-into-the-warehouse-i/
 */

#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        int n = warehouse.size();
        vector<int> minh(n);
        // minh[i] := [0..i] 的最小高度
        minh[0] = warehouse[0];
        for(int i = 1; i < n; ++i)
            minh[i] = min(minh[i - 1], warehouse[i]);
        multiset<int> b(boxes.begin(), boxes.end());
        int ans = 0;
        for(int j = n - 1; j >= 0 && !b.empty(); --j)
        {
            int H = minh[j];
            auto it = b.upper_bound(H);
            if(it == b.begin())
                continue;
            --it;
            b.erase(it);
            ++ans;
        }
        return ans;
    }
};
