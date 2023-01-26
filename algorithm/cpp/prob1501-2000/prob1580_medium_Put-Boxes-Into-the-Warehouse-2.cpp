// prob1580: Put Boxes Into the Warehouse II

/*
 * https://leetcode-cn.com/problems/put-boxes-into-the-warehouse-ii/
 */

#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {

        int n = warehouse.size();
        int mini = 0;
        int minx = warehouse[0];
        for(int i = 1; i < n; ++i)
        {
            if(warehouse[i] < minx)
            {
                minx = warehouse[i];
                mini = i;
            }
        }
        vector<int> minh(n);
        minh[mini] = minx;
        // minh[i] := [0..i] 的最小高度 或者 [i..n-1] 的最小高度
        minh[0] = warehouse[0];
        for(int i = 1; i < mini; ++i)
            minh[i] = min(minh[i - 1], warehouse[i]);
        minh[n - 1] = warehouse[n - 1];
        for(int i = n - 2; i > mini; --i)
            minh[i] = min(minh[i + 1], warehouse[i]);
        multiset<int> b(boxes.begin(), boxes.end());
        int ans = 0;
        for(int j = mini; j >= 0 && !b.empty(); --j)
        {
            int H = minh[j];
            auto it = b.upper_bound(H);
            if(it == b.begin())
                continue;
            --it;
            b.erase(it);
            ++ans;
        }
        for(int j = mini + 1; j < n && !b.empty(); ++j)
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
